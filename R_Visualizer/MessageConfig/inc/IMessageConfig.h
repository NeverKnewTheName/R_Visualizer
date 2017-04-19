#ifndef IMESSAGECONFIG_H
#define IMESSAGECONFIG_H

#include <QString>
#include <QColor>

#include "prettymsg.h"

class IMessageConfig
{
private:
    

public:
    virtual ~IMessageConfig(){}

    virtual PrettyMsg prettifyMsg(const Msg &msg) const = 0;

    virtual MsgIDType getIDToName(const QString &name) const = 0;
    virtual QString getNameToID(const MsgIDType id) const = 0;
    virtual QColor getColorToID(const MsgIDType id) const = 0;
    virtual QColor getColorToIDName(const QString &name) const = 0;
    virtual QCompleter *createIDNameCompleter(QObject *parent = Q_NULLPTR) const = 0;

    virtual MsgCodeType getCodeToName(const QString &name) const = 0;
    virtual QString getNameToCode(const MsgCodeType code) const = 0;
    virtual QColor getColorToCode(const MsgCodeType code) const = 0;
    virtual QColor getColorToCodeName(const QString &name) const = 0;
    virtual QCompleter *createCodeNameCompleter(QObject *parent = Q_NULLPTR) const = 0;

signals:
    virtual void sgnl_IDRepAdded(const IDRep &newIDRep) = 0;
    virtual void sgnl_IDRepUpdated(const IDRep &updatedIDRep) = 0;
    virtual void sgnl_IDRepRemoved(const MsgIDType relatedID) = 0;

    virtual void sgnl_MsgTypeRepAdded(const MsgTypeRep &newMsgTypeRep) = 0;
    virtual void sgnl_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep) = 0;
    virtual void sgnl_MsgTypeRepRemoved(const MsgCodeType relatedCode) = 0;

private slots:
    virtual void slt_ApplyRole(UserRoleMngr::UserRole roleToApply) = 0;
};

#endif /* IMESSAGECONFIG_H */
