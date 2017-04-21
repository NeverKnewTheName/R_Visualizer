/**
 * @file UserRoleManager.h
 * @author Christian Neuberger
 * @date 2017-04-21
 * 
 * @brief The default UserRole Manager
 */
#ifndef USERROLEMANAGER_H
#define USERROLEMANAGER_H

#include "IUserRoleManager.h"

/**
 * @brief The UserRoleManager
 */
class UserRoleManager : public IUserRoleManager
{
public:
    explicit UserRoleManager(
            QObject *parent = Q_NULLPTR,
            UserRoleManagement::UserRole = UserRoleManagement::NormalUserRole
            );
    virtual ~UserRoleManager();

    virtual void setUserRole(const UserRoleManagement::UserRole roleToSet);

    virtual UserRoleManagement::UserRole getUserRole() const;


private:
    UserRoleManagement::UserRole currentUserRole;
};

#endif /* USERROLEMANAGER_H */
