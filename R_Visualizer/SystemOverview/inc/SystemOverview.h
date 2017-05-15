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
class SystemOverview : public ISystemOverview
{
    Q_OBJECT
public:
    explicit SystemOverview(
            ISystemOverviewObjectStore *systemOverviewObjectStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~SystemOverview();

    virtual void receiveMsg(const IMsg &receivedMsg);
    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply);

private:
    ISystemOverviewObjectStore *systemOverviewObjectStore;

};

#endif // SYSTEMOVERVIEW_H
