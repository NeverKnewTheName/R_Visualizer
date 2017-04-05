/**
 * @file ITimestampedMsgFilter.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Provides an interface for timestamped message filters
 */
#ifndef ITIMESTAMPEDMSGFILTER_H
#define ITIMESTAMPEDMSGFILTER_H

#include "IFilter.h"
#include "ITimestampedMsg.h"

/**
 * @brief The #ITimestampedMsgFilter interface
 */
class ITimestampedMsgFilter : public IFilter
{
public:
    virtual ~ITimestampedMsgFilter(){}

    /**
     * @brief Filters an #ITimestampedMsg according to the current filter
     * configuration and filter criteria
     */
    virtual bool filterMessage(const ITimestampedMsg &msgToFilter) const = 0;
};

#endif /* ITIMESTAMPEDMSGFILTER_H */
