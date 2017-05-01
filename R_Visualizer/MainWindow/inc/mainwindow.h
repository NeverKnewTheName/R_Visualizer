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

/* #include "can_packet.h" */
/* #include "devicehandler.h" */

#include "UserRoleManager.h"

#include <QMainWindow>

class MessageStreamWidget;
class ErrorLogView;

class TimestampedMsg;

class IInterfaceHandler;

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
    explicit MainWindow(
            QWidget *parent = 0
            );
    /**
     * \brief Destructs the #MainWindows object
     * 
     * The desctructor of the #MainWindow object takes care of the destruction of all 
     * modules that were previously created and maintained by the #MainWindow.
     */
    ~MainWindow();

    void connectInterfaceHandler(IInterfaceHandler *interfaceHandler);
    void setMessageStreamWidget(QWidget *msgStreamWidget);
    void appendTabMenuWidget(
            QWidget *widgetToAppend,
            const QString &widgetName
            );

    void addToTesting(
        QWidget *widgetToTest
        );
    /* void setErrorDialog(ErrorLogView *errorLogDialog); */

signals:
    void switchUserRoles(UserRoleManagement::UserRole roleToSwitchTo);
    /* void dataReceived(Data_PacketPtr); */
    /* void errorReceived(Error_PacketPtr); */

    void sgnl_AddTestMessage(const TimestampedMsg &testMsg);

    void sgnl_ConnectToInterface();
    void sgnl_DisconnectFromInterface();
    void sgnl_StartSession();
    void sgnl_StopSession();

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

    /**
     * \brief Applies the new role to the #MainWindow
     * 
     * The #UserRole affects the SwitchRoles button as well as advanced options in the menu.
     */
    void applyRole(UserRoleManagement::UserRole roleToSwitchTo);
    void on_actionSwitch_User_Role_triggered();
    void on_TestPB_1_clicked();
    void on_actionOpen_Error_Log_triggered();


    void slt_InterfaceConnected();
    void slt_InterfaceDisconnected();
    void slt_InterfaceSessionStarted();
    void slt_InterfaceSessionStopped();

private:
    void initDeviceHandler();
    void connectDeviceHandler();

    void initErrorLog();
    void connectErrorLog();

    void initUserRoleManager();
    void connectUserRoleManager();

    Ui::MainWindow *ui; //!< The User Interface that was created by QT
    QString currentFileName;

    //Maybe use pointers and dynamic allocation here... QObject hierarchy and garbage collection...
    /*
     * Actually using the stack to allocate these widgets would be better...
     * but to accomodate the QT object hierarchy and management we use the 
     * heap to allocate these widgets. They are automatically delete according
     * to QT's object management as soon as their parent is deleted.
     * For the MessageStream and the ErrorLogView the parent is the MainWindow.
     * For the configuration widgets the parent is the QTabWidget that is
     * inside of the MainWindow.
     */
    //MessageConfig *msgConfigWidget;
    //MessageFilter *msgFilterWidget;
    //MessageStream *msgStream;
    //SendMessages *sndMsgsWidget;
    //SystemOverview *sysOvrvWidget;

    //ErrorLogView *errLogViewDiag;

    UserRoleManager userRoleMngr; //!< The #UserRoleMngr that keeps track of the current #UserRole
    bool m_IsConnectedToDevice; //!< Keeps track of whether an interface ot an R_Sys is connected
};

#endif // MAINWINDOW_H
