#include "TimestampedMsgFilterNotifier.h"


TimestampedMsgFilterNotifier::TimestampedMsgFilterNotifier(
        ITimestampedMsgFilter *filterToNotify,
        QObject *parent
        ) :
    QObject(parent),
    filterToNotify(filterToNotify)
{
}

TimestampedMsgFilterNotifier::~TimestampedMsgFilterNotifier()
{
}

void TimestampedMsgFilterNotifier::emitSgnlFilterEnabled(
        const bool enabled
        )
{
    emit sgnl_filterEnabled(enabled);
}

void TimestampedMsgFilterNotifier::emitSgnlFilterInverted
        const bool inverted
        )
{
    emit sgnl_filterInverted(inverted);
}

void TimestampedMsgFilterNotifier::emitSgnlFilterChanged(
        ITimestampedMsgFilter *filterThatHasChanged
        )
{
    emit sgnl_filterChanged(filterThatHasChanged);
}

void TimestampedMsgFilterNotifier::slt_enableFilter(
        const bool enable
        )
{
    filterToNotify->enableFilter(enable);
}

void TimestampedMsgFilterNotifier::slt_invertFilter(
        const bool invert
        )
{
    filterToNotify->invertFilter(invert);
}

void TimestampedMsgFilterNotifier::slt_applyUserRole(
        const UserRoleMngr::UserRole roleToApply
        )
{
    filterToNotify->applyUserRole(roleToApply);
}
