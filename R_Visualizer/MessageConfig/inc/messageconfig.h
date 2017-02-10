#ifndef MESSAGECONFIG_H
#define MESSAGECONFIG_H

#include <QWidget>
#include "idmodel.h"
#include "msgtypemodel.h"
#include "userrolemngr.h"

class MainWindow;

namespace Ui {
class MessageConfig;
}

class MessageConfig : public QWidget
{
    Q_OBJECT

public:
    explicit MessageConfig(QWidget *parent = 0);
    ~MessageConfig();

    const IDModel &getIDModel() const;
    const MsgTypeModel &getMsgTypeModel() const;

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

private slots:
    void idAddFinished(const MsgIDType id, const QString &name, const QColor &color);
    void msgTypeAddFinished(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color);

    void applyRole(UserRoleMngr::UserRole roleToSwitchTo);

    void on_idStoreBtn_clicked();
    void on_idLoadBtn_clicked();
    void on_msgTypeStoreBtn_clicked();
    void on_msgTypeLoadBtn_clicked();
    void on_idAddBtn_clicked();
    void on_msgTypeAddBtn_clicked();
    void on_idRmvBtn_clicked();
    void on_msgTypeRmvBtn_clicked();
};

#endif // MESSAGECONFIG_H
