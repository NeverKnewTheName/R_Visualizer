/**
 * @file IMsgCodeMappingStore.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Provides an interface for message code mapping stores
 */
#ifndef IMSGCODEMAPPINGSTORE_H
#define IMSGCODEMAPPINGSTORE_H

#include <QString>
#include <QColor>

#include "MsgCodeType.h"
#include "IMsgCodeRep.h"

#include "IFileParsable.h"

/**
 * @brief The IMsgCodeMappingStore interface
 */
class IMsgCodeMappingStore : public IFileParsable
{
public:
    virtual ~IMsgCodeMappingStore();

    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const = 0;
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const = 0;
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const = 0;
    virtual QColor getColorToAlias(const QString &alias) const = 0;

    virtual IMsgCodeRep &getMsgCodeRepToMsgCode(
            const MsgCodeType &msgCode
            ) const = 0;

    virtual IMsgCodeRep &getMsgCodeRepToMsgCode(
            const MsgCodeType &msgCode
            ) = 0;

    virtual bool contains(const MsgCodeType &msgCode) const = 0;
    virtual bool contains(const IMsgCodeRep &msgCodeRep) const = 0;

    virtual void addMsgCodeMapping(const IMsgCodeRep &msgCodeRepToAdd) = 0;
    virtual void removeMsgCodeMapping(const MsgCodeType &relatedMsgCode) = 0;

    virtual void clear() = 0;
};

#endif /* IMSGCODEMAPPINGSTORE_H */
