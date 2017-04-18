#include "SystemOverviewNotifier.h"

#include "ISystemOverview.h"

SystemOverviewNotifier::SystemOverviewNotifier(
        ISystemOverview *systemOverview,
        QObject *parent
        ) :
    QObject(parent),
    systemOverview(systemOverview)
{
}

SystemOverviewNotifier::~SystemOverviewNotifier()
{
}

void SystemOverviewNotifier::slt_receiveMsg(
        const IMsg &receivedMsg
        )
{
    systemOverview->receiveMsg(receivedMsg);
}

void SystemOverviewNotifier::slt_applyUserRole(
        const UserRoleMngr::UserRole roleToApply
        )
{
    systemOverview->applyUserRole(roleToApply);
}
