#include "MsgIDFilter.h"

MsgIDFilter::MsgIDFilter(
        IMsgIDFilterStore *msgIDFilterStore,
        QObject *parent
        ) :
    IMsgIDFilter(parent),
    msgIDFilterStore(msgIDFilterStore),
    isEnabled(false),
    isInverted(false)
{
}

MsgIDFilter::~MsgIDFilter()
{
}

bool MsgIDFilter::filterMessage(const IMsg &msgToFilter) const
{
    if(!isEnabled)
    {
        return true;
    }

    bool filterResult = msgIDFilterStore->containsMsgID(msgToFilter.getMsgID());

    return applyInversion(filterResult);
}

void MsgIDFilter::enableFilter(const bool enable)
{
    isEnabled = enable;
    emit sgnl_filterEnabled(isEnabled);
}

bool MsgIDFilter::isFilterEnabled() const
{
    return isEnabled;
}

void MsgIDFilter::invertFilter(const bool inverted)
{
    isInverted = inverted;
    emit sgnl_filterInverted(isInverted);
}

bool MsgIDFilter::isFilterInverted() const
{
    return isInverted;
}

void MsgIDFilter::addMsgIDToFilter(const MsgIDType &msgIDToAdd)
{
    msgIDFilterStore->addMsgID(msgIDToAdd);
    emit sgnl_filterChanged(*this);
    emit sgnl_MsgFilterChanged(*this);
}

void MsgIDFilter::removeMsgIDFromFilter(const MsgIDType &msgIDToRemove)
{
    msgIDFilterStore->removeMsgID(msgIDToRemove);
    emit sgnl_filterChanged(*this);
    emit sgnl_MsgFilterChanged(*this);
}

bool MsgIDFilter::applyInversion(const bool intermediateFilterResult) const
{
    return isInverted ? !intermediateFilterResult : intermediateFilterResult;
}


void MsgIDFilter::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
}
