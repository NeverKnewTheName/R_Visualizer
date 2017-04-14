#ifndef MSGDATAMAPPING_H
#define MSGDATAMAPPING_H

#include "IMsgMapping.h"

class FileParser;

class MsgDataMapping : public IMsgDataMapping
{
public:
    MsgDataMapping();
    virtual ~MsgDataMapping();

    virtual IPrettyMsg &prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    void accept(FileParser *visitor);
private:
    

};

#endif /* MSGDATAMAPPING_H */
