/**
 * @file SendMessages.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The default implementation of the #ISendMessages interface
 */
#ifndef SENDMESSAGES_H
#define SENDMESSAGES_H

#include <QObject>
#include <QVector>

#include "ISendMessages.h"

class ISendMsgSingle;
class ISendMsgPackage;

/**
 * @brief The SendMessages
 */
class SendMessages : public QObject, public ISendMessages
{
    Q_OBJECT
public:
    SendMessages(QObject *parent = Q_NULLPTR);
    virtual ~SendMessages();

    virtual void addSendMsgSingle(ISendMsgSingle *sendMsgSingleToAdd);
    virtual void removeSendMsgSingle(ISendMsgSingle *sendMsgSingleToAdd);

    virtual void addSendMsgPackage(ISendMsgPackage *sendMsgPackageToAdd);
    virtual void removeSendMsgPackage(ISendMsgPackage *sendMsgPackageToAdd);

public slots:
    void slt_applyUserRole(const UserRoleMngr::UserRole roleToApply);

private:
    QVector<ISendMsgSingle *> sendMsgSingleInstances;
    QVector<ISendMsgPackage *> sendMsgPackageInstances;
    UserRoleMngr::UserRole currentUserRole;

};

#endif /* SENDMESSAGES_H */
