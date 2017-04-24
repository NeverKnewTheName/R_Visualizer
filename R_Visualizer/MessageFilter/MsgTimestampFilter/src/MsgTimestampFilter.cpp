#include "MsgTimestampFilter.h"

#include "ITimestampedMsg.h"

MsgTimestampFilter::MsgTimestampFilter(QObject *parent) :
    ITimestampedMsgFilter(parent),
    timestampFrom(QDateTime::currentDateTime()),
    timestampTo(QDateTime::currentDateTime()),
    isEnabled(true),
    isInverted(false),
    timestampFromFilterEnabled(false),
    timestampToFilterEnabled(false)
{
}

MsgTimestampFilter::~MsgTimestampFilter()
{
}

bool MsgTimestampFilter::filterTimestamp(
        const ITimestamp &timestampToFilter
        ) const
{
    bool filterResult = true;
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
        emit sgnl_TimestampToChanged(timestampTo);
    }
    emit sgnl_TimestampFromChanged(timestampFrom);
    emit sgnl_filterChanged(*this);
    emit sgnl_TimestampFilterChanged(*this);
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
        emit sgnl_TimestampFromChanged(timestampFrom);
    }
    emit sgnl_TimestampToChanged(timestampTo);
    emit sgnl_filterChanged(*this);
    emit sgnl_TimestampFilterChanged(*this);
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

void MsgTimestampFilter::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
}

void MsgTimestampFilter::slt_changeTimestampTo(
        const QDateTime &newTimestampTo
        )
{
    setTimestampTo(newTimestampTo);
}

void MsgTimestampFilter::slt_changeTimestampFrom(
        const QDateTime &newTimestampFrom
        )
{
    setTimestampFrom(newTimestampFrom);
}

void MsgTimestampFilter::enableTimestampFilterFrom(
        const bool enabled
        )
{
    timestampFromFilterEnabled = enabled;

    emit sgnl_TimestampFilterChanged(*this);
}

bool MsgTimestampFilter::isTimestampFilterFromEnabled() const
{
    return timestampFromFilterEnabled;
}

void MsgTimestampFilter::enableTimestampFilterTo(
        const bool enabled
        )
{
    timestampToFilterEnabled = enabled;

    emit sgnl_TimestampFilterChanged(*this);
}

bool MsgTimestampFilter::isTimestampFilterToEnabled() const
{
    return timestampToFilterEnabled;
}

void MsgTimestampFilter::slt_enableTimestampFrom(
        const bool enabled
        )
{
    enableTimestampFilterFrom(enabled);
}

void MsgTimestampFilter::slt_enableTimestampTo(
        const bool enabled
        )
{
    enableTimestampFilterTo(enabled);
}
