#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <can_packet.h>


#include "mysquare.h"
#include "msgmodel.h"
#include "idmodel.h"
#include "msgtypemodel.h"
#include "userrolemngr.h"

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

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

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionConnect_triggered();
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_idStoreBtn_clicked();
    void on_idLoadBtn_clicked();
    void on_msgTypeSoreBtn_clicked();
    void on_msgTypeLoadBtn_clicked();
    void on_idAddBtn_clicked();

    void idAddFinished(const int id, const QString name, const QColor color);
    void msgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color);

    void applyRole(UserRoleMngr::UserRole roleToSwitchTo);

    void on_msgTypeAddBtn_clicked();

    void on_idRmvBtn_clicked();

    void on_msgTypeRmvBtn_clicked();

    void on_sndPcktLoadBtn_clicked();

    void on_sndPcktStoreBtn_clicked();

    void on_sndMsgSendBtn_clicked();


    void on_actionSwitch_User_Role_triggered();

private:
    void initMsgsTableView();
    void initIDTableView();
    void initMsgTypeTableView();
    void initMsgPacketTableView();
    void initVisualizerGraphicsView();

    Ui::MainWindow *ui;
    QString currentFileName;
    MsgModel *msgModel;
    MsgModel *msgPcktModel;
    IDModel *idModel;
    MsgTypeModel *msgTypeModel;

    UserRoleMngr *userRoleMngr;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    MySquare *square;

    DeviceHandler *m_deviceHandler; /**< Pointer to the \ref DeviceHandler */

};

#endif // MAINWINDOW_H
