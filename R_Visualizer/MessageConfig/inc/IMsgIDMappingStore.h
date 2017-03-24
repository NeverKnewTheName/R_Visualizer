/**
 * \file IMsgIDMappingStore.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for message id mapping stores
 */
#ifndef IMSGIDMAPPINGSTORE_H
#define IMSGIDMAPPINGSTORE_H

#include <QString>
#include <QColor>

#include "IMsgIDRep.h"

/**
 * \brief The IMsgIDMappingStore interface
 */
class IMsgIDMappingStore
{
public:
    virtual ~IMsgIDMappingStore(){}

    /* virtual MsgIDType getMsgIDToName(const QString &name) const = 0; */
    /* virtual QString getNameToMsgID(const MsgIDType msgID) const = 0; */
    /* virtual QColor getColorToMsgID(const MsgIDType msgID) const = 0; */
    /* virtual QColor getColorToName(const QString &name) const = 0; */

    virtual IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType msgID) const = 0;
    virtual IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType msgID) = 0;

    virtual bool contains(const MsgIDType msgID) const = 0;
    virtual bool contains(const IMsgIDRep &msgIDRep) const = 0;

    virtual void addMsgIDMapping(const IMsgIDRep &msgIDRepToAppend) = 0;
    virtual void removeMsgIDMapping(const MsgIDType relatedMsgID) = 0;

    virtual void clear() = 0;
};

#endif /* IMSGIDMAPPINGSTORE_H */
