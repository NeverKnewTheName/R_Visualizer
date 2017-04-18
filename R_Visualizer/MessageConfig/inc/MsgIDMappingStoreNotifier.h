#ifndef MSGIDMAPPINGSTORENOTIFIER_H
#define MSGIDMAPPINGSTORENOTIFIER_H

#include <QObject>

class IMsgIDMappingStore;

class MsgIDMappingStoreNotifier : public QObject
{
    Q_OBJECT
public:
    MsgIDMappingStoreNotifier(
            IMsgIDMappingStore *msgIDMappingStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgIDMappingStoreNotifier();

private:
    IMsgIDMappingStore *msgIDMappingStore;
};

#endif /* MSGIDMAPPINGSTORENOTIFIER_H */
