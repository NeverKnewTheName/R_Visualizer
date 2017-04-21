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

IMsgDataRep &MsgDataMappingStore::getMsgDataRep(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    //ToDO...
    return msgDataRepStore[msgID][msgCode];
}

bool MsgDataMappingStore::contains(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        ) const
{
    if(msgDataRepStore.contains(msgID))
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
        return msgDataRepStore[msgID].contains(msgCode);
    }
    else
    {
        return false;
    }
}

bool MsgDataMappingStore::contains(
        const IMsgDataRep &msgDataRep
    ) const
{
    /*
     * ToDO See comment above!
     */
    return false;
}

IMsgDataRep &MsgDataMappingStore::addMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode,
        const IMsgDataRep &msgDataRep
        )
{
    //ToDO...
    msgDataRepStore[msgID].insert(
            msgCode,dynamic_cast<const MsgDataRep &>(msgDataRep)
            );

}

void MsgDataMappingStore::removeMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    //ToDO...
    msgDataRepStore[msgID].remove(msgCode);
}

void MsgDataMappingStore::clear()
{
    msgDataRepStore.clear();
}

void MsgDataMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}
