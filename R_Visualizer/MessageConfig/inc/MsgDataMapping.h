#ifndef MSGDATAMAPPING_H
#define MSGDATAMAPPING_H

#include "IMsgMapping.h"

class FileParser;

class MsgDataMapping : public IMsgDataMapping
{
public:
    MsgDataMapping();
    virtual ~MsgDataMapping();

    IPrettyMsgUniqPtr<IMsg> prettifyMsg(
            IPrettyMsgUniqPtr<IMsg> msgToPrettify
            ) const;
    IPrettyMsgUniqPtr<ITimestampedMsg> prettifyMsg(
            IPrettyMsgUniqPtr<ITimestampedMsg> timestampedMsgToPrettify
            ) const;

    void accept(FileParser *visitor);
private:
    

};

#endif /* MSGDATAMAPPING_H */
