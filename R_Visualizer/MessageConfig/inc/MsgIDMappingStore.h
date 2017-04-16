/**
 * \file MsgIDMappingStore.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief A Store for message id mappings
 */
#ifndef MSGIDMAPPINGSTORE_H
#define MSGIDMAPPINGSTORE_H

#include "IMsgIDMappingStore.h"
#include "MsgIDRep.h"
#include "MsgIDType.h"

#include <QHash>

class FileParser;

/**
 * @brief The MsgIDMappingStore
 */
class MsgIDMappingStore : public IMsgIDMappingStore
{
public:
    MsgIDMappingStore();
    virtual ~MsgIDMappingStore();

    virtual MsgIDType getMsgIDToAlias(const QString &alias) const;
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const;
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const;
    virtual QColor getColorToAlias(const QString &alias) const;

    /* const IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType &msgID) const; */
    virtual IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType &msgID);

    virtual bool contains(const MsgIDType &msgID) const;
    virtual bool contains(const IMsgIDRep &msgIDRep) const;

    virtual IMsgIDRep &addMsgIDMapping(
            const MsgIDType &msgID,
            const IMsgIDRep &msgIDRepToAdd = MsgIDRep()
            );
    virtual void removeMsgIDMapping(const MsgIDType &relatedMsgID);

    virtual void clear();

    virtual void accept(FileParser *visitor);

private:
    QHash<MsgIDType, MsgIDRep> msgIDRepStore;
};

#endif /* MSGIDMAPPINGSTORE_H */
