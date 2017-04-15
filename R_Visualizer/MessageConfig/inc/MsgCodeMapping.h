#ifndef MSGCODEMAPPING_H
#define MSGCODEMAPPING_H

#include "IMsgCodeMapping.h"

class FileParser;
class IMsgCodeMappingStore;

class MsgCodeMapping : public IMsgCodeMapping
{
public:
    MsgCodeMapping(IMsgCodeMappingStore *msgCodeMappingStore);
    virtual ~MsgCodeMapping();

    virtual MsgCodeType getMsgCodeToAlias(const QString &alias) const;
    virtual QString getAliasToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToMsgCode(const MsgCodeType &msgCode) const;
    virtual QColor getColorToAlias(const QString &alias) const;

    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    virtual void accept(FileParser *visitor);

private:
    IMsgCodeMappingStore *msgCodeMappingStore;

};

#endif /* MSGCODEMAPPING_H */
