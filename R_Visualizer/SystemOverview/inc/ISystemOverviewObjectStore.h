/**
 * @file ISystemOverviewObjectStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The ISystemOverviewObjectStore interface
 */
#ifndef ISYSTEMOVERVIEWOBJECTSTORE_H
#define ISYSTEMOVERVIEWOBJECTSTORE_H

#include <QObject>

#include "ISystemOverviewObject.h"

/**
 * @brief The ISystemOverviewObjectStore interface
 */
class ISystemOverviewObjectStore : public QObject
{
    Q_OBJECT

public:
    ISystemOverviewObjectStore(
            QObject *parent = Q_NULLPTR
            ) :
        QObject(parent)
    {
    }
    virtual ~ISystemOverviewObjectStore(){}

    virtual void addSystemOverviewObject(ISysOvrvObjPtr object) = 0;
    virtual ISysOvrvObjPtr getObj(const QString &objectName) = 0;
    virtual void removeObj(const QString &objectName) = 0;
    virtual QVector<ISysOvrvObjPtr> getObjects() const = 0;

    virtual void clear() = 0;
signals:
    void sgnl_objectAdded(ISysOvrvObjPtr obj);
    void sgnl_objectRemoved(ISysOvrvObjPtr obj);
};

#endif /* ISYSTEMOVERVIEWOBJECTSTORE_H */
