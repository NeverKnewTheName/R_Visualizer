#ifndef IFILTER_H
#define IFILTER_H

#include "IMsg.h"

class IFilter
{
public:
    virtual ~IFilter();

    virtual bool filterMessage(const IMsg &msgToFilter) const = 0;

    virtual void enableFilter(const bool enable) = 0;
    virtual bool isEnabled() const = 0;

    virtual void invertFilter(const bool invert) = 0;
    virtual void isInverted() const = 0;
};

#endif /* IFILTER_H */
