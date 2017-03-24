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

#include "prettymsg.h"

/**
 * \brief The IMessageConfig interface
 */
class IMessageConfig
{
public:
    virtual ~IMessageConfig(){}

    virtual PrettyMsg prettifyMsg(const Msg &msg) const = 0;

    virtual MsgIDType getIDToName(const QString &name) const = 0;
    virtual QString getNameToID(const MsgIDType id) const = 0;
    virtual QColor getColorToID(const MsgIDType id) const = 0;
    virtual QColor getColorToIDName(const QString &name) const = 0;
    virtual QCompleter *createIDNameCompleter(
            QObject *parent = Q_NULLPTR
            ) const = 0;

    virtual MsgCodeType getCodeToName(const QString &name) const = 0;
    virtual QString getNameToCode(const MsgCodeType code) const = 0;
    virtual QColor getColorToCode(const MsgCodeType code) const = 0;
    virtual QColor getColorToCodeName(const QString &name) const = 0;
    virtual QCompleter *createCodeNameCompleter(
            QObject *parent = Q_NULLPTR
            ) const = 0;

signals:
    virtual void sgnl_MsgIDRepAdded(const IMsgIDRep &newMsgIDRep) = 0;
    virtual void sgnl_MsgIDRepUpdated(const IMsgIDRep &updatedMsgIDRep) = 0;
    virtual void sgnl_MsgIDRepRemoved(const MsgIDType relatedID) = 0;

    virtual void sgnl_MsgCodeRepAdded(const IMsgCodeRep &newMsgCodeRep) = 0;
    virtual void sgnl_MsgCodeRepUpdated(
            const IMsgCodeRep &updatedMsgCodeRep
            ) = 0;
    virtual void sgnl_MsgCodeRepRemoved(const MsgCodeType relatedCode) = 0;

    virtual void sgnl_MsgDataRepAdded(const IMsgDataRep &newMsgDataRep) = 0;
    virtual void sgnl_MsgDataRepUpdated(
            const IMsgDataRep &updatedMsgDataRep
            ) = 0;
    virtual void sgnl_MsgDataRepRemoved(
            const MsgIDType relatedID,
            const MsgCodeType relatedCode
            ) = 0;

private slots:
    virtual void slt_ApplyRole(UserRoleMngr::UserRole roleToApply) = 0;
};

#endif /* IMESSAGECONFIG_H */
