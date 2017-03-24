/**
 * \file IMsgIDMappingModel.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides an interface for models storing message id mappings
 */
#ifndef IMSGIDMAPPINGMODEL_H
#define IMSGIDMAPPINGMODEL_H

#include <QString>
#include <QColor>
#include <QCompleter>

#include "msg.h"
#include "IMsgIDRep.h"

/**
 * \brief The IMsgIDMappingModel interface
 */
class IMsgIDMappingModel
{
public:
    virtual ~IMsgIDMappingModel(){}

    virtual IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType msgID) const = 0;
    virtual IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType msgID) = 0;

    /* virtual QString getAliasToMsgID(const MsgIDType msgID) const = 0; */
    /* virtual MsgIDType getMsgIDToAlias(const QString &alias) const = 0; */
    /* virtual QColor getColorToMsgID(const MsgIDType msgID) const = 0; */
    /* virtual QColor getColorToAlias(const QString &alias) const = 0; */

    virtual bool contains(const MsgIDType msgID) const = 0;
    virtual bool contains(const IMsgIDRep &msgIDRep) const = 0;

    virtual void appendMsgIDMapping(const IMsgIDRep &msgIDRepToAppend) = 0;
    virtual void removeMsgIDMapping(const MsgIDType relatedMsgID) = 0;

    virtual void clear() = 0;

signals:
    virtual void sgnl_MappingAdded(const MsgIDType relatedID) = 0;
    virtual void sgnl_MappingUpdated(const MsgIDType relatedID) = 0;
    virtual void sgnl_MappingRemoved(const MsgIDType relatedID) = 0;

    virtual void sgnl_MsgIDRepAdded(const IMsgIDRep &newMsgIDRep) = 0;
    virtual void sgnl_MsgIDRepUpdated(const IMsgIDRep &updatedMsgIDRep) = 0;
    virtual void sgnl_MsgIDRepRemoved(const MsgIDType relatedID) = 0;
};

#endif /* IMSGIDMAPPINGMODEL_H */
