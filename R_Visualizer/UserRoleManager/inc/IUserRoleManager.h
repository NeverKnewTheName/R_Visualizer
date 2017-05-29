/**
 * @file IUserRoleManager.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The interface for the User-Role Manager
 */
#ifndef IUSERROLEMANAGER_H
#define IUSERROLEMANAGER_H

#include <QObject>

namespace UserRoleManagement
{
    enum UserRole
    {
        NormalUserRole, //!< Role of a normal user with minimum priviledges
        AdminRole,      //!< Role of an administrator with maximum priviledges
        NR_OF_ROLES     //!< The overall number of provided user roles
    };

}

/**
 * @brief The IUserRoleManager interface
 */
class IUserRoleManager : public QObject
{
    Q_OBJECT
public:
    explicit IUserRoleManager(QObject *parent = Q_NULLPTR) : QObject(parent){}
    virtual ~IUserRoleManager(){}

    virtual void setUserRole(const UserRoleManagement::UserRole roleToSet) = 0;

    virtual UserRoleManagement::UserRole getUserRole() const = 0;

signals:
    void sgnl_UserRoleHasChanged(const UserRoleManagement::UserRole newUserRole);

public slots:
    virtual void slt_SetUserRole(const UserRoleManagement::UserRole roleToSet)
    {
        setUserRole(roleToSet);
    }
};

#endif /* IUSERROLEMANAGER_H */
