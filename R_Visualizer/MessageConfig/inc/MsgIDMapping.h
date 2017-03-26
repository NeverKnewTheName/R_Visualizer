#ifndef MSGIDMAPPING_H
#define MSGIDMAPPING_H

#include "IMsgIDMapping.h"

#include "IPrettyMsg.h"
#include "IMsg.h"
#include "ITimestampedMsg.h"

class MsgIDMapping : public IMsgIDMapping
{
public:
    MsgIDMapping();
    virtual ~MsgIDMapping();

    IPrettyMsgUniqPtr<IMsg> prettifyMsg(
            IPrettyMsgUniqPtr<IMsg> msgToPrettify
            ) const;
    IPrettyMsgUniqPtr<ITimestampedMsg> prettifyMsg(
            IPrettyMsgUniqPtr<ITimestampedMsg> timestampedMsgToPrettify
            ) const;

    QCompleter *createIDNameCompleter(QObject *parent = Q_NULLPTR) const;

    void accept(FileParser *visitor);

private:
    

};

#endif /* MSGIDMAPPING_H */
