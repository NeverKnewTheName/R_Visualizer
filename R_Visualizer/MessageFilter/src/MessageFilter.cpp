#include "MessageFilter.h"

MessageFilter::MessageFilter()
{

}

MessageFilter::~MessageFilter()
{
}

bool MessageFilter::filterMessage(const IMsg &msgToFilter) const
{
    for(auto filter : filterStore)
    {
        if(!filter->filterMessage(msgToFilter))
        {
            return false;
        }
    }

    return true;
}

void MessageFilter::addFilter(IFilter *filterToAdd)
{
    filterStore.append(filterToAdd);
}

void MessageFilter::removeFilter(IFilter *fitlerToRemove)
{
    const int filterStoreSize = filterStore.size();

    for(int i = 0; i < filterStoreSize; ++i)
    {
        if(filterStore.at(i) == filterToRemove)
        {
            filterStore.removeAt(i);
            break;
        }
    }
}

void MessageFilter::slt_applyRole(const UserRoleMngr::UserRole roleToApply)
{
}
