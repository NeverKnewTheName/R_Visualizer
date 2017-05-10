#include "MsgTimespanFilter.h"

#include "ITimestampedMsg.h"

MsgTimespanFilter::MsgTimespanFilter(QObject *parent) :
    IMsgTimespanFilter(parent),
    timestampFrom(QDateTime::currentDateTime()),
    timestampTo(QDateTime::currentDateTime()),
    isEnabled(true),
    isInverted(false),
    timestampFromFilterEnabled(false),
    timestampToFilterEnabled(false)
{
}

MsgTimespanFilter::~MsgTimespanFilter()
{
}

bool MsgTimespanFilter::filterTimestamp(
        const ITimestamp &timestampToFilter
        ) const
{
    bool filterResult = true;

    if(isEnabled)
    {
        const QDateTime &msgTimestamp = timestampToFilter.getTimestamp();

        if(timestampFromFilterEnabled)
        {
            filterResult &= greaterThanTimestampFrom(msgTimestamp);
        }
        if(timestampToFilterEnabled)
        {
            filterResult &= lowerThanTimestampTo(msgTimestamp);
        }

        return applyInversion(filterResult);
    }
    else
    {
        return filterResult;
    }
}

void MsgTimespanFilter::enableFilter(const bool enable)
{
    this->isEnabled = enable;
}

bool MsgTimespanFilter::isFilterEnabled() const
{
    return isEnabled;
}

void MsgTimespanFilter::invertFilter(const bool invert)
{
    this->isInverted = invert;
}

bool MsgTimespanFilter::isFilterInverted() const
{
    return isInverted;
}

void MsgTimespanFilter::setTimestampFrom( const QDateTime &timestampFrom)
{
    this->timestampFrom = timestampFrom;
    if(this->timestampFrom > this->timestampTo)
    {
        this->timestampTo = this->timestampFrom;
        emit sgnl_TimestampToChanged(timestampTo);
    }
    emit sgnl_TimestampFromChanged(timestampFrom);
    emit sgnl_filterChanged(*this);
    emit sgnl_TimestampFilterChanged(*this);
}

QDateTime MsgTimespanFilter::getTimestampFrom() const
{
    return timestampFrom;
}

void MsgTimespanFilter::setTimestampTo( const QDateTime &timestampTo)
{
    this->timestampTo = timestampTo;
    if(this->timestampFrom > this->timestampTo)
    {
        this->timestampFrom = this->timestampTo;
        emit sgnl_TimestampFromChanged(timestampFrom);
    }
    emit sgnl_TimestampToChanged(timestampTo);
    emit sgnl_filterChanged(*this);
    emit sgnl_TimestampFilterChanged(*this);
}

QDateTime MsgTimespanFilter::getTimestampTo() const
{
    return timestampTo;
}

bool MsgTimespanFilter::greaterThanTimestampFrom(const QDateTime &timestamp) const
{
    return timestampFrom > timestamp;
}

bool MsgTimespanFilter::lowerThanTimestampTo(const QDateTime &timestamp) const
{
    return timestampTo < timestamp;
}

bool MsgTimespanFilter::applyInversion(
        const bool intermediateFilterResult
        ) const
{
    return isInverted ? !intermediateFilterResult : intermediateFilterResult;
}

void MsgTimespanFilter::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

void MsgTimespanFilter::applyUserRole(
        const UserRoleManagement::UserRole roleToApply
        )
{
}

void MsgTimespanFilter::enableTimestampFilterFrom(
        const bool enabled
        )
{
    timestampFromFilterEnabled = enabled;

    emit sgnl_TimestampFilterChanged(*this);
}

bool MsgTimespanFilter::isTimestampFilterFromEnabled() const
{
    return timestampFromFilterEnabled;
}

void MsgTimespanFilter::enableTimestampFilterTo(
        const bool enabled
        )
{
    timestampToFilterEnabled = enabled;

    emit sgnl_TimestampFilterChanged(*this);
}

bool MsgTimespanFilter::isTimestampFilterToEnabled() const
{
    return timestampToFilterEnabled;
}
