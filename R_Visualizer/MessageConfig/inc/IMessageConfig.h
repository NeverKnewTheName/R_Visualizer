/**
 * \file IMessageConfig.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief An interface for the Message Config Module
 */
#ifndef IMESSAGECONFIG_H
#define IMESSAGECONFIG_H

#include <QString>
#include <QColor>
#include <QCompleter>

#include "IMsg.h"
#include "ITimestampedMsg.h"
#include "PrettyMsg.h"

#include "userrolemngr.h"

class IMsgMapping;
class IMsgIDRep;
class IMsgCodeRep;
class IMsgDataRep;

/**
 * \brief The IMessageConfig interface
 */
class IMessageConfig //: public IFileParsable
{
public:
    /**
     * @brief Enumeration of mapping types
     * 
     * The Message config expects three mapping types to be present:
     * - Message ID Mapping
     * - Message Code Mapping
     * - Message Data Mapping
     * 
     * Every other mapping, that is added by the user, must start its
     * Enumeration at USERMappingType
     */
    typedef enum _MessageMappingTypes
    {
        MessageIDMappingType, //!< Message ID Mapping Type
        MessageCodeMappingType, //!< Message Code Mapping Type
        MessageDataMappingType, //!< Message Data Mapping Type
        USERMappingType //!< Start of USER definded mappings
    }MessageMappingTypes;

    /**
     * @brief Destructor
     */
    virtual ~IMessageConfig(){}

    /**
     * @brief Prettifies the given #IPrettyMsg and returns a reference to it
     */
    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const = 0;

    virtual void prettifyMsgByMapping(
            IPrettyMsg &msgToPrettify,
            const IMsgMapping &mappingToApply
            ) const = 0;

    /**
     * @brief Generic QCompleter generator function for mappings
     */
    virtual QCompleter *createAliasCompleterForMapping(
            const MessageMappingTypes mappingType,
            QObject *parent = Q_NULLPTR
            ) = 0;

    //ToTHINK Deprecated
    /* virtual QCompleter *createIDNameCompleter( */
    /*         QObject *parent = Q_NULLPTR */
    /*         ) const = 0; */

    //ToTHINK Deprecated
    /* virtual QCompleter *createCodeNameCompleter( */
    /*         QObject *parent = Q_NULLPTR */
    /*         ) const = 0; */

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
    virtual void sgnl_MappingChanged(
            const IMessageConfig::MessageMappingTypes mappingType
            ) = 0;

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
    virtual void slt_ApplyRole(const UserRoleMngr::UserRole roleToApply) = 0;
};

#endif /* IMESSAGECONFIG_H */
