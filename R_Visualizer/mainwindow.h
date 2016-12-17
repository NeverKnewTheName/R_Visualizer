#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <can_packet.h>

/*
 * Custom Widgets
 */
#include "messageconfig.h"
#include "sendmessages.h"
#include "systemoverview.h"

#include "errlogview.h"

#include "msgmodel.h"
//#include "msgproxymodel.h"
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
    void dataReceived(Data_PacketPtr);
    void errorReceived(Error_PacketPtr);

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionConnect_triggered();
    void on_actionStart_triggered();
    void on_actionStop_triggered();

    void idAddFinished(const MsgIDType id, const QString &name, const QColor &color);
    void msgTypeAddFinished(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color);

    void applyRole(UserRoleMngr::UserRole roleToSwitchTo);

    void on_actionSwitch_User_Role_triggered();
    void scrollBarMsgTableViewMoved(int position);

    void autoScroll();
    void updateSlider(int direction);
    void scrollToGetMoreContent(bool enabled);

    void on_TestPB_1_clicked();

    void on_actionOpen_Error_Log_triggered();


    void messageReceived(CAN_PacketPtr ptr);

private:
    void initMsgsTableView();

    Ui::MainWindow *ui;
    QString currentFileName;
    MsgModel msgModel;
    MsgModel msgPcktModel;
    IDModel idModel;
    MsgTypeModel msgTypeModel;

    MessageConfig *msgConfigWidget;
    SendMessages *sndMsgsWidget;
    SystemOverview *sysOvrvwWidget;

    ErrorLogView *errLogViewDiag;
    int currErrCntr;
    int totalErrCntr;

    UserRoleMngr *userRoleMngr;
    bool m_IsConnectedToDevice;

    DeviceHandler *m_deviceHandler; /**< Pointer to the \ref DeviceHandler */

};

#endif // MAINWINDOW_H
