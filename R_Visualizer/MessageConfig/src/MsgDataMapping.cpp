#include "MsgDataMapping.h"

#include "MsgIDType.h"
#include "MsgCodeType.h"

MsgDataMapping::MsgDataMapping(IMsgDataMappingStore *msgDataMappingStore) :
    msgDataMappingStore(msgDataMappingStore)
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
    const MsgIDType &msgID = msgToPrettify.getMsgID();
    const MsgCodeType &msgCode = msgToPrettify.getMsgCode();
    const MsgDataType &msgData = msgToPrettify.getMsgData();

    /* msgDataMappingStore-> */
}

void MsgDataMapping::accept(FileParser *visitor)
{
    msgDataMappingStore->accept(visitor);
}
