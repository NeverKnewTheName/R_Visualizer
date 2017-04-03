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
#include "IMsgIDRep.h"
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

    MsgIDType getMsgIDToAlias(const QString &alias) const;
    QString getAliasToMsgID(const MsgIDType &msgID) const;
    QColor getColorToMsgID(const MsgIDType &msgID) const;
    QColor getColorToAlias(const QString &alias) const;

    IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType &msgID) const;
    IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType &msgID);

    bool contains(const MsgIDType &msgID) const;
    bool contains(const IMsgIDRep &msgIDRep) const;

    void addMsgIDMapping(const IMsgIDRep &msgIDRepToAdd);
    void removeMsgIDMapping(const MsgIDType &relatedMsgID);

    void clear();

    void accept(FileParser *visitor);

private:
    QHash<MsgIDType, IMsgIDRepUniqPtr> msgIDRepStore;
};

#endif /* MSGIDMAPPINGSTORE_H */
