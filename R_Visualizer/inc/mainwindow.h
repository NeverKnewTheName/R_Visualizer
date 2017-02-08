/**
 * \file mainwindow.h
 * \author Christian Neuberger
 * \date 2017-01-31
 * 
 * \brief The main window of R_Visualizer!
 * 
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "can_packet.h"
#include "devicehandler.h"

/*
 * Custom Widgets
 */
#include "messagestream.h"
#include "messageconfig.h"
#include "messagefilter.h"
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

/**
 * \brief The main window of R_Visualizer that manages all sub windows and modules.
 * 
 * The main window is the starting point of the whole application. Every module of the application
 * is set up by the #MainWindow object.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a new #MainWindow object
     * 
     * The constructor of the #MainWindow takes care of the construction of all modules
     * and everything that is needed for the execution of R_Visualizer.
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * \brief Destructs the #MainWindows object
     * 
     * The desctructor of the #MainWindow object takes care of the destruction of all 
     * modules that were previously created and maintained by the #MainWindow.
     */
    ~MainWindow();

signals:
    void sigSendCANPacket(CAN_PacketPtr);
    void switchUserRoles(UserRoleMngr::UserRole roleToSwitchTo);
    void changedDataAcquisitionMode(bool state);
    void queryFetchRow(int direction);
    void dataReceived(Data_PacketPtr);
    void errorReceived(Error_PacketPtr);

private slots:
    /**
     * \brief Slot that is called when the NEW button was triggered
     * 
     * Drops the current session and starts a new session.
     */
    void on_actionNew_triggered();
    /**
     * \brief Slot that is called when the OPEN button was triggered
     * 
     * Opens a previously saved sesseion.
     */
    void on_actionOpen_triggered();
    /**
     * \brief Slot that is called when the SAVE button was triggered
     * 
     * Saves the current session.
     */
    void on_actionSave_triggered();
    /**
     * \brief Slot that is called when the CONNECT button was triggered
     * 
     * Initiates a connection to the interface that connects the application with the R_Sys to observe/control.
     */
    void on_actionConnect_triggered();
    /**
     * \brief Slot that is called when the START button was triggered
     * 
     * Initiates the start of message recording and displaying.
     */
    void on_actionStart_triggered();
    /**
     * \brief Slot that is called when the STOP button was triggered
     * 
     * Stops the current recording and displaying of messages.
     */
    void on_actionStop_triggered();

    void idAddFinished(const MsgIDType id, const QString &name, const QColor &color);
    void msgTypeAddFinished(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color);

    /**
     * \brief Applies the new role to the #MainWindow
     * 
     * The #UserRole affects the SwitchRoles button as well as advanced options in the menu.
     */
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
    void initDeviceHandler();

    void initMessageStream();
    void initTabs();

    void initErrorLog();

    void initUserRoleManager();

    void initMsgsTableView();

    Ui::MainWindow *ui; //!< The User Interface that was created by QT
    QString currentFileName;
    MsgStorage receivedMsgsStore;
    MsgModel msgPcktModel;

    //Maybe use pointers and dynamic allocation here... QObject hierarchy and garbage collection...
    MessageConfig msgConfigWidget;
    MessageFilter msgFilterWidget;
    MessageStream msgStream;
    SendMessages sndMsgsWidget;
    SystemOverview sysOvrvWidget;

    ErrorLogView errLogViewDiag;
    int currErrCntr;
    int totalErrCntr;

    UserRoleMngr userRoleMngr; //!< The #UserRoleMngr that keeps track of the current #UserRole
    bool m_IsConnectedToDevice; //!< Keeps track of whether an interface ot an R_Sys is connected

    DeviceHandler m_deviceHandler; /**< #DeviceHandler */
};

#endif // MAINWINDOW_H
