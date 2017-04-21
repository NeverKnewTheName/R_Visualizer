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

class ITimestampedMsg;

/**
 * @brief The #ITimestampedMsgFilter interface
 */
class ITimestampedMsgFilter : public IFilter
{
public:
    ITimestampedMsgFilter(QObject *parent = Q_NULLPTR) : IFilter(parent){}
    virtual ~ITimestampedMsgFilter(){}

    /**
     * @brief Filters an #ITimestampedMsg according to the current filter
     * configuration and filter criteria
     */
    virtual bool filterMessage(const ITimestampedMsg &msgToFilter) const = 0;
};

#endif /* ITIMESTAMPEDMSGFILTER_H */
