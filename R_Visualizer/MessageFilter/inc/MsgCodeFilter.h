#ifndef MSGCODEFILTER_H
#define MSGCODEFILTER_H

#include "IMsg.h"
#include "IFilter.h"

#include "MsgCodeType.h"

class MsgCodeFilter : public IFilter
{
public:
    MsgCodeFilter();
    virtual ~MsgCodeFilter();

    virtual bool filterMessage(const IMsg &msgToFilter) const;

    virtual void enableFilter(const bool enable);
    virtual bool isEnabled() const;

    virtual void invertFilter(const bool invert);
    virtual bool isInverted() const;

    void addMsgCodeToFilter(const MsgCodeType &msgCodeToAdd);
    void removeMsgCodeFromFilter(const MsgCodeType &msgCodeToRemove);

private:
    QVector<MsgCodeType> msgCodeFilterStore;

    bool isEnabled;
    bool isInverted;
};

#endif /* MSGCODEFILTER_H */
