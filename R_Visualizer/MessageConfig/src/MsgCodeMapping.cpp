#include "MsgCodeMapping.h"


MsgCodeMapping::MsgCodeMapping()
{
}

MsgCodeMapping::~MsgCodeMapping()
{
}

IPrettyMsgUniqPtr<IMsg> MsgCodeMapping::prettifyMsg(
       IPrettyMsgUniqPtr<IMsg> msgToPrettify
       ) const
{
    //ToDO
    msgToPrettify->setMsgCodePlainTextAlias("SomeCodeALias");
    msgToPrettify->setMsgCodeColorRepresentation(QColor(Qt::green));
    return std::move(msgToPrettify);
}

IPrettyMsgUniqPtr<ITimestampedMsg> MsgCodeMapping::prettifyMsg(
       IPrettyMsgUniqPtr<ITimestampedMsg> msgToPrettify
       ) const
{
    //ToDO
    msgToPrettify->setMsgCodePlainTextAlias("SomeTimestampCodeLias");
    msgToPrettify->setMsgCodeColorRepresentation(QColor(Qt::green).darker());
    return std::move(msgToPrettify);
}

QCompleter *createCodeNameCompleter(
        QObject *parent = Q_NULLPTR
        ) const
{
}
