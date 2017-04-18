/**
 * @file SystemOverviewNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-18
 * 
 * @brief The singal and slot manager for #ISystemOverview
 */
#ifndef SYSTEMOVERVIEWNOTIFIER_H
#define SYSTEMOVERVIEWNOTIFIER_H

#include <QObject>
#include "userrolemngr.h"

class ISystemOverview;
class IMsg;

/**
 * @brief The SystemOverviewNotifier
 */
class SystemOverviewNotifier : public QObject
{
    Q_OBJECT
public:
    SystemOverviewNotifier(
            ISystemOverview *systemOverview,
            QObject *parent = Q_NULLPTR
            );
    virtual ~SystemOverviewNotifier();

signals:

public slots:
    void slt_receiveMsg(const IMsg &receivedMsg);
    void slt_applyUserRole(const UserRoleMngr::UserRole roleToApply);

private:
    ISystemOverview *systemOverview;
};

#endif /* SYSTEMOVERVIEWNOTIFIER_H */
