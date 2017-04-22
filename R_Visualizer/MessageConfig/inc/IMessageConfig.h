/**
 * @file IMessageConfig.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief An interface for the Message Config Module
 */
#ifndef IMESSAGECONFIG_H
#define IMESSAGECONFIG_H

#include <QObject>

#include "IUserRoleManager.h"

class IPrettyMsg;
class IMsgMappingManager;
class IMsg;
class ITimestampedMsg;

/**
 * @brief The IMessageConfig interface
 */
class IMessageConfig : public QObject
{
    Q_OBJECT
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

    explicit IMessageConfig(QObject *parent = Q_NULLPTR) : QObject(parent){}

    /**
     * @brief Destructor
     */
    virtual ~IMessageConfig(){}

    /**
     * @brief Prettifies the given #IPrettyMsg
     * 
     * @param[inout] msgToPrettify #IPrettyMsg that shall be prettified
     */
    virtual void prettifyMsg(
            IPrettyMsg &msgToPrettify
            ) const = 0;

    /**
     * @brief Prettifies the given #IPrettyMsg with the given #IMsgMappingManager
     * 
     * @param[inout] msgToPrettify #IPrettyMsg that shall be prettified
     * @param[in] mappingToApply #IMsgMappingManager that shall be used to prettify
     */
    virtual void prettifyMsgByMappingManager(
            IPrettyMsg &msgToPrettify,
            const IMsgMappingManager &mappingToApply
            ) const = 0;

    /**
     * @brief Applies the roleToApply to this module
     * 
     * @note Must emit sgnl_PropagateUserRole to inform sub-modules about the
     * changes to the current UserRole
     */
    virtual void applyUserRole(const UserRoleManagement::UserRole roleToApply) = 0;

signals:
    /**
     * @brief This signal shall be emitted wheneever a contained mapping has
     * changed to inform interrested parties about this evernt
     * 
     * Modules that make use of the #IMessageConfig must be informed whenever a
     * mapping contained in the #IMessageConfig object changes to react to this
     * change by calling #prettifyMsgByMappingManager for example.
     */
    void sgnl_MappingManagerChanged(
            const IMsgMappingManager &changedMappingManager
            );

    /**
     * @brief This signal must be emitted whenever the UserRole of this object
     * changes to inform sub-modules about the new UserRole
     */
    void sgnl_PropagateUserRole(
            const UserRoleManagement::UserRole roleToApply
            );

public slots:
    /**
     * @brief This slot must be called to enforce a new UserRole to this module
     * 
     * @note Calls #applyUserRole
     * 
     * @note This slot does not emit #sgnl_PropagateUserRole
     */
    virtual void slt_ApplyRole(const UserRoleManagement::UserRole roleToApply)
    {
        applyUserRole(roleToApply);
    }

};

#endif /* IMESSAGECONFIG_H */
