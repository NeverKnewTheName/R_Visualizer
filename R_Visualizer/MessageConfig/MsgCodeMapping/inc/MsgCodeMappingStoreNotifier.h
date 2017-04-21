/**
 * @file MsgCodeMappingStoreNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-18
 * 
 * @brief The signal and slot handler for the #IMsgCodeMappingStore
 */
#ifndef MSGCODEMAPPINGSTORENOTIFIER_H
#define MSGCODEMAPPINGSTORENOTIFIER_H

#include <QObject>

class IMsgCodeMappingStore;

/**
 * @brief THe MsgCodeMappingStoreNotifier
 */
class MsgCodeMappingStoreNotifier : public QObject
{
    Q_OBJECT
public:
    MsgCodeMappingStoreNotifier(
            IMsgCodeMappingStore *msgCodeMappingStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeMappingStoreNotifier();

private:
    IMsgCodeMappingStore *msgCodeMappingStore;
};

#endif /* MSGCODEMAPPINGSTORENOTIFIER_H */
