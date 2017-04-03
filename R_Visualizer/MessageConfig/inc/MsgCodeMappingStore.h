#ifndef MSGCODEMAPPINGSTORE_H
#define MSGCODEMAPPINGSTORE_H

#include "IMsgCodeMappingStore.h"
#include "IMsgCodeRep.h"
#include "MsgCodeType.h"

#include <QHash>
class FileParser;

class MsgCodeMappingStore : public IMsgCodeMappingStore
{
public:
    MsgCodeMappingStore();
    virtual ~MsgCodeMappingStore();

    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const;
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToAlias(const QString &alias) const;

    virtual IMsgCodeRep &getMsgCodeRepToMsgCode(
            const MsgCodeType &msgCode
            ) const;

    virtual IMsgCodeRep &getMsgCodeRepToMsgCode(
            const MsgCodeType &msgCode
            );

    virtual bool contains(const MsgCodeType &msgCode) const;
    virtual bool contains(const IMsgCodeRep &msgCodeRep) const;

    virtual void addMsgCodeMapping(const IMsgCodeRep &msgCodeRepToAdd);
    virtual void removeMsgCodeMapping(const MsgCodeType &relatedMsgCode);

    virtual void clear();

    virtual void accept(FileParser *visitor);

private:
    QHash<MsgCodeType, IMsgCodeRepUniqPtr> msgCodeRepStore;
};

#endif /* MSGCODEMAPPINGSTORE_H */
