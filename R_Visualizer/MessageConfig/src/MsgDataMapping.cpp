#include "MsgDataMapping.h"

MsgDataMapping::MsgDataMapping()
{
}

MsgDataMapping::~MsgDataMapping()
{
}

IPrettyMsgUniqPtr<IMsg> MsgDataMapping::prettifyMsg(
        IPrettyMsgUniqPtr<IMsg> msgToPrettify
        ) const
{
    //ToDO
    return std::move(msgToPrettify);
}

IPrettyMsgUniqPtr<ITimestampedMsg> MsgDataMapping::prettifyMsg(
        IPrettyMsgUniqPtr<ITimestampedMsg> timestampedMsgToPrettify
        ) const
{
    //ToDO
    return std::move(msgToPrettify);
}

void MsgDataMapping::accept(FileParser *visitor)
{
    visitor->accept(*this);
}
