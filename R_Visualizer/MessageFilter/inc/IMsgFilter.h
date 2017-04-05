/**
 * @file IMsgFilter.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Provides an interface for message filters
 */
#ifndef IMSGFILTER_H
#define IMSGFILTER_H

#include "IFilter.h"
#include "IMsg.h"

/**
 * @brief The #IMsgFilter interface
 */
class IMsgFilter : public IFilter
{
public:
    virtual ~IMsgFilter(){}

    /**
     * @brief Filters an #IMsg according to the current filter configuration and
     * filter criteria
     */
    virtual bool filterMessage(const IMsg &msgToFilter) const = 0;
};

#endif /* IFILTER_H */
