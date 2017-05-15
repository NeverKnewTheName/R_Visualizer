#include "UserRoleManager.h"

UserRoleManager::UserRoleManager(
        QObject *parent,
        UserRoleManagement::UserRole defaultRole
        ) :
    IUserRoleManager(parent),
    currentUserRole(defaultRole)
{
}

UserRoleManager::~UserRoleManager()
{
}

void UserRoleManager::setUserRole(const UserRoleManagement::UserRole roleToSet)
{
    currentUserRole = roleToSet;

    emit sgnl_UserRoleHasChanged(currentUserRole);
}

UserRoleManagement::UserRole UserRoleManager::getUserRole() const
{
    return currentUserRole;
}
