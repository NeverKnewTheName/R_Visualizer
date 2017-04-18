#ifndef MSGDATAMAPPINGSTORENOTIFIER_H
#define MSGDATAMAPPINGSTORENOTIFIER_H

#include <QObject>

class IMsgDataMappingStore;

class MsgDataMappingStoreNotifier : public QObject
{
    Q_OBJECT
public:
    MsgDataMappingStoreNotifier(
            IMsgDataMappingStore *msgDataMappingStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgDataMappingStoreNotifier();

private:
    IMsgDataMappingStore *msgDataMappingStore;
};

#endif /* MSGDATAMAPPINGSTORENOTIFIER_H */
