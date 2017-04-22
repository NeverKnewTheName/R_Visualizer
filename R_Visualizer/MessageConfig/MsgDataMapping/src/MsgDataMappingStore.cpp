#include "MsgDataMappingStore.h"

#include "fileparser.h"

MsgDataMappingStore::MsgDataMappingStore()
{
}

MsgDataMappingStore::~MsgDataMappingStore()
{
}

QString MsgDataMappingStore::parseMsgDataToString(const IMsg &msg) const
{

}

QColor MsgDataMappingStore::parseMsgDataToColor(const IMsg &msg) const
{
}

IMsgDataMapping &MsgDataMappingStore::getMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    //ToDO...
    return msgDataMappingStore[msgID][msgCode];
}

bool MsgDataMappingStore::contains(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        ) const
{
    if(msgDataMappingStore.contains(msgID))
    {
        /*
         * ToDO FIX IT!
         * This operation is costly because we are in a const function
         * hence the const operator[] function is called which returns a
         * value... so basically we copy the whole msgID hash just to check if
         * it contains a msgCode.. THIS IS STUPID... 
         * 
         * Fix: merge MsgID and MsgCode into one hash key
         */
        return msgDataMappingStore[msgID].contains(msgCode);
    }
    else
    {
        return false;
    }
}

bool MsgDataMappingStore::contains(
        const IMsgDataMapping &msgDataMapping
    ) const
{
    /*
     * ToDO See comment above!
     */
    return false;
}

IMsgDataMapping &MsgDataMappingStore::addMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode,
        const IMsgDataMapping &msgDataMapping
        )
{
    //ToDO...
    msgDataMappingStore[msgID].insert(
            msgCode,dynamic_cast<const MsgDataMapping &>(msgDataMapping)
            );

}

void MsgDataMappingStore::removeMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    //ToDO...
    msgDataMappingStore[msgID].remove(msgCode);
}

void MsgDataMappingStore::clear()
{
    msgDataMappingStore.clear();
}

void MsgDataMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
