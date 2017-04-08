#include "MessageConfig.h"

#include "IMsgIDMapping.h"
#include "IMsgCodeMapping.h"
#include "IMsgDataMapping.h"

MessageConfig::MessageConfig(
        IMsgIDMapping *msgIDMapping,
        IMsgCodeMapping *msgCodeMapping,
        IMsgDataMapping *msgDataMapping,
        QObject *parent
        ) : 
    QObject(parent),
    msgIDMapping(msgIDMapping),
    msgCodeMapping(msgCodeMapping),
    msgDataMapping(msgDataMapping)
{
}

MessageConfig::~MessageConfig()
{
}

IPrettyMsgUniqPtr<IMsg> MessageConfig::prettifyMsg(
        IPrettyMsgUniqPtr<IMsg> msgToPrettify
        ) const
{

    return std::move(msgToPrettify);
}

IPrettyMsgUniqPtr<ITimestampedMsg> MessageConfig::prettifyMsg(
        IPrettyMsgUniqPtr<ITimestampedMsg> msgToPrettify
        ) const
{

    return std::move(msgToPrettify);
}

QCompleter *MessageConfig::createAliasCompleterForMapping(
        const IMessageConfig::MessageMappingTypes mappingType,
        QObject *parent
        )
{
    switch(mappingType)
    {
    case IMessageConfig::MessageIDMappingType:
        return createIDNameCompleter(parent);
        break;
    case IMessageConfig::MessageCodeMappingType:
        return createCodeNameCompleter(parent);
        break;
    case IMessageConfig::MessageDataMappingType:
        return Q_NULLPTR;
        break;
    default:
        return Q_NULLPTR;
    }
}

//ToTHINK DEPRECATED?
//void MessageConfig::accept(FileParser *visitor)
//{
//    visitor->visit(*this);
//}

void MessageConfig::slt_ApplyRole(const UserRoleMngr::UserRole roleToApply)
{
    emit sgnl_PropagateUserRole(roleToApply);
}


QCompleter *MessageConfig::createIDNameCompleter(
        QObject *parent
        ) const
{
    return msgIDMapping->createIDNameCompleter(parent);
}

QCompleter *MessageConfig::createCodeNameCompleter(
        QObject *parent
        ) const
{
    return msgCodeMapping->createCodeNameCompleter(parent);
}

