#ifndef IMESSAGECONFIG_H
#define IMESSAGECONFIG_H

#include <QString>
#include <QColor>

#include "prettymsg.h"

class IMessageConfig
{
private:
    

public:
    IMessageConfig();
    virtual ~IMessageConfig();

    PrettyMsg prettifyMsg(const Msg &msg) const = 0;

    MsgIDType getIDToName(const QString &name) const = 0;
    QString getNameToID(const MsgIDType id) const = 0;
    QColor getColorToID(const MsgIDType id) const = 0;
    QColor getColorToIDName(const QString &name) const = 0;
    QCompleter *createIDNameCompleter(QObject *parent = Q_NULLPTR) const = 0;

    MsgCodeType getCodeToName(const QString &name) const = 0;
    QString getNameToCode(const MsgCodeType code) const = 0;
    QColor getColorToCode(const MsgCodeType code) const = 0;
    QColor getColorToCodeName(const QString &name) const = 0;
    QCompleter *createCodeNameCompleter(QObject *parent = Q_NULLPTR) const = 0;

signals:
    void sgnl_IDRepAdded(const IDRep &newIDRep) = 0;
    void sgnl_IDRepUpdated(const IDRep &updatedIDRep) = 0;
    void sgnl_IDRepRemoved(const MsgIDType relatedID) = 0;

    void sgnl_MsgTypeRepAdded(const MsgTypeRep &newMsgTypeRep) = 0;
    void sgnl_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep) = 0;
    void sgnl_MsgTypeRepRemoved(const MsgCodeType relatedCode) = 0;

private slots:
    void slt_ApplyRole(UserRoleMngr::UserRole roleToApply) = 0;
};

#endif /* IMESSAGECONFIG_H */
