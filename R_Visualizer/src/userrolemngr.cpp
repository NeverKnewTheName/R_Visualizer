#include "userrolemngr.h"

UserRoleMngr::UserRoleMngr(QObject *parent) : QObject(parent)
{
    this->currentRole = UserRoleMngr::NormalUserRole;
}

UserRoleMngr::UserRoleMngr(UserRole defaultRole, QObject *parent) : QObject(parent), currentRole(defaultRole)
{

}

UserRoleMngr::UserRole UserRoleMngr::getCurrentRole() const
{
    return currentRole;
}

void UserRoleMngr::setCurrentRole(const UserRole &value)
{
    currentRole = value;
}

void UserRoleMngr::switchRoles(UserRole roleToSwitchTo)
{
    this->currentRole = roleToSwitchTo;
}
