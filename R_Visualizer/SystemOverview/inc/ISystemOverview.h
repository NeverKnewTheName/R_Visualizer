/**
 * @file ISystemOverview.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The interface for the System Overview
 */
#ifndef ISYSTEMOVERVIEW_H
#define ISYSTEMOVERVIEW_H

#include <QObject>

#include "IUserRoleManager.h"

class SystemOverviewNotifier;
class IMsg;

/**
 * @brief The ISystemOverview interface
 */
class ISystemOverview : public QObject
{
    Q_OBJECT
public:
    ISystemOverview(QObject *parent = Q_NULLPTR) : QObject(parent){}
    virtual ~ISystemOverview(){}

    virtual void receiveMsg(const IMsg &receivedMsg) = 0;
    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply) = 0;

signals:

public slots:
    virtual void slt_ReceiveMsg(const IMsg &receivedMsg)
    {
        receiveMsg(receivedMsg);
    }

};

#endif /* ISYSTEMOVERVIEW_H */
