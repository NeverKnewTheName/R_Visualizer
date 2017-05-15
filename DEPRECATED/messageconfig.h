/**
 * \file messageconfig.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief The Message Config Module provides means to customize the visual
 * appearance of message fields in the whole application
 */
#ifndef MESSAGECONFIG_H
#define MESSAGECONFIG_H

#include <QObject>
/* #include "idmodel.h" */
/* #include "MsgIDMappingWidget.h" */
/* #include "msgtypemodel.h" */
#include "userrolemngr.h"

#include "IMessageConfig.h"
#include "IPrettyMsg.h"
#include "IFileParsable.h"

class FileParser;

/**
 * \brief The Message Config Module
 * 
 * The MessageConfig module expects three mappings to be present:
 * - Message ID Mapping
 * - Message Code Mapping
 * - Message Data Mapping
 * 
 * @note Derives from QObject for singal and slot mechanism
 */
class MessageConfig : public QObject, public IMessageConfig
{
    Q_OBJECT

public:
    explicit MessageConfig(QObject *parent = Q_NULLPTR);
    ~MessageConfig();

    IPrettyMsgUniqPtr<IMsg> prettifyMsg(
            const IMsg &msgToPrettify
            ) const;
    IPrettyMsgUniqPtr<ITimestampedMsg> prettifyMsg(
            const ITimestampedMsg &timestampedMsgToPrettify
            ) const;

    /* MsgIDType getIDToName(const QString &name) const; */
    /* QString getNameToID(const MsgIDType id) const; */
    /* QColor getColorToID(const MsgIDType id) const; */
    /* QColor getColorToIDName(const QString &name) const; */
    QCompleter *createIDNameCompleter(QObject *parent = Q_NULLPTR) const;

    /* MsgCodeType getCodeToName(const QString &name) const; */
    /* QString getNameToCode(const MsgCodeType code) const; */
    /* QColor getColorToCode(const MsgCodeType code) const; */
    /* QColor getColorToCodeName(const QString &name) const; */
    QCompleter *createCodeNameCompleter(QObject *parent = Q_NULLPTR) const;


    /* const IDModel &getIDModel() const; */
    /* const MsgTypeModel &getMsgTypeModel() const; */

    void accept(FileParser *visitor);

private:

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

    /* void sgnl_MsgIDRepAdded(const IMsgIDRep &newMsgIDRep); */
    /* void sgnl_MsgIDRepUpdated(const IMsgIDRep &updatedMsgIDRep); */
    /* void sgnl_MsgIDRepRemoved(const MsgIDType relatedID); */

    /* void sgnl_MsgCodeRepAdded(const IMsgCodeRep &newMsgCodeRep); */
    /* void sgnl_MsgCodeRepUpdated(const IMsgCodeRep &updatedMsgCodeRep); */
    /* void sgnl_MsgCodeRepRemoved(const MsgCodeType relatedCode); */

    /* void sgnl_MsgDataRepAdded(const IMsgDataRep &newMsgDataRep); */
    /* void sgnl_MsgDataRepUpdated( */
    /*         const IMsgDataRep &updatedMsgDataRep */
    /*         ); */
    /* void sgnl_MsgDataRepRemoved( */
    /*         const MsgIDType relatedID, */
    /*         const MsgCodeType relatedCode */
    /*         ); */
    /* void sgnl_MsgDataRepAdded(const MsgDataRep &newMsgData); */
    /* void sgnl_MsgDataRepUpdated(const MsgDataRep &updatedMsgData); */
    /* void sgnl_MsgDataRepRemoved(const MsgCodeType relatedCode); */

private slots:
    void slt_ApplyRole(UserRoleMngr::UserRole roleToApply);

    void on_idStoreBtn_clicked();
    void on_idLoadBtn_clicked();
    void on_msgTypeStoreBtn_clicked();
    void on_msgTypeLoadBtn_clicked();
    void on_idAddBtn_clicked();
    void on_msgTypeAddBtn_clicked();
    void on_idRmvBtn_clicked();
    void on_msgTypeRmvBtn_clicked();

    void slt_IDRepAdded(const IDRep &newIDRep);
    void slt_IDRepUpdated(const IDRep &updatedIDRep);
    void slt_IDRepRemoved(const MsgIDType relatedID);

    void slt_MsgTypeRepAdded(const MsgTypeRep &newMsgTypeRep);
    void slt_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep);
    void slt_MsgTypeRepRemoved(const MsgCodeType relatedCode);

    void slt_MsgDataRepAdded(const MsgDataRep &newMsgDataRep);
    void slt_MsgDataRepUpdated(const MsgDataRep &updatedMsgDataRep);
    void slt_MsgDataRepRemoved(const MsgCodeType relatedCode);

};

#endif // MESSAGECONFIG_H
