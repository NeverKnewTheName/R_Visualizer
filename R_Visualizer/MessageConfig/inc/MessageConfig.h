#ifndef MESSAGECONFIG_H
#define MESSAGECONFIG_H

#include "IMessageConfig.h"
#include "IMsg.h"
#include "IPrettyMsg.h"

class MessageConfig : public IMessageConfig
{
public:
    MessageConfig();
    virtual ~MessageConfig();

    template<class BaseClass>
    IPrettyMsgUniqPtr<BaseClass> prettifyMsg(const IMsg &msgToPrettify) const;
private:
    

};

#endif /* MESSAGECONFIG_H */
