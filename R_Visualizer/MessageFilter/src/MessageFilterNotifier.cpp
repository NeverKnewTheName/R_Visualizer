#include "MessageFilterNotifier.h"

#include "IMessageFilter.h"

MessageFilterNotifier::MessageFilterNotifier(
            IMessageFilter *msgFilter,
            QObject *parent
            ) :
    QObject(parent),
    msgFilter(msgFilter)
{
}

MessageFilterNotifier::~MessageFilterNotifier()
{
}

void MessageFilterNotifier::emitSnglMsgFilterChanged
        (
        IMsgFilter *filterThatHasChanged
        )
{
    emit sgnl_MsgFilterChanged(filterThatHasChanged);
}

void MessageFilterNotifier::emitSnglTimestampedMsgFilterChanged
        (
        ITimestampedMsgFilter *filterThatHasChanged
        )
{
    emit sgnl_TimestampedMsgFilterChanged(filterThatHasChanged);
}

void MessageFilterNotifier::slt_applyRole(
        const UserRoleManagement::UserRole roleToApply
        )
{
    msgFilter->applyUserRole(roleToApply);
    emit sgnl_PropagateUserRole(roleToApply);
}

