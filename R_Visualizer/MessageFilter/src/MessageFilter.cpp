#include "MessageFilter.h"

#include "MessageFilterNotifier.h"
#include "IMsgFilter.h"
#include "ITimestampedMsgFilter.h"
#include "IMsg.h"
#include "ITimestampedMsg.h"

MessageFilter::MessageFilter(QObject *parent) :
    QObject(parent),
    msgFilterNotifier(new MessageFilterNotifier(this, this))
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
        if(!filter->filterMessage(msgToFilter))
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
    return filterToUse->filterMessage(msgToFilter);
}

/* void MessageFilter::addFilter(IFilter *filterToAdd) */
/* { */
/*     regularFilterStore.append(filterToAdd); */
/* } */

void MessageFilter::addFilter(IMsgFilter *filterToAdd)
{
    msgFilterStore.append(filterToAdd);
}

void MessageFilter::addFilter(ITimestampedMsgFilter *filterToAdd)
{
    timestampedMsgFilterStore.append(filterToAdd);
}

/* void MessageFilter::removeFilter(IFilter *filterToRemove) */
/* { */
/*     regularFilterStore.removeAll(filterToRemove); */
/* } */

void MessageFilter::removeFilter(IMsgFilter *filterToRemove)
{
    msgFilterStore.removeAll(filterToRemove);
}

void MessageFilter::removeFilter(ITimestampedMsgFilter *filterToRemove)
{
    timestampedMsgFilterStore.removeAll(filterToRemove);
}

void MessageFilter::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
    //ToDo
}

MessageFilterNotifier *MessageFilter::getNotifier()
{
    return msgFilterNotifier;
}
