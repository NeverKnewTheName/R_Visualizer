/**
 * @file MessageConfig.h
 * @author Christian Neuberger
 * @date 2017-03-27
 * 
 * @brief The basic implementation of the Message Configuration module
 */
#ifndef MESSAGECONFIG_H
#define MESSAGECONFIG_H

#include <QObject>

#include "IMessageConfig.h"
#include "IMsg.h"
#include "IPrettyMsg.h"

#include "userrolemngr.h"

class IMsgIDMapping;
class IMsgCodeMapping;
class IMsgDataMapping;

/**
 * @brief The MessageConfig module
 */
class MessageConfig : public QObject, public IMessageConfig
{
public:
    MessageConfig(
            IMsgIDMapping *msgIDMapping,
            IMsgCodeMapping *msgCodeMapping,
            IMsgDataMapping *msgDataMapping,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MessageConfig();

    IPrettyMsgUniqPtr<IMsg> prettifyMsg(
            const IMsg &msgToPrettify
            ) const;
    IPrettyMsgUniqPtr<ITimestampedMsg> prettifyMsg(
            const ITimestampedMsg &timestampedMsgToPrettify
            ) const;

    QCompleter *createAliasCompleterForMapping(
            const IMessageConfig::MessageMappingTypes mappingType
            );

    //ToTHINK Deprecated
    QCompleter *createIDNameCompleter(QObject *parent = Q_NULLPTR) const;
    QCompleter *createCodeNameCompleter(QObject *parent = Q_NULLPTR) const;

    //ToTHINK DEPRECATED?
    void accept(FileParser *visitor);

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
            const IMessageConfig::MessageMappingTypes mappingType
            );

    /**
     * @brief Propagated signal that widgets or mappings can connect to in
     * order to receive changes in the user-role
     * 
     * This signal is emitted as a response to receiving a user-role change
     * from the #UserRoleMngr
     */
    virtual void sgnl_PropagateUserRole(
            const UserRoleMngr::UserRole roleToApply
            ) = 0;

private slots:
    void slt_ApplyRole(UserRoleMngr::UserRole roleToApply);

private:
    IMsgIDMapping *msgIDMapping;
    IMsgCodeMapping *msgCodeMapping;
    IMsgDataMapping *msgDataMapping;

};

#endif /* MESSAGECONFIG_H */
