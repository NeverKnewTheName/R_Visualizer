/**
 * @file SystemOverview.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The SystemOverview
 */
#ifndef SYSTEMOVERVIEW_H
#define SYSTEMOVERVIEW_H

#include <QObject>
#include "ISystemOverview.h"

class SystemOverviewNotifier;

/**
 * @brief The SystemOverview
 */
class SystemOverview : public QObject, public ISystemOverview
{
    Q_OBJECT
public:
    explicit SystemOverview(QObject *parent = 0);
    virtual ~SystemOverview();

    virtual void receiveMsg(const IMsg &receivedMsg);
    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);

    virtual SystemOverviewNotifier *getNotifier();

private:
    SystemOverviewNotifier *notifier;
};

#endif // SYSTEMOVERVIEW_H
