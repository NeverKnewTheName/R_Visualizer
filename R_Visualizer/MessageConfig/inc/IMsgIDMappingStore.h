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

#include "MsgIDType.h"
#include "IMsgIDRep.h"

#include "IFileParsable.h"

/**
 * \brief The IMsgIDMappingStore interface
 */
class IMsgIDMappingStore : public IFileParsable
{
public:
    virtual ~IMsgIDMappingStore(){}

    virtual MsgIDType getMsgIDToAlias(const QString &alias) const = 0;
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const = 0;
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    /* virtual QCompleter *createIDAliasCompleter(QObject *parent = Q_NULLPTR) = 0; */

    /* virtual const IMsgIDRep &getMsgIDRepToMsgID(
     * const MsgIDType &msgID
     * ) const = 0; */
    virtual IMsgIDRep &getMsgIDRepToMsgID(const MsgIDType &msgID) = 0;

    virtual bool contains(const MsgIDType &msgID) const = 0;
    virtual bool contains(const IMsgIDRep &msgIDRep) const = 0;

    virtual IMsgIDRep &addMsgIDMapping(
            const MsgIDType &msgID,
            const IMsgIDRep &msgIDRepToAppend
            ) = 0;
    virtual void removeMsgIDMapping(const MsgIDType &relatedMsgID) = 0;

    virtual void clear() = 0;

};

#endif /* IMSGIDMAPPINGSTORE_H */
