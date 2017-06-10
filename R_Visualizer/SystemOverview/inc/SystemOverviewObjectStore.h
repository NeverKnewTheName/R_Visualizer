/**
 * @file SystemOverviewObjectStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The SystemOverviewObjectStore
 */
#ifndef SYSTEMOVERVIEWOBJECTSTORE_H
#define SYSTEMOVERVIEWOBJECTSTORE_H

#include <QHash>

#include "ISystemOverviewObjectStore.h"


/**
 * @brief The SystemOverviewObjectStore
 */
class SystemOverviewObjectStore : public ISystemOverviewObjectStore
{
    Q_OBJECT
public:
    SystemOverviewObjectStore(
            QObject *parent = Q_NULLPTR
            );
    virtual ~SystemOverviewObjectStore();

    virtual void addSystemOverviewObject(ISysOvrvObjPtr object);
    virtual ISysOvrvObjPtr getObj(const QString &objectName);
    virtual void removeObj(const QString &objectName);
    virtual QVector<ISysOvrvObjPtr> getObjects() const;

    virtual void clear();
private:
    QHash<QString,ISysOvrvObjPtr> sysOverviewObjStore;

};

#endif /* SYSTEMOVERVIEWOBJECTSTORE_H */
