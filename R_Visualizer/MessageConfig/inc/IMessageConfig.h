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

class IMsgIDRep;
class IMsgCodeRep;
class IMsgDataRep;

/**
 * \brief The IMessageConfig interface
 */
class IMessageConfig : public IFileParsable
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
     * @note Every other mapping, that is added by the user, must start its
     * Enumeration at USERMappingType
     */
    typedef enum _MessageMappingTypes
    {
        MessageIDMappingType, //!< Message ID Mapping Type
        MessageCodeMappingType, //!< Message Code Mapping Type
        MessageDataMappingType, //!< Message Data Mapping Type
        USERMappingType //!< Start of USER definded mappings
    }MessageMappingTypes;

    virtual ~IMessageConfig(){}

    /**
     * @brief Returns a unique_ptr to the prettified message
     * 
     * @note The template parameter BaseClass must be specialized in the
     * implementation classes to match the used derivate of #IPrettyMsg
     */
    virtual IPrettyMsgUniqPtr<IMsg> prettifyMsg(
            const IMsg &msgToPrettify
            ) const = 0;
    virtual IPrettyMsgUniqPtr<ITimestampedMsg> prettifyMsg(
            const ITimestampedMsg &timestampedMsgToPrettify
            ) const = 0;
    /* virtual PrettyMsg prettifyMsg(const Msg &msg) const = 0; */

    /* virtual MsgIDType getIDToName(const QString &name) const = 0; */
    /* virtual QString getNameToID(const MsgIDType id) const = 0; */
    /* virtual QColor getColorToID(const MsgIDType id) const = 0; */
    /* virtual QColor getColorToIDName(const QString &name) const = 0; */
    virtual QCompleter *createIDNameCompleter(
            QObject *parent = Q_NULLPTR
            ) const = 0;

    /* virtual MsgCodeType getCodeToName(const QString &name) const = 0; */
    /* virtual QString getNameToCode(const MsgCodeType code) const = 0; */
    /* virtual QColor getColorToCode(const MsgCodeType code) const = 0; */
    /* virtual QColor getColorToCodeName(const QString &name) const = 0; */
    virtual QCompleter *createCodeNameCompleter(
            QObject *parent = Q_NULLPTR
            ) const = 0;

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

    /* virtual void sgnl_MsgIDRepAdded(const IMsgIDRep &newMsgIDRep) = 0; */
    /* virtual void sgnl_MsgIDRepUpdated(const IMsgIDRep &updatedMsgIDRep) = 0; */
    /* virtual void sgnl_MsgIDRepRemoved(const MsgIDType relatedID) = 0; */

    /* virtual void sgnl_MsgCodeRepAdded(const IMsgCodeRep &newMsgCodeRep) = 0; */
    /* virtual void sgnl_MsgCodeRepUpdated( */
    /*         const IMsgCodeRep &updatedMsgCodeRep */
    /*         ) = 0; */
    /* virtual void sgnl_MsgCodeRepRemoved(const MsgCodeType relatedCode) = 0; */

    /* virtual void sgnl_MsgDataRepAdded(const IMsgDataRep &newMsgDataRep) = 0; */
    /* virtual void sgnl_MsgDataRepUpdated( */
    /*         const IMsgDataRep &updatedMsgDataRep */
    /*         ) = 0; */
    /* virtual void sgnl_MsgDataRepRemoved( */
    /*         const MsgIDType relatedID, */
    /*         const MsgCodeType relatedCode */
    /*         ) = 0; */

private slots:
    virtual void slt_ApplyRole(UserRoleMngr::UserRole roleToApply) = 0;
};

#endif /* IMESSAGECONFIG_H */
