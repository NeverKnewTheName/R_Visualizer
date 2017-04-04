#ifndef MSGIDFILTER_H
#define MSGIDFILTER_H

#include "IMsg.h"
#include "IFilter.h"

#include "MsgIDType.h"

class MsgIDFilter : public IFilter
{
public:
    MsgIDFilter();
    virtual ~MsgIDFilter();

    virtual bool filterMessage(const IMsg &msgToFilter) const;

    virtual void enableFilter(const bool enable);
    virtual bool isEnabled() const;

    virtual void invertFilter(const bool invert);
    virtual bool isInverted() const;

    void addMsgIDToFilter(const MsgIDType &msgIDToAdd);
    void removeMsgIDFromFilter(const MsgIDType &msgIDToRemove);

private:
    QVector<MsgIDType> msgIDFilterStore;

    bool isEnabled;
    bool isInverted;
};

#endif /* MSGIDFILTER_H */
