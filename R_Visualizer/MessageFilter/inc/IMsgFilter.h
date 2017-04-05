#ifndef IMSGFILTER_H
#define IMSGFILTER_H

#include "IFilter.h"
#include "IMsg.h"

class IMsgFilter : public IFilter
{
public:
    virtual ~IMsgFilter(){}

    virtual bool filterMessage(const IMsg &msgToFilter) const = 0;
};

#endif /* IFILTER_H */
