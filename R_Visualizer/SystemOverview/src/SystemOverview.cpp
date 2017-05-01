#include "SystemOverview.h"

#include "IMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

SystemOverview::SystemOverview(
        QObject *parent
        ) :
    ISystemOverview(parent)
{

}

SystemOverview::~SystemOverview()
{
}

void SystemOverview::receiveMsg(const IMsg &receivedMsg)
{
    const MsgIDType &msgID = receivedMsg.getMsgID();
    const MsgCodeType &msgCode = receivedMsg.getMsgCode();
    const MsgDataType &msgData = receivedMsg.getMsgData();
}

void SystemOverview::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
    //ToDo
}

SystemOverviewNotifier *SystemOverview::getNotifier()
{
    return notifier;
}
