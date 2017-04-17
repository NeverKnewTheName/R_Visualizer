/**
 * \file IMessageConfig.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief An interface for the Message Config Module
 */
#ifndef IMESSAGECONFIG_H
#define IMESSAGECONFIG_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QCompleter>

#include "userrolemngr.h"

class MessageConfigNotifier;
class IPrettyMsg;
class IMsgMapping;
class IMsg;
class ITimestampedMsg;

/**
 * \brief The IMessageConfig interface
 */
class IMessageConfig
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

    /* /** */
    /*  * @brief Generic QCompleter generator function for mappings */
    /*  *1/ */
    /* virtual QCompleter *createAliasCompleterForMapping( */
    /*         const MessageMappingTypes mappingType, */
    /*         QObject *parent = Q_NULLPTR */
    /*         ) = 0; */

    virtual void applyUserRole(const UserRoleMngr::UserRole roleToApply) = 0;

    /**
     * @brief Workaround for messy signal and slot mechanism with interfaces...
     */
    virtual MessageConfigNotifier *getNotifier() = 0;
};

#endif /* IMESSAGECONFIG_H */
