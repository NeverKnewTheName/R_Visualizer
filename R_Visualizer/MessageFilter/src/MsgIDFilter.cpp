#include "MsgIDFilter.h"

MsgIDFilter::MsgIDFilter(
        IMsgIDFilterStore *msgIDFilterStore,
        QObject *parent
        ) :
    QObject(parent),
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

    bool filterResult = msgIDFilterStore.containsMsgID(msgToFilter);

    return applyInversion(filterResult);
}

void MsgIDFilter::enableFilter(const bool enable)
{
    isEnabled(enable);
    emit sngl_filterEnabled(isEnabled);
}

bool MsgIDFilter::isEnabled() const
{
    return isEnabled;
}

void MsgIDFilter::invertFilter(const bool inverted)
{
    isInverted = inverted;
    emit sgnl_filterInverted(isInverted);
}

bool MsgIDFilter::isInverted() const
{
    return isInverted;
}

void MsgIDFilter::addMsgIDToFilter(const MsgIDType &msgIDToAdd)
{
    msgIDFilterStore->addMsgID(msgIDToAdd);
    emit sgnl_filterChanged();
}

void MsgIDFilter::removeMsgIDFromFilter(const MsgIDType &msgIDtoRemove)
{
    msgIDFilterStore->removeMsgID(msgIDToRemove);
    emit sgnl_filterChanged();
}

bool MsgIDFilter::applyInversion(const bool intermediateFilterResult) const
{
    return isInverted ? !intermediateFilterResult : intermediateFilterResult;
}
