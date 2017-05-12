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
    connect(
            msgIDFilterStore,
            &IMsgIDFilterStore::sgnl_HasChanged,
                [=](){
                        if(isEnabled)
                        {
                            emit sgnl_MsgFilterChanged(*this);
                        }
                    }
            );
    connect(
            this,
            &IMsgIDFilter::sgnl_MsgFilterChanged,
            this,
            &IMsgIDFilter::sgnl_filterChanged
            );
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
    emit sgnl_MsgFilterChanged(*this);
}

bool MsgIDFilter::isFilterEnabled() const
{
    return isEnabled;
}

void MsgIDFilter::invertFilter(const bool inverted)
{
    isInverted = inverted;
    emit sgnl_filterInverted(isInverted);
    if(isEnabled)
    {
        emit sgnl_MsgFilterChanged(*this);
    }
}

bool MsgIDFilter::isFilterInverted() const
{
    return isInverted;
}

void MsgIDFilter::addMsgIDToFilter(const MsgIDType &msgIDToAdd)
{
    msgIDFilterStore->addMsgID(msgIDToAdd);
}

void MsgIDFilter::removeMsgIDFromFilter(const MsgIDType &msgIDToRemove)
{
    msgIDFilterStore->removeMsgID(msgIDToRemove);
}

bool MsgIDFilter::applyInversion(const bool intermediateFilterResult) const
{
    return isInverted ? !intermediateFilterResult : intermediateFilterResult;
}

void MsgIDFilter::accept(FileParser *visitor)
{
    msgIDFilterStore->accept(visitor);
}

void MsgIDFilter::clear()
{
    msgIDFilterStore->clear();
}


void MsgIDFilter::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
}
