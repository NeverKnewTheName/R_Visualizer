/**
 * @file MsgCodeMappingStore.h
 * @author Christian Neuberger
 * @date 2017-04-16
 *
 * @brief A store for message code mappings
 */
#ifndef MSGCODEMAPPINGSTORE_H
#define MSGCODEMAPPINGSTORE_H

#include "IMsgCodeMappingStore.h"
#include "IMsgCodeRep.h"
#include "MsgCodeRep.h"
#include "MsgCodeType.h"

#include <QHash>

class FileParser;

/**
 * @brief The MsgCodeMappingStore
 */
class MsgCodeMappingStore : public IMsgCodeMappingStore
{
public:
    MsgCodeMappingStore();
    virtual ~MsgCodeMappingStore();

    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const;
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToAlias(const QString &alias) const;

    /* virtual IMsgCodeRep &getMsgCodeRepToMsgCode( */
    /*         const MsgCodeType &msgCode */
    /*         ) const; */

    virtual IMsgCodeRep &getMsgCodeRepToMsgCode(
            const MsgCodeType &msgCode
            );

    virtual bool contains(const MsgCodeType &msgCode) const;
    virtual bool contains(const IMsgCodeRep &msgCodeRep) const;

    virtual IMsgCodeRep &addMsgCodeMapping(
            const MsgCodeType &msgCode,
            const IMsgCodeRep &msgCodeRepToAdd = MsgCodeRep()
            );
    virtual void removeMsgCodeMapping(const MsgCodeType &relatedMsgCode);

    virtual void clear();

    virtual void accept(FileParser *visitor);

private:
    QHash<MsgCodeType, MsgCodeRep> msgCodeRepStore;
};

#endif /* MSGCODEMAPPINGSTORE_H */
