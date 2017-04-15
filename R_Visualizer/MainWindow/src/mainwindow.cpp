#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * MainWindow Widgets
 */
//#include "MessageConfig.h"
//#include "messagefilter.h"
//#include "messagestream.h"
//#include "sendmessages.h"
//#include "systemoverview.h"

//#include "msgdelegate.h"
//#include "msgiddelegate.h"
//#include "msgdatadelegate.h"
//#include "filteridstore.h"

#include "errlogview.h"

#include "csvmsgpackethandler.h"

#include "devicehandler.h"

#include <QFile>
#include <QFileDialog>

#include <QDateTime>
#include <QMessageBox>
#include <QScrollBar>
#include <QHeaderView>

/* #include "csvinparser.h" */
/* #include "csvoutparser.h" */
/* #include "jsoninparser.h" */
/* #include "jsonoutparser.h" */

#include "MessageStreamWidget.h"

#define __DEBUG__

#ifdef __DEBUG__
#include <QDebug>
#endif //__DEBUG__

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentFileName(QString()),
    userRoleMngr(this),
    m_IsConnectedToDevice(false)
{
    ui->setupUi(this);

//    ui->splitter->insertWidget(0,msgStream);

    connectErrorLog();
    connectUserRoleManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMessageStreamWidget(MessageStreamWidget *msgStreamWidget)
{
    QWidget *oldMsgStream = ui->splitter->widget(0);
    if(oldMsgStream != Q_NULLPTR && oldMsgStream != ui->configTabWidget)
    {
        oldMsgStream->setParent(Q_NULLPTR);
        oldMsgStream->deleteLater();
    }
    ui->splitter->insertWidget(0,msgStreamWidget);
}

void MainWindow::appendTabMenuWidget(
        QWidget *widgetToAppend,
        const QString &widgetName
        )
{
    ui->configTabWidget->addTab(widgetToAppend,widgetName);
}

void MainWindow::setErrorDialog(ErrorLogView *errorLogDialog)
{
//    this->errLogViewDiag = errorLogDialog;
}

void MainWindow::initDeviceHandler()
{
    ui->actionStop->setDisabled(true);
    ui->actionStart->setDisabled(true);
}

void MainWindow::connectDeviceHandler()
{
//    connect(this->sndMsgsWidget, &SendMessages::sigSendCANPacket, &m_deviceHandler, &DeviceHandler::sltSendPacket/*, Qt::QueuedConnection*/);
//    connect(&m_deviceHandler, &DeviceHandler::sigPacketReceived, this, &MainWindow::messageReceived, Qt::QueuedConnection);
    /* connect(&m_deviceHandler, &DeviceHandler::sigMsgReceived, &msgModel, &MsgModel::messageReceived, Qt::QueuedConnection); */
    /* connect(this, &MainWindow::dataReceived, this->sysOvrvWidget, &SystemOverview::newMessage, Qt::QueuedConnection); */
    //connect(&m_deviceHandler, &DeviceHandler::sigErrorMsgReceived, errLogViewDiag->getErrLogModel(), &ErrLogModel::errLogMsgReceived, Qt::QueuedConnection);
    //    connect(ui->actionStart, &QAction::triggered, m_deviceHandler, &DeviceHandler::sltStartCapture);
    //    connect(ui->actionStop, &QAction::triggered, m_deviceHandler, &DeviceHandler::sltStopCapture);
}

void MainWindow::initErrorLog()
{
    ui->actionOpen_Error_Log->setText(QString("Show Error Log"));
            // (%1/%2)").arg(totalErrCntr).arg(currErrCntr));
}

void MainWindow::connectErrorLog()
{
//    connect(ui->actionOpen_Error_Log, &QAction::triggered, errLogViewDiag, &ErrorLogView::show);
}

void MainWindow::initUserRoleManager()
{
    ui->actionSwitch_User_Role->setIcon(QIcon(":/GUI/Icons/Icons/UserAdmin-32.png"));
    ui->actionSwitch_User_Role->setToolTip(QString("Switch to Admin Role"));
    ui->actionSwitch_User_Role->setText(QString("Switch to Admin Role"));
}

void MainWindow::connectUserRoleManager()
{
//    connect(this, &MainWindow::switchUserRoles, &userRoleMngr, &UserRoleMngr::switchRoles);
//    connect(this, &MainWindow::switchUserRoles, sysOvrvWidget, &SystemOverview::slt_applyRole);
//    connect(this, &MainWindow::switchUserRoles, sndMsgsWidget, &SendMessages::applyRole);
    /* connect(this, &MainWindow::switchUserRoles, msgConfigWidget, &MessageConfig::applyRole); */
    connect(this, &MainWindow::switchUserRoles, this, &MainWindow::applyRole);

    emit switchUserRoles(UserRoleMngr::NormalUserRole);
}

void MainWindow::on_actionNew_triggered()
{
}

void MainWindow::on_actionOpen_triggered()
{
/* #ifdef __DEBUG__ */
/*     qDebug() << __PRETTY_FUNCTION__ << " - Triggered"; */
/* #endif //__DEBUG__ */
/*     //disconnect(&msgModel, &MsgModel::rowAppended, ui->msgTableView, &MsgTableView::rowAdded); */

/*     QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)"); */
/*     qDebug() << openLoc; */
/*     currentFileName = openLoc; */
/*     QFile jsonOpenFile(openLoc); */
/*     if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) { */
/*         qDebug() << "error opening: " << jsonOpenFile.fileName(); */
/*     } */
/*     else */
/*     { */
/*         //ToDO */
/*         // read file content */
/*         JsonInParser jsonInParser; */
/*         jsonInParser.setJsonDocument(QJsonDocument::fromJson(jsonOpenFile.readAll())); */
/*         receivedMsgsStore.accept(&jsonInParser); */
/*         /1* msgModel.parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1) *1/ */
/*         // parse file */
/*         // populate ui */
/*         // close file */
/*     } */
/*     jsonOpenFile.close(); */
/*     /1* connect(&msgModel, &MsgModel::rowAppended, ui->msgTableView, &MsgTableView::rowAdded, Qt::QueuedConnection); *1/ */
/*     /1* ui->msgTableView->filterChanged(); *1/ */
}

void MainWindow::on_actionSave_triggered()
{
/* #ifdef __DEBUG__ */
/*     qDebug() << __PRETTY_FUNCTION__ << " - Triggered"; */
/* #endif //__DEBUG__ */

/*     if(currentFileName.isEmpty()) */
/*     { */
/*         QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)"); */
/*         qDebug() << saveLoc; */
/*         currentFileName = saveLoc; */
/*     } */
/*     QFile jsonSaveFile(currentFileName); */
/*     if(!jsonSaveFile.open(QIODevice::WriteOnly)) { */
/*         qDebug() << "error open file to save: " << jsonSaveFile.fileName(); */
/*     } */
/*     else */
/*     { */
/*         //ToDO */
/*         // extract ui content */
/*         // parse content to file format */
/*         // write to file */
/*         JsonOutParser jsonOutParser; */
/*         receivedMsgsStore.accept(&jsonOutParser); */
/*         /1* jsonOutParser.getJsonDocument().toJson() *1/ */
/*         jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson()); */
/*         /1* jsonSaveFile.write(msgModel.parseToJSON()); //ToDO check for error (-1) *1/ */
/*         // close file */
/*     } */
/*     jsonSaveFile.flush(); //always flush after write! */
/*     jsonSaveFile.close(); */
}

void MainWindow::on_actionConnect_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

//    if(m_IsConnectedToDevice)
//    {
//        //Disconnect
//        ui->actionStart->setDisabled(true);
//        ui->actionStop->setDisabled(true);
//        m_deviceHandler.disconnect();
//        qDebug() << "Disconnected";
//        m_IsConnectedToDevice = false;
//        ui->actionConnect->setIcon(QIcon(":/GUI/Icons/Icons/Network-01-32.png"));
//        ui->actionConnect->setText(QString("Connect"));
//        ui->actionConnect->setToolTip(QString("Connect to a device"));
//    }
//    else
//    {
//        //        connect
//
//        if (m_deviceHandler.devices().isEmpty())
//        {
//            QMessageBox::information(this, tr("Kein Gerät gefunden"), tr("Bitte schließen Sie ein Gerät an!"), QMessageBox::Cancel);
//            return;
//        }
//
//        HID_Device device = m_deviceHandler.devices()[0];
//        if (m_deviceHandler.connectTo(device))
//        {
//            qDebug() << "Connected";
//            ui->actionStart->setDisabled(false);
//            ui->actionStop->setDisabled(true);
//            m_IsConnectedToDevice = true;
//            ui->actionConnect->setIcon(QIcon(":/GUI/Icons/Icons/Network_Disconnected-32.png"));
//            ui->actionConnect->setText(QString("Disconnect"));
//            ui->actionConnect->setToolTip(QString("Disconnect form connected device"));
//            //m_deviceHandler.sltStartCapture();
//            //m_state = Connected;
//            //updateActionStates();
//            ui->statusBar->showMessage(QString("Connected to device: %1").arg(device.product));
//            //ui->statusBar->showMessage(tr("Eine Verbindung zu dem Gerät %1 wurde hergestellt. Die Analyse kann nun gestartet werden.").arg(device.product));
//        }
//        else
//        {
//            qDebug() << "Connection failed";
//            ui->statusBar->showMessage(QString("Connection failed"));
//            //ui->statusBar->showMessage(tr("Eine Verbindung zu dem Gerät %1 konnte nicht hergestellt werden. Das Gerät ist nicht betriebsbereit.").arg(device.product));
//        }
//    }
}

void MainWindow::on_actionStart_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    ui->actionStart->setDisabled(true);
    ui->actionStop->setDisabled(false);
//    m_deviceHandler.sltStartCapture();
}

void MainWindow::on_actionStop_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    ui->actionStart->setDisabled(false);
    ui->actionStop->setDisabled(true);
//    m_deviceHandler.sltStopCapture();
    //Somehow the device cannot be restarted without a disconnect...
    emit ui->actionConnect->triggered();
}

void MainWindow::applyRole(UserRoleMngr::UserRole roleToSwitchTo)
{
    QString RoleName;
    QIcon RoleIcon;

    if( roleToSwitchTo == UserRoleMngr::NormalUserRole )
    {
        RoleIcon = QIcon(":/GUI/Icons/Icons/UserAdmin-32.png");
        RoleName = QString("Admin");
    }
    else if( roleToSwitchTo == UserRoleMngr::AdminRole )
    {
        RoleIcon = QIcon(":/GUI/Icons/Icons/UserNormal-32.png");
        RoleName = QString("User");
    }

    ui->actionSwitch_User_Role->setIcon(RoleIcon);
    ui->actionSwitch_User_Role->setToolTip(QString("Switch to %1 Role").arg(RoleName));
    ui->actionSwitch_User_Role->setText(QString("Switch to %1 Role").arg(RoleName));
}

void MainWindow::on_actionSwitch_User_Role_triggered()
{
    UserRoleMngr::UserRole role = userRoleMngr.getCurrentRole();

    if( role == UserRoleMngr::NormalUserRole )
    {
        role = UserRoleMngr::AdminRole;
    }
    else if( role == UserRoleMngr::AdminRole )
    {
        role = UserRoleMngr::NormalUserRole;
    }

    emit this->switchUserRoles(role);
}

//void MainWindow::scrollBarMsgTableViewMoved(int position)
//{
    /* QScrollBar *vertScrollBar = ui->msgTableView->verticalScrollBar(); */

    /* if(position >= (vertScrollBar->maximum())) */
    /* { */
    /*     if(!ui->msgTableView->isAtTopEnd()) */
    /*     { */
    /*         qDebug() << "Scrollbar is at max pos"; */

    /*         disconnect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved); */
    /*         ui->msgTableView->scrollFetchRows(+1); */
    /*         if(!ui->msgTableView->isAtTopEnd()) */
    /*         { */
    /*             vertScrollBar->setSliderPosition(vertScrollBar->sliderPosition()-2); */
    /*         } */
    /*         connect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved); */
    /*     } else */
    /*     { */
    /*         emit this->changedDataAcquisitionMode(true); */
    /*     } */
    /* } */
    /* else if(position <= (vertScrollBar->minimum())) */
    /* { */
    /*     if(!ui->msgTableView->isAtBottomEnd()) */
    /*     { */
    /*         disconnect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved); */
    /*         ui->msgTableView->scrollFetchRows(-1); */
    /*         if(!ui->msgTableView->isAtBottomEnd()) */
    /*             vertScrollBar->setSliderPosition(vertScrollBar->sliderPosition()+2); */
    /*         connect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved); */
    /*         qDebug() << "Scrollbar is at min pos"; */
    /*     } */
    /* } else */
    /* { */
    /*     emit this->changedDataAcquisitionMode(false); */
    /* } */
//}

void MainWindow::on_TestPB_1_clicked()
{
    //this->msgModel->removeRow(3,QModelIndex());
}

void MainWindow::on_actionOpen_Error_Log_triggered()
{
    //this->errLogViewDiag->show();
}

//void MainWindow::messageReceived(CAN_PacketPtr ptr)
//{
//    if( ptr->type() == CAN_Packet::Data_Frame )
//    {
//        emit dataReceived(qSharedPointerDynamicCast<Data_Packet>(ptr));
//    }
//    else if( ptr->type() == CAN_Packet::Error_Frame )
//    {
//        currErrCntr++;
//        totalErrCntr++;
//        ui->actionOpen_Error_Log->setText(QString("Show Error Log (%1/%2)").arg(totalErrCntr).arg(currErrCntr));
//        emit errorReceived(qSharedPointerDynamicCast<Error_Packet>(ptr));
//    }
//}
