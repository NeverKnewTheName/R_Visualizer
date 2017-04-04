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
 * @brief The MessageConfig module is a standard implementation of the
 * #IMessageConfig interface
 * 
 * The standard implementation has per default mappings for message ID,
 * message code, and message data fields.
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

    virtual IPrettyMsgUniqPtr<IMsg> prettifyMsg(
            const IMsg &msgToPrettify
            ) const;
    virtual IPrettyMsgUniqPtr<ITimestampedMsg> prettifyMsg(
            const ITimestampedMsg &timestampedMsgToPrettify
            ) const;

    virtual QCompleter *createAliasCompleterForMapping(
            const IMessageConfig::MessageMappingTypes mappingType,
            QObject *parent = Q_NULLPTR
            );


    //ToTHINK DEPRECATED?
    //void accept(FileParser *visitor);

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
            );

private slots:
    void slt_ApplyRole(const UserRoleMngr::UserRole roleToApply);

private:
    QCompleter *createIDNameCompleter(QObject *parent = Q_NULLPTR);
    QCompleter *createCodeNameCompleter(QObject *parent = Q_NULLPTR);

private:
    IMsgIDMapping *msgIDMapping;
    IMsgCodeMapping *msgCodeMapping;
    IMsgDataMapping *msgDataMapping;
};

#endif /* MESSAGECONFIG_H */
