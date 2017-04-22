#include "MessageConfigNotifier.h"

#include "IMessageConfig.h"
#include "IMsgMappingManager.h"

MessageConfigNotifier::MessageConfigNotifier(
        IMessageConfig *msgConfig,
        QObject *parent
        ) :
    QObject(parent),
    msgConfig(msgConfig)
{
}

MessageConfigNotifier::~MessageConfigNotifier()
{
}

void MessageConfigNotifier::emitSgnlMappingChanged(
        const IMsgMappingManager &changedMapping
        )
{
    emit sgnl_MappingChanged(changedMapping);
}

void MessageConfigNotifier::emitSgnlPropagateUserRole(
        const UserRoleManagement::UserRole roleToApply
        )
{
    emit sgnl_PropagateUserRole(roleToApply);
}

void MessageConfigNotifier::slt_ApplyRole(
        const UserRoleManagement::UserRole roleToApply
        )
{
    emit sgnl_PropagateUserRole(roleToApply);
    msgConfig->applyUserRole(roleToApply);
}
