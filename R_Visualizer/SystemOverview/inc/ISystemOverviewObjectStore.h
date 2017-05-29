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

class ISystemOverviewObject;

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

    virtual void addSystemOverviewObject(ISystemOverviewObject *object) = 0;
};

#endif /* ISYSTEMOVERVIEWOBJECTSTORE_H */
