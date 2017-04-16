/**
 * @file MsgDataMappingStore.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The default MsgData Mapping store
 */
#ifndef MSGDATAMAPPINGSTORE_H
#define MSGDATAMAPPINGSTORE_H

#include "IMsgDataMappingStore.h"

#include <QHash>

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "IMsgDataRep.h"
#include "MsgDataRep.h"

class FileParser;

/**
 * @brief The MsgDataMappingStore
 */
class MsgDataMappingStore : public IMsgDataMappingStore
{
public:
    MsgDataMappingStore();
    virtual ~MsgDataMappingStore();

    virtual QString parseMsgDataToString(const IMsg &msg);
    virtual QColor parseMsgDataToColor(const IMsg &msg);

    virtual IMsgDataRep &getMsgDataRep(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    virtual bool contains(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const;

    virtual bool contains(
            const IMsgDataRep &msgDataRep
            ) const;

    virtual IMsgDataRep &addMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const IMsgDataRep &msgDataRepToAdd = MsgDataRep()
            );

    virtual void removeMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    virtual void clear();

    void accept(FileParser *visitor);
private:
    QHash<MsgIDType,QHash<MsgCodeType, MsgDataRep>> msgDataRepStore;
};

#endif /* MSGDATAMAPPINGSTORE_H */
