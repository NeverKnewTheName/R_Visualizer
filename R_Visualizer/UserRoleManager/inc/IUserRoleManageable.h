/**
 * @file IUserRoleManageable.h
 * @author Christian Neuberger
 * @date 2017-04-21
 * 
 * @brief Interface that has to be implemented to be manageable by the
 * #IUserRoleManager
 */
#ifndef IUSERROLEMANAGEABLE_H
#define IUSERROLEMANAGEABLE_H

#include "IUserRoleManager.h"

/**
 * @brief The IUserRoleManageable interface
 */
class IUserRoleManageable
{
public:
    virtual ~IUserRoleManageable(){}

    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply) = 0;
};

#endif /* IUSERROLEMANAGEABLE_H */
