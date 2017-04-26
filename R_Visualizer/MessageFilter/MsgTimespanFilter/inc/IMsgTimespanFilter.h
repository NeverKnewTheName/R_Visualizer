/**
 * @file IMsgTimespanFilter.h
 * @author Christian Neuberger
 * @date 2017-04-26
 * 
 * @brief Interface for Message Timstamp Filters
 */
#ifndef IMSGTIMESTAMPFILTER_H
#define IMSGTIMESTAMPFILTER_H

#include "ITimestampedMsgFilter.h"

/**
 * @defgroup MsgTimespanFilterGroup Message Timespan Filter
 * @ingroup MsgTimestampFilterGroup
 * 
 * @{
 */

/**
 * @brief The IMsgTimespanFilter interface
 */
class IMsgTimespanFilter : public ITimestampedMsgFilter
{
    Q_OBJECT
public:
    IMsgTimespanFilter(
            QObject *parent = Q_NULLPTR
            ) :
        ITimestampedMsgFilter(parent)
    {}
    virtual ~IMsgTimespanFilter(){}

    virtual void setTimestampFrom(const QDateTime &timestampFrom) = 0;
    virtual QDateTime getTimestampFrom() const = 0;
    virtual void setTimestampTo(const QDateTime &timestampTo) = 0;
    virtual QDateTime getTimestampTo() const = 0;

    virtual void enableTimestampFilterFrom(const bool enabled) = 0;
    virtual bool isTimestampFilterFromEnabled() const = 0;
    virtual void enableTimestampFilterTo(const bool enabled) = 0;
    virtual bool isTimestampFilterToEnabled() const = 0;

signals:
    void sgnl_TimestampFromChanged(const QDateTime &newTimestampFrom);
    void sgnl_TimestampToChanged(const QDateTime &newTimestampTo);

public slots:
    virtual void slt_changeTimestampFrom(const QDateTime &newTimestampFrom)
    {
        setTimestampFrom(newTimestampFrom);
    }

    virtual void slt_changeTimestampTo(const QDateTime &newTimestampTo)
    {
        setTimestampTo(newTimestampTo);
    }

    virtual void slt_enableTimestampFrom(const bool enabled)
    {
        enableTimestampFilterFrom(enabled);
    }
    virtual void slt_enableTimestampTo(const bool enabled)
    {
        enableTimestampFilterTo(enabled);
    }

};

/**
 * @}
 */

#endif /* IMSGTIMESTAMPFILTER_H */
