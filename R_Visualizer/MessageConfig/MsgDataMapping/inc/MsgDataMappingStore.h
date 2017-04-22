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
#include "IMsgDataMapping.h"
#include "MsgDataMapping.h"

class FileParser;

/**
 * @brief The MsgDataMappingStore
 */
class MsgDataMappingStore : public IMsgDataMappingStore
{
public:
    MsgDataMappingStore();
    virtual ~MsgDataMappingStore();

    virtual QString parseMsgDataToString(const IMsg &msg) const;
    virtual QColor parseMsgDataToColor(const IMsg &msg) const;

    virtual IMsgDataMapping &getMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    virtual bool contains(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const;

    virtual bool contains(
            const IMsgDataMapping &msgDataMapping
            ) const;

    virtual IMsgDataMapping &addMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const IMsgDataMapping &msgDataMappingToAdd = MsgDataMapping()
            );

    virtual void removeMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    virtual void clear();

    void accept(FileParser *visitor);
private:
    QHash<MsgIDType,QHash<MsgCodeType, MsgDataMapping>> msgDataMappingStore;
};

#endif /* MSGDATAMAPPINGSTORE_H */
