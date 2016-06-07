#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <can_packet.h>

/*
 * Custom Widgets
 */
#include "MessageConfig/messageconfig.h"
#include "SendMessages/sendmessages.h"
#include "SystemOverview/systemoverview.h"

#include "msgmodel.h"
#include "msgproxymodel.h"
#include "idmodel.h"
#include "msgtypemodel.h"

#include "userrolemngr.h"

#include <QMainWindow>

class DeviceHandler;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sigSendCANPacket(CAN_PacketPtr);
    void switchUserRoles(UserRoleMngr::UserRole roleToSwitchTo);
    void changedDataAcquisitionMode(bool state);
    void queryFetchRow(int direction);

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionConnect_triggered();
    void on_actionStart_triggered();
    void on_actionStop_triggered();

    void idAddFinished(const int id, const QString name, const QColor color);
    void msgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color);

    void applyRole(UserRoleMngr::UserRole roleToSwitchTo);

    void on_actionSwitch_User_Role_triggered();
    void scrollBarMsgTableViewMoved(int position);

    void autoScroll();
    void updateSlider(int direction);
    void scrollToGetMoreContent(bool enabled);

private:
    void initMsgsTableView();

    Ui::MainWindow *ui;
    QString currentFileName;
    MsgModel *msgModel;
    MsgProxyModel *msgProxyModel;
    MsgModel *msgPcktModel;
    IDModel *idModel;
    MsgTypeModel *msgTypeModel;

    MessageConfig *msgConfigWidget;
    SendMessages *sndMsgsWidget;
    SystemOverview *sysOvrvwWidget;

    UserRoleMngr *userRoleMngr;

    DeviceHandler *m_deviceHandler; /**< Pointer to the \ref DeviceHandler */

};

#endif // MAINWINDOW_H
