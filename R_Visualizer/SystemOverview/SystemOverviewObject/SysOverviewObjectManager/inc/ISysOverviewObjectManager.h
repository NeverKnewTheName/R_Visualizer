/**
 * @file ISysOverviewObjectManager.h
 * @author Christian Neuberger
 * @date 2017-05-01
 * 
 * @brief Interface for managers for #ISystemOverviewObject
 */
#ifndef ISYSOVERVIEWOBJECTMANAGER_H
#define ISYSOVERVIEWOBJECTMANAGER_H

#include <QPainter>
#include <QRectF>
#include <QColor>

/**
 * @brief The ISysOverviewObjectManager interface
 */
class ISysOverviewObjectManager
{
public:
    enum ObjectType
    {
        INVALID_TYPE,
        ShapeType,
        ImageType,
        UserType
    };

    virtual ~ISysOverviewObjectManager(){}

    virtual ISysOverviewObjectManager *clone() const = 0;

    virtual void paint(
            QPainter *painter,
            const QRectF &boundingRect,
            const bool selected
            ) = 0;

    ObjectType getType() const
    {
        return type;
    }

    virtual QString getTypeAsString() const
    {
        return translateObjectType(type);
    }

    static QString translateObjectType(const ObjectType type)
    {
        switch(type)
        {
        case INVALID_TYPE:
            return QString("Invalid Type");
            break;
        case ShapeType:
            return QString("Shape Type");
            break;
        case ImageType:
            return QString("Image Type");
            break;
        case UserType:
            return QString("User Type");
            break;
        }
    }

protected:
    ISysOverviewObjectManager(const ObjectType type) : type(type)
    {
    }

private:
    ObjectType type;
};

template<class Derived>
class ISysOverviewObjectManagerCRTPHelper : public ISysOverviewObjectManager
{
public:
    using ISysOverviewObjectManager::ISysOverviewObjectManager;

    virtual ISysOverviewObjectManager *clone() const
    {
        return new Derived(static_cast<const Derived &>(*this));
    }
};

#endif /* ISYSOVERVIEWOBJECTMANAGER_H */
