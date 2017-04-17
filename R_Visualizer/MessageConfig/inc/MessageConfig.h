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

class MessageConfigNotifier;
class IMsgMapping;
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
class MessageConfig :
    public QObject,
    public IMessageConfig
{
    Q_OBJECT
public:
    MessageConfig(
            IMsgIDMapping *msgIDMapping,
            IMsgCodeMapping *msgCodeMapping,
            IMsgDataMapping *msgDataMapping,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MessageConfig();

    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const;

    virtual void prettifyMsgByMapping(
            IPrettyMsg &msgToPrettify,
            const IMsgMapping &mappingToApply
            ) const;

    /* virtual QCompleter *createAliasCompleterForMapping( */
    /*         const IMessageConfig::MessageMappingTypes mappingType, */
    /*         QObject *parent = Q_NULLPTR */
    /*         ); */

    virtual void applyUserRole(const UserRoleMngr::UserRole roleToApply);

    /**
     * @brief Returns the notifier to this #MessageConfig object
     * 
     * The notifier was introduced to have a unified interface for signals and
     * slots. Somehow it is not possible to declare signals and slots inside of
     * interfaces without sacrificing sanity. Thus, this workaround shall
     * suffice.
     * 
     * \note Signals and Slots for this object are contained in the notifier.
     * Connect to the notifier to connect to this object.
     */
    virtual MessageConfigNotifier *getNotifier();

private:
    MessageConfigNotifier *msgConfigNotifier;
    IMsgIDMapping *msgIDMapping;
    IMsgCodeMapping *msgCodeMapping;
    IMsgDataMapping *msgDataMapping;
};

#endif /* MESSAGECONFIG_H */
