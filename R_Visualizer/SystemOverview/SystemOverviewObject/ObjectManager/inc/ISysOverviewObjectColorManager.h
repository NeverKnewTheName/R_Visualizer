#ifndef ISYSOVERVIEWOBJECTCOLORMANAGER_H
#define ISYSOVERVIEWOBJECTCOLORMANAGER_H

#include <QColor>
#include <QSharedPointer>
#include <memory>

class SysOverviewObjectShapeManager;

class ISysOverviewObjectColorManager
{
public:
    virtual ~ISysOverviewObjectColorManager(){}

    virtual ISysOverviewObjectColorManager *clone() const = 0;

    virtual void setFillColor(const QColor &color) = 0;
    virtual QColor getFillColor() const = 0;
    virtual QColor getHighlightFillColor() const = 0;

    virtual void setBorderColor(const QColor &color) = 0;
    virtual QColor getBorderColor() const = 0;

    virtual void setTransparency(const qreal transparency) = 0;
    virtual qreal getTransparency() const = 0;

    virtual void setShapeManager(SysOverviewObjectShapeManager *shapeManager) = 0;
};

typedef std::unique_ptr<ISysOverviewObjectColorManager> SysOvrvObjColorManagerPtr;
typedef QSharedPointer<ISysOverviewObjectColorManager> SysOvrvObjColorManagerSharedPtr;

template<class Derived>
class ISysOverviewObjectColorManagerCRTPHelper :
        public ISysOverviewObjectColorManager
{
public:
    ISysOverviewObjectColorManager *clone() const
    {
        return new Derived(static_cast<const Derived &>(*this));
    }
};

#endif // ISYSOVERVIEWOBJECTCOLORMANAGER_H
