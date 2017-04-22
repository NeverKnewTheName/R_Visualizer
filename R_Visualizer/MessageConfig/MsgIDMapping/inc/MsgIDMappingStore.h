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
#include "MsgIDMapping.h"
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

    /* const IMsgIDMapping &getMsgIDMappingToMsgID(const MsgIDType &msgID) const; */
    virtual IMsgIDMapping &getMsgIDMappingToMsgID(const MsgIDType &msgID);

    virtual bool contains(const MsgIDType &msgID) const;
    virtual bool contains(const IMsgIDMapping &msgIDMapping) const;

    virtual IMsgIDMapping &addMsgIDMapping(
            const MsgIDType &msgID,
            const IMsgIDMapping &msgIDMappingToAdd = MsgIDMapping()
            );
    virtual void removeMsgIDMapping(const MsgIDType &relatedMsgID);

    virtual void clear();

    virtual void accept(FileParser *visitor);

private:
    QHash<MsgIDType, MsgIDMapping> msgIDMappingStore;
};

#endif /* MSGIDMAPPINGSTORE_H */
