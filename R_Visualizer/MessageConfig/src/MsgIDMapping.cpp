#include "MsgIDMapping.h"

MsgIDMapping::MsgIDMapping()
{
}

MsgIDMapping::~MsgIDMapping()
{
}


IPrettyMsgUniqPtr<IMsg> MsgIDMapping::prettifyMsg(
        IPrettyMsgUniqPtr<IMsg> msgToPrettify
        ) const
{
    //ToDO
    msgToPrettify->setMsgIDPlainTextAlias("SomeIDALias");
    msgToPrettify->setMsgIDColorRepresentation(QColor(Qt::blue));
    return std::move(msgToPrettify);
}

IPrettyMsgUniqPtr<ITimestampedMsg> MsgIDMapping::prettifyMsg(
        IPrettyMsgUniqPtr<ITimestampedMsg> timestampedMsgToPrettify
        ) const
{
    //ToDO
    msgToPrettify->setMsgIDPlainTextAlias("SomeTimestampIDALias");
    msgToPrettify->setMsgIDColorRepresentation(QColor(Qt::blue).darker());
    return std::move(msgToPrettify);
}

QCompleter *MsgIDMapping::createIDNameCompleter(QObject *parent) const
{
    return QCompleter();
}

void MsgIDMapping::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
