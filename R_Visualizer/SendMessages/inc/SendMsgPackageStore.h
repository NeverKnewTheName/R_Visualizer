/**
 * @file SendMsgPackageStore.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The default implementation for the #ISendMsgPackageStore
 */
#ifndef SENDMSGPACKAGESTORE_H
#define SENDMSGPACKAGESTORE_H

#include <QObject>
#include <QVector>

#include "ISendMsgPackageStore.h"
#include "PrettyMsg.h"

/**
 * @brief The SendMsgPackageStore
 */
class SendMsgPackageStore : public QObject, public ISendMsgPackageStore
{
    Q_OBJECT
public:
    SendMsgPackageStore(
            QObject *parent = Q_NULLPTR
            );
    virtual ~SendMsgPackageStore();

    /**
     * @brief Appends the given message to the store
     * 
     * The msgToAppend can be left empty to construct a default #IPrettyMsg
     * derivate. A mofiable reference is returned to the caller. This is done
     * to not inflict the low level details about which #IPrettyMsg
     * implementation has been implemented in this store. The caller can work
     * with the returned #IPrettyMsg reference without being concerned about
     * these details.
     */
    IPrettyMsg &appendMsg(const IPrettyMsg &msgToAppend = PrettyMsg());

signals:

public slots:

private:
    QVector<PrettyMsg> msgStorage;
};

#endif /* SENDMSGPACKAGESTORE_H */
