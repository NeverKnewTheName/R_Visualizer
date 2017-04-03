#ifndef MSGIDMAPPING_H
#define MSGIDMAPPING_H

#include "IMsgIDMapping.h"

#include "IPrettyMsg.h"
#include "IMsg.h"
#include "ITimestampedMsg.h"

class IMsgIDMappingStore;

class MsgIDMapping : public IMsgIDMapping
{
public:
    MsgIDMapping(IMsgIDMappingStore *msgIDMappingStore);
    virtual ~MsgIDMapping();

    virtual MsgIDType getMsgIDToAlias(const QString &alias) const;
    virtual QString getAliasToMsgID(const MsgIDType &msgID) const;
    virtual QColor getColorToMsgID(const MsgIDType &msgID) const;
    virtual QColor getColorToAlias(const QString &alias) const;

    virtual IPrettyMsgUniqPtr<IMsg> prettifyMsg(
            IPrettyMsgUniqPtr<IMsg> msgToPrettify
            ) const;
    virtual IPrettyMsgUniqPtr<ITimestampedMsg> prettifyMsg(
            IPrettyMsgUniqPtr<ITimestampedMsg> timestampedMsgToPrettify
            ) const;

    /* QCompleter *createIDaliasCompleter(QObject *parent = Q_NULLPTR) const; */

    virtual void accept(FileParser *visitor);

private:
    IMsgIDMappingStore *msgIDMappingStore;

};

#endif /* MSGIDMAPPING_H */
