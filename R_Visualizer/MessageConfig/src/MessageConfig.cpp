#include "MessageConfig.h"

#include "IMsgMappingManager.h"
#include "IMsgIDMappingManager.h"
#include "IMsgCodeMappingManager.h"
#include "IMsgDataMappingManager.h"
#include "IPrettyMsg.h"

MessageConfig::MessageConfig(
        IMsgIDMappingManager *msgIDMappingManager,
        IMsgCodeMappingManager *msgCodeMappingManager,
        IMsgDataMappingManager *msgDataMappingManager,
        QObject *parent
        ) :
    IMessageConfig(parent),
    msgIDMappingManager(msgIDMappingManager),
    msgCodeMappingManager(msgCodeMappingManager),
    msgDataMappingManager(msgDataMappingManager)
{
    connect(
            msgIDMappingManager,
            &IMsgIDMappingManager::sgnl_MappingManagerChanged,
            this,
            &IMessageConfig::sgnl_MappingManagerChanged
            );
    connect(
            msgCodeMappingManager,
            &IMsgCodeMappingManager::sgnl_MappingManagerChanged,
            this,
            &IMessageConfig::sgnl_MappingManagerChanged
            );
    connect(
            msgDataMappingManager,
            &IMsgDataMappingManager::sgnl_MappingManagerChanged,
            this,
            &IMessageConfig::sgnl_MappingManagerChanged
            );
}

MessageConfig::~MessageConfig()
{
}

void MessageConfig::prettifyMsg(
        IPrettyMsg &msgToPrettify
        ) const
{
    msgIDMappingManager->prettifyMsg(msgToPrettify);
    msgCodeMappingManager->prettifyMsg(msgToPrettify);
    msgDataMappingManager->prettifyMsg(msgToPrettify);
}

void MessageConfig::prettifyMsgByMappingManager(
        IPrettyMsg &msgToPrettify,
        const IMsgMappingManager &mappingToApply
        ) const
{
    mappingToApply.prettifyMsg(msgToPrettify);
}

void MessageConfig::applyUserRole(
        const UserRoleManagement::UserRole roleToApply
        )
{
    //ToDO
}
