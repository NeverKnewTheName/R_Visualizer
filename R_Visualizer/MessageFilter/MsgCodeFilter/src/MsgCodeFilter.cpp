#include "MsgCodeFilter.h"

MsgCodeFilter::MsgCodeFilter(
        IMsgCodeFilterStore *msgCodeFilterStore,
        QObject *parent
        ) :
    IMsgCodeFilter(parent),
    msgCodeFilterStore(msgCodeFilterStore),
    isEnabled(false),
    isInverted(false)
{
    connect(
            msgCodeFilterStore,
            &IMsgCodeFilterStore::sgnl_HasChanged,
                [=](){
                        if(isEnabled)
                        {
                            emit sgnl_MsgFilterChanged(*this);
                        }
                    }
            );
    connect(
            this,
            &IMsgCodeFilter::sgnl_MsgFilterChanged,
            this,
            &IMsgCodeFilter::sgnl_filterChanged
            );
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
    emit sgnl_MsgFilterChanged(*this);
}

bool MsgCodeFilter::isFilterEnabled() const
{
    return isEnabled;
}

void MsgCodeFilter::invertFilter(const bool inverted)
{
    isInverted = inverted;
    emit sgnl_filterInverted(isInverted);
    if(isEnabled)
    {
        emit sgnl_MsgFilterChanged(*this);
    }
}

bool MsgCodeFilter::isFilterInverted() const
{
    return isInverted;
}

void MsgCodeFilter::addMsgCodeToFilter(const MsgCodeType &msgCodeToAdd)
{
    msgCodeFilterStore->addMsgCode(msgCodeToAdd);
}

void MsgCodeFilter::removeMsgCodeFromFilter(const MsgCodeType &msgCodeToRemove)
{
    msgCodeFilterStore->removeMsgCode(msgCodeToRemove);
}

bool MsgCodeFilter::applyInversion(const bool intermediateFilterResult) const
{
    return isInverted ? !intermediateFilterResult : intermediateFilterResult;
}


void MsgCodeFilter::applyUserRole(const UserRoleManagement::UserRole roleToApply)
{
}


void MsgCodeFilter::accept(FileParser *visitor)
{
    msgCodeFilterStore->accept(visitor);
}

void MsgCodeFilter::clear()
{
    msgCodeFilterStore->clear();
}
