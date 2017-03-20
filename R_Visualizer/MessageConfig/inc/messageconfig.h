#ifndef MESSAGECONFIG_H
#define MESSAGECONFIG_H

#include <QWidget>
/* #include "idmodel.h" */
#include "MsgIDMappingWidget.h"
#include "msgtypemodel.h"
#include "userrolemngr.h"

#include "prettymsg.h"
#include "IMessageConfig.h"
#include "IFileParsable.h"

class MainWindow;
class FileParser;

namespace Ui {
class MessageConfig;
}

class MessageConfig : public QWidget, public IMessageConfig, public IFileParsable
{
    Q_OBJECT

public:
    explicit MessageConfig(QWidget *parent = 0);
    ~MessageConfig();

    PrettyMsg prettifyMsg(const Msg &msg) const;

    MsgIDType getIDToName(const QString &name) const;
    QString getNameToID(const MsgIDType id) const;
    QColor getColorToID(const MsgIDType id) const;
    QColor getColorToIDName(const QString &name) const;
    QCompleter *createIDNameCompleter(QObject *parent = Q_NULLPTR) const;

    MsgCodeType getCodeToName(const QString &name) const;
    QString getNameToCode(const MsgCodeType code) const;
    QColor getColorToCode(const MsgCodeType code) const;
    QColor getColorToCodeName(const QString &name) const;
    QCompleter *createCodeNameCompleter(QObject *parent = Q_NULLPTR) const;


    const IDModel &getIDModel() const;
    const MsgTypeModel &getMsgTypeModel() const;

    void accept(FileParser *visitor);

private:
    Ui::MessageConfig *ui;
    void initIDTableView();
    void initMsgTypeTableView();

    friend class MainWindow;

    IDModel idModel;
    MsgTypeModel msgTypeModel;

    bool idFilterEnabled;
    bool codeFilterEnabled;
    bool timeStampFilterFromEnabled;
    bool timeStampFilterToEnabled;

signals:
    void sgnlIdAddFinished(const MsgIDType id, const QString &name, const QColor &color);
    void sgnlMsgTypeAddFinished(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color);

    void sgnl_MsgIDRepAdded(const IMsgIDRep &newMsgIDRep);
    void sgnl_MsgIDRepUpdated(const IMsgIDRep &updatedMsgIDRep);
    void sgnl_MsgIDRepRemoved(const MsgIDType relatedID);

    void sgnl_MsgCodeRepAdded(const IMsgCodeRep &newMsgCodeRep);
    void sgnl_MsgCodeRepUpdated(const IMsgCodeRep &updatedMsgCodeRep);
    void sgnl_MsgCodeRepRemoved(const MsgCodeType relatedCode);

    void sgnl_MsgDataRepAdded(const IMsgDataRep &newMsgDataRep);
    void sgnl_MsgDataRepUpdated(
            const IMsgDataRep &updatedMsgDataRep
            );
    void sgnl_MsgDataRepRemoved(
            const MsgIDType relatedID,
            const MsgCodeType relatedCode
            );
    /* void sgnl_MsgDataRepAdded(const MsgDataRep &newMsgData); */
    /* void sgnl_MsgDataRepUpdated(const MsgDataRep &updatedMsgData); */
    /* void sgnl_MsgDataRepRemoved(const MsgCodeType relatedCode); */

private slots:
    void idAddFinished(const MsgIDType id, const QString &name, const QColor &color);
    void msgTypeAddFinished(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color);

    void applyRole(UserRoleMngr::UserRole roleToSwitchTo);
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

    /* void slt_MsgDataRepAdded(const MsgDataRep &newMsgDataRep); */
    /* void slt_MsgDataRepUpdated(const MsgDataRep &updatedMsgDataRep); */
    /* void slt_MsgDataRepRemoved(const MsgCodeType relatedCode); */

};

#endif // MESSAGECONFIG_H
