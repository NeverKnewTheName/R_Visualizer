#include "MsgDataMapping.h"

MsgDataMapping::MsgDataMapping()
{
}

MsgDataMapping::~MsgDataMapping()
{
}

void MsgDataMapping::prettifyMsg(
        IPrettyMsg &msgToPrettify
        ) const
{
    //ToDO
    const MsgDataType &msgData = msgToPrettify.getMsgData();

    /* msgDataMappingStore-> */
}

void MsgDataMapping::accept(FileParser *visitor)
{
    visitor->accept(*this);
}
