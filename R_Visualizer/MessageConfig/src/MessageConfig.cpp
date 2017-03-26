#include "MessageConfig.h"

#include "IMsgIDMapping.h"
#include "IMsgCodeMapping.h"
#include "IMsgDataMapping.h"

#include "fileparser.h"

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
        const IMsg &msgToPrettify
        ) const
{
    IPrettyMsgUniqPtr<IMsg> prettyMsg(msgToPrettify->cloneMsg());

    return std::move(prettyMsg);
}

IPrettyMsgUniqPtr<ITimestampedMsg> MessageConfig::prettifyMsg(
        const ITimestampedMsg &timestampedMsgToPrettify
        ) const
{
    IPrettyMsgUniqPtr<ITimestampedMsg> prettyMsg(TimestampedMsgToPrettify->cloneMsg());

    return std::move(prettyMsg);
}


QCompleter *MessageConfig::createIDNameCompleter(
        QObject *parent
        ) const
{
}

QCompleter *MessageConfig::createCodeNameCompleter(
        QObject *parent
        ) const
{
}

//ToTHINK DEPRECATED?
void MessageConfig::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

