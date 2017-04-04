#ifndef MSGTIMESTAMPFILTER_H
#define MSGTIMESTAMPFILTER_H

#include <QDateTime>

#include "IMsg.h"
#include "IFilter.h"

class MsgTimestampFilter : public IFilter
{
public:
    MsgTimestampFilter();
    virtual ~MsgTimestampFilter();

    virtual bool filterMessage(const IMsg &msgToFilter) const;

    void enableFilter(const bool enable);
    bool isEnabled() const;

    void invertFilter(const bool invert);
    bool isInverted() const;

    void setTimestampFrom(const QDateTime &timestampFrom);
    QDateTime getTimestampFrom() const;
    void setTimestampTo(const QDateTime &timestampTo);
    QDateTime getTimestampTo() const;

private:
    virtual bool greaterThanTimestampFrom(const QDateTime &timestamp) const;
    virtual bool lowerThanTimestampTo(const QDateTime &timestamp) const;
    bool applyInversion(const bool intermediateFilterResult) const;


private:
    QDateTime timestampeFrom;
    QDateTime timestampTo;

    bool isEnabled;
    bool isInverted;
};

#endif /* MSGTIMESTAMPFILTER_H */
