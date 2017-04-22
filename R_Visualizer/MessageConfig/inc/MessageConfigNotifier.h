#ifndef MESSAGECONFIGNOTIFIER_H
#define MESSAGECONFIGNOTIFIER_H

#include <QObject>

#include "IUserRoleManager.h"

class IMessageConfig;
class IMsgMappingManager;

class MessageConfigNotifier : public QObject
{
    Q_OBJECT
public:
    MessageConfigNotifier(
            IMessageConfig *msgConfig,
            QObject *parent = Q_NULLPTR
            );

    virtual ~MessageConfigNotifier();

    virtual void emitSgnlMappingChanged(const IMsgMappingManager &changedMapping
            );

    virtual void emitSgnlPropagateUserRole(
            const UserRoleManagement::UserRole roleToApply
            );

signals:
    /**
     * @brief This signal is emitted when a mapping is changed
     * 
     * The singal is emitted with the corresponding mappingType whenever a new
     * entry is added, an existing entry is updated, or an existing entry is
     * removed.
     * 
     * @param[out] mappingType Type of the mapping that has changed
     */
    void sgnl_MappingChanged(
            const IMsgMappingManager &changedMapping
            );

    /**
     * @brief Propagated signal that widgets or mappings can connect to in
     * order to receive changes in the user-role
     * 
     * This signal is emitted as a response to receiving a user-role change
     * from the #UserRoleMngr
     */
    void sgnl_PropagateUserRole(
            const UserRoleManagement::UserRole roleToApply
            );

public slots:
    void slt_ApplyRole(const UserRoleManagement::UserRole roleToApply);

private:
    IMessageConfig *msgConfig;
};

#endif /* MESSAGECONFIGNOTIFIER_H */
