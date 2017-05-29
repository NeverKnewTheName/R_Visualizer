/**
 * \file userrolemngr.h
 * \author Christian Neuberger
 * \date 2017-01-31
 * 
 * \brief The UserRoleMngr takes care of handling various roles.
 * 
 * Many modules of the application expose different information or even different
 * control facilities depending on the current user. If the user has, for instance, 
 * no administrative priviledges, the user is then not allowed to change important
 * aspects of the data.
 * 
 * Currently there are two main roles:
 * - Administrator
 * - User
 *   
 * The Administrator has all priviledges and can control every aspect of the application.
 * The User, however, may only change visualization aspects and view the information that is 
 * provided to the user.
 */
#ifndef USERROLE_H
#define USERROLE_H

#include <QObject>

//! The UserRoleMngr Class
/**
 * This class manages the various roles that an operator of the application can have.
 * Its main purpose is to keep track of the current role and dispatch a change of 
 * this role to all subscribed modules.
 */
class UserRoleMngr : public QObject
{
    Q_OBJECT
public:
    /**
     * \brief Enumeration of the provided user roles
     */
    typedef enum userRoleEnum
    {
        NormalUserRole, //!< Role of a normal user with minimum priviledges
        AdminRole,      //!< Role of an administrator with maximum priviledges
        NR_OF_ROLES     //!< The overall number of provided user roles
    } UserRole;

    /**
     * \brief Constructs a new #UserRoleMngr with the given defaultRole.
     * 
     * \param[in] defaultRole The default #UserRole that shall be valid for the application at the start.
     * \param[in] parent      The parent QObject of the #UserRoleMngr.
     * 
     * This constructor creates a new #UserRoleMngr object. If no defaultRole is provided,
     * the defaultRole is set to #NormalUserRole.
     */
    explicit UserRoleMngr( QObject *parent = 0, UserRole defaultRole = NormalUserRole);

    /**
     * \brief Retrieve the current #UserRole
     * 
     * \note Rather than querying the current #UserRole by calling this function,
     * the Signal #SgnlUserRoleChanged shall be subscribed to.
     */
    UserRole getCurrentRole() const;
    /**
     * \brief Set the current user role to \c value
     * 
     * \param[in] value  New #UserRole that shall be set.
     * 
     * \note Rather than calling this function, the Slot #switchRoles shall be used.
     */
    void setCurrentRole(const UserRole &value);

private:
    UserRole currentRole; //!< Current #UserRole that is valid for the application

signals:
    /**
     * \brief Signal that is emitted when the current #UserRole has changed
     * 
     * \param[out] newRole The current #UserRole
     */
    void SgnlUserRoleChanged(const UserRole newRole);

public slots:
    /**
     * \brief Slot that triggers the change of the current #UserRole
     * \param[in] roleToSwitchTo The new #UserRole that shall be applied to the application
     */
    void switchRoles(UserRole roleToSwitchTo);
};

#endif // USERROLE_H
