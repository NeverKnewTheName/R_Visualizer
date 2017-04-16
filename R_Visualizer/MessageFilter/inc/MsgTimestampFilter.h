/**
 * @file MsgTimestampFilter.h
 * @author Christian Neuberger
 * @date 2017-04-03
 * 
 * @brief Filters #ITimestampedMsg by a timespan defined by two timestamps
 */
#ifndef MSGTIMESTAMPFILTER_H
#define MSGTIMESTAMPFILTER_H

#include <QDateTime>

#include "IMsg.h"
#include "ITimestampedMsgFilter.h"

/**
 * @brief The MsgTimestampFilter
 */
class MsgTimestampFilter : public QObject, public ITimestampedMsgFilter
{
    Q_OBJECT
public:
    explicit MsgTimestampFilter(QObject *parent = 0);
    virtual ~MsgTimestampFilter();

    /**
     * @brief Matches the passed #ITImestampedMsg against the current filter
     * state and configuration and returns the result
     * 
     * If the filter is not enabled, this function always returns true
     * 
     * @returns bool filter result
     * @retval true The timestamp of the passed #ITimestampedMsg is inside of
     *  the filter's range
     * @retval false The timestamp of the passed #ITimestampedMsg is outside of
     *  the filter's range
     */
    virtual bool filterMessage(const ITimestampedMsg &msgToFilter) const;

    void enableFilter(const bool enable);
    bool isFilterEnabled() const;

    void invertFilter(const bool invert);
    bool isFilterInverted() const;

    void setTimestampFrom(const QDateTime &timestampFrom);
    QDateTime getTimestampFrom() const;
    void setTimestampTo(const QDateTime &timestampTo);
    QDateTime getTimestampTo() const;

signals:
    void sgnl_filterEnabled(const bool enabled);
    void sgnl_filterInverted(const bool inverted);
    void sngl_filterChanged();

public slots:
    void slt_enableFilter(const bool enable);
    void slt_invertFilter(const bool invert);

    void slt_changeTimestampFrom(const QDateTime &newTimestampFrom);
    void slt_changeTimestampTo(const QDateTime &newTimestampTo);

private:
    virtual bool greaterThanTimestampFrom(const QDateTime &timestamp) const;
    virtual bool lowerThanTimestampTo(const QDateTime &timestamp) const;
    bool applyInversion(const bool intermediateFilterResult) const;

private:
    QDateTime timestampFrom;
    QDateTime timestampTo;

    bool isEnabled;
    bool isInverted;
};

#endif /* MSGTIMESTAMPFILTER_H */
