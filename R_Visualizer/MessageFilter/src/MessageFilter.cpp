#include "MessageFilter.h"

#include "IMsgFilter.h"
#include "ITimestampedMsgFilter.h"
#include "IMsg.h"
#include "ITimestampedMsg.h"

MessageFilter::MessageFilter(QObject *parent) :
    IMessageFilter(parent)
{

}

MessageFilter::~MessageFilter()
{
}

bool MessageFilter::filterMessage(const IMsg &msgToFilter) const
{
    for(auto filter : msgFilterStore)
    {
        if(!filter->filterMessage(msgToFilter))
        {
            return false;
        }
    }

    return true;
}

bool MessageFilter::filterMessage(const ITimestampedMsg &msgToFilter) const
{
    for(auto filter : timestampedMsgFilterStore)
    {
        if(!filter->filterTimestamp(msgToFilter))
        {
            return false;
        }
    }

    // A ITimestampedMsg is a IMsg, thus the upcast is safe
    return filterMessage(dynamic_cast<const IMsg &>(msgToFilter));
}

bool MessageFilter::filterMessageByFilter(
        IMsgFilter *filterToUse,
        const IMsg &msgToFilter
        ) const
{
    return filterToUse->filterMessage(msgToFilter);
}

bool MessageFilter::filterMessageByFilter(
        ITimestampedMsgFilter *filterToUse,
        const ITimestampedMsg &msgToFilter
        ) const
{
    return filterToUse->filterTimestamp(msgToFilter);
}

/* void MessageFilter::addFilter(IFilter *filterToAdd) */
/* { */
/*     regularFilterStore.append(filterToAdd); */
/* } */

void MessageFilter::addFilter(IMsgFilter *filterToAdd)
{
    msgFilterStore.append(filterToAdd);
    connect(
            filterToAdd,
            &IMsgFilter::sgnl_MsgFilterChanged,
            this,
            &IMessageFilter::sgnl_MsgFilterHasChanged
            );
}

void MessageFilter::addFilter(ITimestampedMsgFilter *filterToAdd)
{
    timestampedMsgFilterStore.append(filterToAdd);
    connect(
            filterToAdd,
            &ITimestampedMsgFilter::sgnl_TimestampFilterChanged,
            this,
            &IMessageFilter::sgnl_TimestampFilterHasChanged
            );
}

/* void MessageFilter::removeFilter(IFilter *filterToRemove) */
/* { */
/*     regularFilterStore.removeAll(filterToRemove); */
/* } */

void MessageFilter::removeFilter(IMsgFilter *filterToRemove)
{
    msgFilterStore.removeAll(filterToRemove);
    disconnect(filterToRemove);
}

void MessageFilter::removeFilter(ITimestampedMsgFilter *filterToRemove)
{
    timestampedMsgFilterStore.removeAll(filterToRemove);
    disconnect(filterToRemove);
}

void MessageFilter::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
    //ToDo
}
