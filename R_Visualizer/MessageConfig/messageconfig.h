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
    explicit MessageConfig(IDModel *idModel, MsgTypeModel *msgTypeModel, QWidget *parent = 0);
    ~MessageConfig();

signals:
    void sgnlIdAddFinished(const int id, const QString name, const QColor color);
    void sgnlMsgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color);

private:
    Ui::MessageConfig *ui;
    void initIDTableView();
    void initMsgTypeTableView();

    friend class MainWindow;

    IDModel *idModel;
    MsgTypeModel *msgTypeModel;

private slots:
    void idAddFinished(const int id, const QString name, const QColor color);
    void msgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color);

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
