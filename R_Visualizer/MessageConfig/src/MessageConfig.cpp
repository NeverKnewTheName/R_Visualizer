#include "MessageConfig.h"

#include "MessageConfigNotifier.h"

#include "IMsgMapping.h"
#include "IMsgIDMapping.h"
#include "IMsgCodeMapping.h"
#include "IMsgDataMapping.h"
#include "IPrettyMsg.h"

MessageConfig::MessageConfig(
        IMsgIDMapping *msgIDMapping,
        IMsgCodeMapping *msgCodeMapping,
        IMsgDataMapping *msgDataMapping,
        QObject *parent
        ) :
    QObject(parent),
    msgConfigNotifier(new MessageConfigNotifier(this, this)),
    msgIDMapping(msgIDMapping),
    msgCodeMapping(msgCodeMapping),
    msgDataMapping(msgDataMapping)
{
}

MessageConfig::~MessageConfig()
{
}

void MessageConfig::prettifyMsg(
        IPrettyMsg &msgToPrettify
        ) const
{
    msgIDMapping->prettifyMsg(msgToPrettify);
    msgCodeMapping->prettifyMsg(msgToPrettify);
    msgDataMapping->prettifyMsg(msgToPrettify);
}

void MessageConfig::prettifyMsgByMapping(
        IPrettyMsg &msgToPrettify,
        const IMsgMapping &mappingToApply
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
        const UserRoleMngr::UserRole roleToApply
        )
{
    //ToDO
}

MessageConfigNotifier *MessageConfig::getNotifier()
{
    return msgConfigNotifier;
}

//ToTHINK DEPRECATED?
//void MessageConfig::accept(FileParser *visitor)
//{
//    visitor->visit(*this);
//}

/* void MessageConfig::slt_ApplyRole(const UserRoleMngr::UserRole roleToApply) */
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

