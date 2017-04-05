#ifndef ITIMESTAMPEDMSGFILTER_H
#define ITIMESTAMPEDMSGFILTER_H

#include "IFilter.h"
#include "ITimestampedMsg.h"

class ITimestampedMsgFilter : public IFilter
{
public:
    virtual ~ITimestampedMsgFilter(){}

    virtual bool filterMessage(const ITimestampedMsg &msgToFilter) const = 0;
};

#endif /* ITIMESTAMPEDMSGFILTER_H */
