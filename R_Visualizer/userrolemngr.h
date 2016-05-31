#ifndef USERROLE_H
#define USERROLE_H

#include <QObject>



class UserRoleMngr : public QObject
{
    Q_OBJECT
public:
    typedef enum userRoleEnum
    {
        NormalUserRole,
        AdminRole,
        NR_OF_ROLES
    } UserRole;

    explicit UserRoleMngr(QObject *parent = 0);
    explicit UserRoleMngr(UserRole defaultRole, QObject *parent = 0);

    UserRole getCurrentRole() const;
    void setCurrentRole(const UserRole &value);

private:
    UserRole currentRole;
signals:

public slots:
    void switchRoles(UserRole roleToSwitchTo);
};

#endif // USERROLE_H
