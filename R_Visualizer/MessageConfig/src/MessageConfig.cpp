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

/* QCompleter *MessageConfig::createAliasCompleterForMapping( */
/*         const IMessageConfig::MessageMappingTypes mappingType, */
/*         QObject *parent */
/*         ) */
/* { */
/*     switch(mappingType) */
/*     { */
/*     case IMessageConfig::MessageIDMappingType: */
/*         //return createIDNameCompleter(parent); */
/*         break; */
/*     case IMessageConfig::MessageCodeMappingType: */
/*         //return createCodeNameCompleter(parent); */
/*         break; */
/*     case IMessageConfig::MessageDataMappingType: */
/*         return Q_NULLPTR; */
/*         break; */
/*     default: */
/*         return Q_NULLPTR; */
/*     } */
/* } */

void MessageConfig::applyUserRole(
        const UserRoleManagement::UserRole roleToApply
        )
{
    //ToDO
}

//MessageConfigNotifier *MessageConfig::getNotifier()
//{
    //return msgConfigNotifier;
//}

//ToTHINK DEPRECATED?
//void MessageConfig::accept(FileParser *visitor)
//{
//    visitor->visit(*this);
//}

/* void MessageConfig::slt_ApplyRole(const UserRoleManagement::UserRole roleToApply) */
/* { */
/*     emit IMessageConfig::sgnl_PropagateUserRole(roleToApply); */
/* } */


//QCompleter *MessageConfig::createIDNameCompleter(
        //QObject *parent
        //) const
//{
    //return msgIDMapping->createIDNameCompleter(parent);
//}

//QCompleter *MessageConfig::createCodeNameCompleter(
        //QObject *parent
        //) const
//{
    //return msgCodeMapping->createCodeNameCompleter(parent);
//}

