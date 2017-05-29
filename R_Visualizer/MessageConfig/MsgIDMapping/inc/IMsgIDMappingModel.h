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

    virtual IMsgIDMapping &getMsgIDMappingToMsgID(const MsgIDType &msgID) = 0;

    virtual bool contains(const MsgIDType &msgID) const = 0;
    virtual bool contains(const IMsgIDMapping &msgIDMapping) const = 0;

    virtual void appendMsgIDMapping(const IMsgIDMapping &msgIDMappingToAppend) = 0;
    virtual void removeMsgIDMapping(const MsgIDType &relatedMsgID) = 0;

    virtual void clear() = 0;

    /* virtual QCompleter *createIDNameCompleter(
     * QObject *parent = Q_NULLPTR
     * ) const = 0; */

};

#endif /* IMSGIDMAPPINGMODEL_H */
