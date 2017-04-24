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

class ITimestamp;

/**
 * @brief The #ITimestampedMsgFilter interface
 */
class ITimestampedMsgFilter : public IFilter
{
    Q_OBJECT
public:
    ITimestampedMsgFilter(QObject *parent = Q_NULLPTR) : IFilter(parent){}
    virtual ~ITimestampedMsgFilter(){}

    /**
     * @brief Filters an #ITimestamp according to the current filter
     * configuration and filter criteria
     */
    virtual bool filterTimestamp(
            const ITimestamp &timestampToFilter
            ) const = 0;

signals:
    void sgnl_TimestampFilterChanged(
            const ITimestampedMsgFilter &filterThatHasChanged
            );

public slots:
};

#endif /* ITIMESTAMPEDMSGFILTER_H */
