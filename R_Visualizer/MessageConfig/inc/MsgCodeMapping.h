#ifndef MSGCODEMAPPING_H
#define MSGCODEMAPPING_H

#include "IMsgCodeMapping.h"

class FileParser;

class MsgCodeMapping : public IMsgCodeMapping
{
public:
    MsgCodeMapping();
    virtual ~MsgCodeMapping();

    IPrettyMsgUniqPtr<IMsg> prettifyMsg(
            IPrettyMsgUniqPtr<IMsg> msgToPrettify
            ) const;

    IPrettyMsgUniqPtr<ITimestampedMsg> prettifyMsg(
            IPrettyMsgUniqPtr<ITimestampedMsg> timestampedMsgToPrettify
            ) const;

    QCompleter *createCodeNameCompleter(
            QObject *parent = Q_NULLPTR
            ) const;

    void accept(FileParser *visitor);

private:
    

};

#endif /* MSGCODEMAPPING_H */
