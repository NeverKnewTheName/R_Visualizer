#include "MsgTimestampFilter.h"

#include "ITimestampedMsg.h"

MsgTimestampFilter::MsgTimestampFilter(QObject *parent) :
    QObject(parent)
{
}

MsgTimestampFilter::~MsgTimestampFilter()
{
}

bool MsgTimestampFilter::filterMessage(const ITimestampedMsg &msgToFilter) const
{
    bool filterResult = true;
    const QDateTime &msgTimestamp = msgToFilter.getTimestamp();

    filterResult &= greaterThanTimestampFrom(msgTimestamp);
    filterResult &= lowerThanTimestampTo(msgTimestamp);

    return applyInversion(filterResult);
}

void MsgTimestampFilter::enableFilter(const bool enable)
{
    this->isEnabled = enable;
}

bool MsgTimestampFilter::isFilterEnabled() const
{
    return isEnabled;
}

void MsgTimestampFilter::invertFilter(const bool invert)
{
    this->isInverted = invert;
}

bool MsgTimestampFilter::isFilterInverted() const
{
    return isInverted;
}

void MsgTimestampFilter::setTimestampFrom( const QDateTime &timestampFrom)
{
    this->timestampFrom = timestampFrom;
    if(this->timestampFrom > this->timestampTo)
    {
        this->timestampTo = this->timestampFrom;
    }
}

QDateTime MsgTimestampFilter::getTimestampFrom() const
{
    return timestampFrom;
}

void MsgTimestampFilter::setTimestampTo( const QDateTime &timestampTo)
{
    this->timestampTo = timestampTo;
    if(this->timestampFrom > this->timestampTo)
    {
        this->timestampFrom = this->timestampTo;
    }
}

QDateTime MsgTimestampFilter::getTimestampTo() const
{
    return timestampTo;
}

bool MsgTimestampFilter::greaterThanTimestampFrom(const QDateTime &timestamp) const
{
    return timestampFrom > timestamp;
}

bool MsgTimestampFilter::lowerThanTimestampTo(const QDateTime &timestamp) const
{
    return timestampTo < timestamp;
}

bool MsgTimestampFilter::applyInversion(
        const bool intermediateFilterResult
        ) const
{
    return isInverted ? !intermediateFilterResult : intermediateFilterResult;
}
