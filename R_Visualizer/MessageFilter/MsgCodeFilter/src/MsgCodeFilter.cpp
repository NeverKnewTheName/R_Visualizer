#include "MsgCodeFilter.h"

MsgCodeFilter::MsgCodeFilter(
        IMsgCodeFilterStore *msgCodeFilterStore,
        QObject *parent
        ) :
    IMsgFilter(parent),
    msgCodeFilterStore(msgCodeFilterStore),
    isEnabled(false),
    isInverted(false)
{
}

MsgCodeFilter::~MsgCodeFilter()
{
}

bool MsgCodeFilter::filterMessage(const IMsg &msgToFilter) const
{
    if(!isEnabled)
    {
        return true;
    }

    bool filterResult = msgCodeFilterStore->containsMsgCode(msgToFilter.getMsgCode());

    return applyInversion(filterResult);
}

void MsgCodeFilter::enableFilter(const bool enable)
{
    isEnabled = enable;
    emit sgnl_filterEnabled(isEnabled);
}

bool MsgCodeFilter::isFilterEnabled() const
{
    return isEnabled;
}

void MsgCodeFilter::invertFilter(const bool inverted)
{
    isInverted = inverted;
    emit sgnl_filterInverted(isInverted);
}

bool MsgCodeFilter::isFilterInverted() const
{
    return isInverted;
}

void MsgCodeFilter::addMsgCodeToFilter(const MsgCodeType &msgCodeToAdd)
{
    msgCodeFilterStore->addMsgCode(msgCodeToAdd);
    emit sgnl_filterChanged();
}

void MsgCodeFilter::removeMsgCodeFromFilter(const MsgCodeType &msgCodeToRemove)
{
    msgCodeFilterStore->removeMsgCode(msgCodeToRemove);
    emit sgnl_filterChanged();
}

bool MsgCodeFilter::applyInversion(const bool intermediateFilterResult) const
{
    return isInverted ? !intermediateFilterResult : intermediateFilterResult;
}


void MsgCodeFilter::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
}
