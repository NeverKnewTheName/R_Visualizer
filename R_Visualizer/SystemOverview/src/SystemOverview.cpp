#include "SystemOverview.h"

#include "SystemOverviewNotifier.h"

SystemOverview::SystemOverview(QObject *parent) :
    QObject(parent),
    notifier(new SystemOverviewNotifier(this, this))
{

}

SystemOverview::~SystemOverview()
{
}

void SystemOverview::receiveMsg(const IMsg &receivedMsg)
{
    //ToDo
}

void SystemOverview::applyUserRole(const UserRoleMngr::UserRole roleToApply)
{
    //ToDo
}

SystemOverviewNotifier *SystemOverview::getNotifier()
{
    return notifier;
}
