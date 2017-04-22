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

#include "Msg.h"
#include "IMsgIDMapping.h"
#include "IFileParsable.h"

/**
 * \brief The IMsgIDMappingModel interface
 */
class IMsgIDMappingModel : public IFileParsable
{
public:
    virtual ~IMsgIDMappingModel(){}

    /* virtual IMsgIDMapping &getMsgIDMappingToMsgID(const MsgIDType &msgID) const = 0; */
    virtual IMsgIDMapping &getMsgIDMappingToMsgID(const MsgIDType &msgID) = 0;

    /* virtual QString getAliasToMsgID(const MsgIDType msgID) const = 0; */
    /* virtual MsgIDType getMsgIDToAlias(const QString &alias) const = 0; */
    /* virtual QColor getColorToMsgID(const MsgIDType msgID) const = 0; */
    /* virtual QColor getColorToAlias(const QString &alias) const = 0; */

    virtual bool contains(const MsgIDType &msgID) const = 0;
    virtual bool contains(const IMsgIDMapping &msgIDMapping) const = 0;

    virtual void appendMsgIDMapping(const IMsgIDMapping &msgIDMappingToAppend) = 0;
    virtual void removeMsgIDMapping(const MsgIDType &relatedMsgID) = 0;

    virtual void clear() = 0;

signals:
    virtual void sgnl_MappingAdded(const MsgIDType &relatedID) = 0;
    virtual void sgnl_MappingUpdated(const MsgIDType &relatedID) = 0;
    virtual void sgnl_MappingRemoved(const MsgIDType &relatedID) = 0;

    virtual void sgnl_MsgIDMappingAdded(const IMsgIDMapping &newMsgIDMapping) = 0;
    virtual void sgnl_MsgIDMappingUpdated(const IMsgIDMapping &updatedMsgIDMapping) = 0;
    virtual void sgnl_MsgIDMappingRemoved(const MsgIDType &relatedID) = 0;
};

#endif /* IMSGIDMAPPINGMODEL_H */
