#include "MsgTimestampFilter.h"

#include "ITimestampedMsg.h"

MsgTimestampFilter::MsgTimestampFilter()
{
}

MsgTimestampFilter::~MsgTimestampFilter()
{
}

bool MsgTimestampFilter::filterMessage(const IMsg &msgToFilter) const
{
    try
    {
        //The cast will throw an exception when the cast fails
        const ITimestampedMsg &timestampedMsg =
            dynamic_cast<const ITimestampedMsg&>(msgToFilter);
        const QDateTime &msgTimestamp = timestampedMsg.getTimestamp();

        bool filterResult = true;

        filterResult &= filterTimestampFrom(msgTimestamp);
        filterResult &= filterTimestampTo(msgTimestamp);

        return applyInversion(filterResult);
    }
    catch(std::bad_cast exp)
    {
        //If a regular Msg that does not contain a timestamp is passed, ignore
        //this filter!
        return true;
    }
}

void MsgTimestampFilter::enableFilter(const bool enable)
{
    this->isEnabled = enable;
}

bool MsgTimestampFilter::isEnabled() const
{
    return isEnabled;
}

void MsgTimestampFilter::invertFilter(const bool invert)
{
    this->isInverted = invert;
}

bool MsgTimestampFilter::isInverted() const
{
    return isInverted;
}

void MsgTimestampFilter::setTimestampFrom( const QDateTime &timestampFrom)
{
    this->timestampeFrom = timestampFrom;
}

QDateTime MsgTimestampFilter::getTimestampFrom() const
{
    return timestampFrom;
}

void MsgTimestampFilter::setTimestampTo( const QDateTime &timestampTo)
{
    this->timestampTo = timestampTo;
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
