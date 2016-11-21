#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "msgdelegate.h"
#include "filteridstore.h"

#include "errlogview.h"

#include "csvmsgpackethandler.h"

#include "devicehandler.h"

#include <QFile>
#include <QFileDialog>

#include <QDateTime>
#include <QMessageBox>
#include <QScrollBar>
#include <QHeaderView>

#define __DEBUG__

#ifdef __DEBUG__
#include <QDebug>
#endif //__DEBUG__

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    msgModel(this),
    msgPcktModel(this),
    idModel(this),
    msgTypeModel(this),
    currErrCntr(0),
    totalErrCntr(0),
    m_IsConnectedToDevice(false)
{
    ui->setupUi(this);
    currentFileName = "";

    /*
     * INIT MODELS
     */

    connect(&msgTypeModel, &MsgTypeModel::internalModelChanged, ui->msgTableView, &QTableView::resizeRowsToContents);

    connect(&idModel, &IDModel::internalModelChanged, ui->msgTableView, &QTableView::resizeRowsToContents);

    this->sysOvrvwWidget = new SystemOverview(this);
    ui->tabWidget->addTab(sysOvrvwWidget, QString("System Overview"));

    this->sndMsgsWidget = new SendMessages(idModel, msgTypeModel, this);
    ui->tabWidget->addTab(sndMsgsWidget, QString("Send Messages"));

    this->msgConfigWidget = new MessageConfig(idModel, msgTypeModel, this);
    ui->tabWidget->addTab(msgConfigWidget, QString("Message Configuration"));

    connect(this->msgConfigWidget, &MessageConfig::sgnlIdAddFinished, this, &MainWindow::idAddFinished);
    connect(this->msgConfigWidget, &MessageConfig::sgnlMsgTypeAddFinished, this, &MainWindow::msgTypeAddFinished);

    this->errLogViewDiag = new ErrorLogView(this);
    connect(ui->actionOpen_Error_Log, &QAction::triggered, this->errLogViewDiag, &ErrorLogView::show);
    ui->actionOpen_Error_Log->setText(QString("Show Error Log (%1/%2)").arg(totalErrCntr).arg(currErrCntr));

    this->initMsgsTableView();

    this->userRoleMngr = new UserRoleMngr(this);
    ui->actionSwitch_User_Role->setIcon(QIcon(":/GUI/Icons/Icons/UserAdmin-32.png"));
    ui->actionSwitch_User_Role->setToolTip(QString("Switch to Admin Role"));
    ui->actionSwitch_User_Role->setText(QString("Switch to Admin Role"));
    connect(this, &MainWindow::switchUserRoles, this->userRoleMngr, &UserRoleMngr::switchRoles);
    connect(this, &MainWindow::switchUserRoles, this->sysOvrvwWidget, &SystemOverview::applyRole);
    connect(this, &MainWindow::switchUserRoles, this->sndMsgsWidget, &SendMessages::applyRole);
    connect(this, &MainWindow::switchUserRoles, this->msgConfigWidget, &MessageConfig::applyRole);
    connect(this, &MainWindow::switchUserRoles, this, &MainWindow::applyRole);

    emit switchUserRoles(UserRoleMngr::NormalUserRole);

    m_deviceHandler = new DeviceHandler();
    connect(this->sndMsgsWidget, &SendMessages::sigSendCANPacket, m_deviceHandler, &DeviceHandler::sltSendPacket/*, Qt::QueuedConnection*/);

    connect(m_deviceHandler, &DeviceHandler::sigPacketReceived, this, &MainWindow::messageReceived, Qt::QueuedConnection);

    connect(m_deviceHandler, &DeviceHandler::sigMsgReceived, &msgModel, &MsgModel::messageReceived, Qt::QueuedConnection);
    connect(this, &MainWindow::dataReceived, this->sysOvrvwWidget, &SystemOverview::newMessage, Qt::QueuedConnection);
    connect(m_deviceHandler, &DeviceHandler::sigErrorMsgReceived, this->errLogViewDiag->getErrLogModel(), &ErrLogModel::errLogMsgReceived, Qt::QueuedConnection);
    //    connect(ui->actionStart, &QAction::triggered, m_deviceHandler, &DeviceHandler::sltStartCapture);
    //    connect(ui->actionStop, &QAction::triggered, m_deviceHandler, &DeviceHandler::sltStopCapture);
    ui->actionStop->setDisabled(true);
    ui->actionStart->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_deviceHandler;
}


void MainWindow::on_actionNew_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__
    //TESTING ONLY
    static int cntr = 0;
    ++cntr;
    DataByteVect msgData;
    msgData.append(static_cast<quint8>(cntr));
    msgData.append(static_cast<quint8>(0x0));
    msgData.append(static_cast<quint8>(cntr*2));
    msgData.append(static_cast<quint8>(0x0));
    msgData.append(static_cast<quint8>(cntr));
    msgData.append(static_cast<quint8>(0x4*cntr));
    msgData.append(static_cast<quint8>(cntr));

    msgModel.addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,0x2,msgData));
//    msgModel.addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xF0,0x2,msgData));
//    msgModel.addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xF0,0x2,msgData));
//    msgData.clear();

//    msgData.append(static_cast<quint8>(cntr));
//    msgData.append(static_cast<quint8>(0x0));
//    msgData.append(static_cast<quint8>(cntr*2));
//    msgData.append(static_cast<quint8>(0x0));
//    msgData.append(static_cast<quint8>(cntr));
//    msgData.append(static_cast<quint8>(0x4*cntr));
//    msgData.append(static_cast<quint8>(cntr));

//    msgModel.addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,0x3,msgData));
//    msgModel.addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,0x3,msgData));
//    msgModel.addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xF0,0x3,msgData));
//    msgModel.addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,0x3,msgData));
}

void MainWindow::on_actionOpen_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__
    disconnect(&msgModel, &MsgModel::rowAppended, ui->msgTableView, &MsgTableView::rowAdded);

    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    currentFileName = openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    else
    {
        //ToDO
        // read file content
        msgModel.parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
        // parse file
        // populate ui
        // close file
    }
    jsonOpenFile.close();
    connect(&msgModel, &MsgModel::rowAppended, ui->msgTableView, &MsgTableView::rowAdded, Qt::QueuedConnection);
    ui->msgTableView->filterChanged();
}

void MainWindow::on_actionSave_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    if(currentFileName.isEmpty())
    {
        QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
        qDebug() << saveLoc;
        currentFileName = saveLoc;
    }
    QFile jsonSaveFile(currentFileName);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    }
    else
    {
        //ToDO
        // extract ui content
        // parse content to file format
        // write to file
        jsonSaveFile.write(msgModel.parseToJSON()); //ToDO check for error (-1)
        // close file
    }
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MainWindow::on_actionConnect_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    if(m_IsConnectedToDevice)
    {
        //Disconnect
        ui->actionStart->setDisabled(true);
        ui->actionStop->setDisabled(true);
        m_deviceHandler->disconnect();
        qDebug() << "Disconnected";
        m_IsConnectedToDevice = false;
        ui->actionConnect->setIcon(QIcon(":/GUI/Icons/Icons/Network-01-32.png"));
        ui->actionConnect->setText(QString("Connect"));
        ui->actionConnect->setToolTip(QString("Connect to a device"));
    }
    else
    {
        //        connect

        if (m_deviceHandler->devices().isEmpty())
        {
            QMessageBox::information(this, tr("Kein Gerät gefunden"), tr("Bitte schließen Sie ein Gerät an!"), QMessageBox::Cancel);
            return;
        }

        HID_Device device = m_deviceHandler->devices()[0];
        if (m_deviceHandler->connectTo(device))
        {
            qDebug() << "Connected";
            ui->actionStart->setDisabled(false);
            ui->actionStop->setDisabled(true);
            m_IsConnectedToDevice = true;
            ui->actionConnect->setIcon(QIcon(":/GUI/Icons/Icons/Network_Disconnected-32.png"));
            ui->actionConnect->setText(QString("Disconnect"));
            ui->actionConnect->setToolTip(QString("Disconnect form connected device"));
            //m_deviceHandler->sltStartCapture();
            //m_state = Connected;
            //updateActionStates();
            ui->statusBar->showMessage(QString("Connected to device: %1").arg(device.product));
            //ui->statusBar->showMessage(tr("Eine Verbindung zu dem Gerät %1 wurde hergestellt. Die Analyse kann nun gestartet werden.").arg(device.product));
        }
        else
        {
            qDebug() << "Connection failed";
            ui->statusBar->showMessage(QString("Connection failed"));
            //ui->statusBar->showMessage(tr("Eine Verbindung zu dem Gerät %1 konnte nicht hergestellt werden. Das Gerät ist nicht betriebsbereit.").arg(device.product));
        }
    }
}

void MainWindow::on_actionStart_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    ui->actionStart->setDisabled(true);
    ui->actionStop->setDisabled(false);
    m_deviceHandler->sltStartCapture();
}

void MainWindow::on_actionStop_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    ui->actionStart->setDisabled(false);
    ui->actionStop->setDisabled(true);
    m_deviceHandler->sltStopCapture();
    //Somehow the device cannot be restarted without a disconnect...
    emit ui->actionConnect->triggered();
}

#define FILTER_PROXY_VIEW
void MainWindow::initMsgsTableView()
{
    FilterIDStore &filterIDModel = this->msgConfigWidget->getFilterIDModel();
    FilterCodeStore &filterCodeModel = this->msgConfigWidget->getFilterCodeModel();
    FilterTimestampStore &filterTimestampModel = this->msgConfigWidget->getFilterTimestampModel();
    ui->msgTableView->setFilterIDModel(&filterIDModel);
    ui->msgTableView->setFilterCodeModel(&filterCodeModel);
    ui->msgTableView->setFilterTimestampModel(&filterTimestampModel);

    connect(this->msgConfigWidget, &MessageConfig::filterIDstateChange, ui->msgTableView, &MsgTableView::changeIDFilterEnabled);
    connect(this->msgConfigWidget, &MessageConfig::filterCodestateChange, ui->msgTableView, &MsgTableView::changeCodeFilterEnabled);
    connect(this->msgConfigWidget, &MessageConfig::filterTimestampFromStateChange, ui->msgTableView, &MsgTableView::changeTimestampFromFilterEnabled);
    connect(this->msgConfigWidget, &MessageConfig::filterTimestampToStateChange, ui->msgTableView, &MsgTableView::changeTimestampToFilterEnabled);

    connect(&filterIDModel, &FilterIDStore::internalModelChanged, ui->msgTableView, &MsgTableView::filterChanged);
    connect(&filterCodeModel, &FilterCodeStore::internalModelChanged, ui->msgTableView, &MsgTableView::filterChanged);
    connect(&filterTimestampModel, &FilterTimestampStore::internalModelChanged, ui->msgTableView, &MsgTableView::filterChanged);

    connect(ui->msgTableView, &MsgTableView::invisibleRows, this, &MainWindow::scrollToGetMoreContent);
    // queued connection for the case that many rows are added at once and could not be rendered either way
    connect(&msgModel, &MsgModel::rowAppended, ui->msgTableView, &MsgTableView::rowAdded, Qt::QueuedConnection);
    connect(&msgModel, &MsgModel::modelReset, ui->msgTableView, &MsgTableView::reset);
    connect(this, &MainWindow::changedDataAcquisitionMode, ui->msgTableView, &MsgTableView::scrollContinuousChange);
    ui->msgTableView->setModel(&msgModel);

    QHeaderView *horzHeader = ui->msgTableView->horizontalHeader();
    horzHeader->setSectionResizeMode(0, QHeaderView::Fixed);
    horzHeader->resizeSection(0, 150);
    horzHeader->setSectionResizeMode(1, QHeaderView::Interactive);
    horzHeader->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->msgTableView->verticalHeader()->hide();

    ui->msgTableView->setAlternatingRowColors(true);
    ui->msgTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->msgTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->msgTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);

    ui->msgTableView->setItemDelegate( new MsgDelegate(msgTypeModel, idModel, ui->msgTableView));
}


void MainWindow::idAddFinished(const MsgIDType/*ToDO MsgIDType*/ id, const QString &name, const QColor &color)
{
    IDRep IdRepToAdd(id, name, color);
    idModel.add(IdRepToAdd);
}


void MainWindow::msgTypeAddFinished(const MsgCodeType/*ToDo MsgCodeType*/ code, const QString &codeName, const QString &messageFormat, const QColor &color)
{
    MsgTypeRep MsgTypeRepToAdd(code, codeName, messageFormat, color);
    msgTypeModel.add(MsgTypeRepToAdd);
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
    UserRoleMngr::UserRole role = this->userRoleMngr->getCurrentRole();

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

void MainWindow::scrollBarMsgTableViewMoved(int position)
{
    QScrollBar *vertScrollBar = ui->msgTableView->verticalScrollBar();

    if(position >= (vertScrollBar->maximum()))
    {
        if(!ui->msgTableView->isAtTopEnd())
        {
            qDebug() << "Scrollbar is at max pos";

            disconnect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
            ui->msgTableView->scrollFetchRows(+1);
            if(!ui->msgTableView->isAtTopEnd())
            {
                vertScrollBar->setSliderPosition(vertScrollBar->sliderPosition()-2);
            }
            connect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
        } else
        {
            emit this->changedDataAcquisitionMode(true);
        }
    }
    else if(position <= (vertScrollBar->minimum()))
    {
        if(!ui->msgTableView->isAtBottomEnd())
        {
            disconnect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
            ui->msgTableView->scrollFetchRows(-1);
            if(!ui->msgTableView->isAtBottomEnd())
                vertScrollBar->setSliderPosition(vertScrollBar->sliderPosition()+2);
            connect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
            qDebug() << "Scrollbar is at min pos";
        }
    } else
    {
        emit this->changedDataAcquisitionMode(false);
    }
}

void MainWindow::autoScroll()
{
    QTimer::singleShot(0,ui->msgTableView, &QTableView::scrollToBottom);
}

void MainWindow::updateSlider(int direction)
{
    qDebug() << __PRETTY_FUNCTION__;
    QScrollBar *vertScrollBar = ui->msgTableView->verticalScrollBar();
    vertScrollBar->setSliderPosition(vertScrollBar->sliderPosition()+direction);
}

void MainWindow::scrollToGetMoreContent(bool enabled)
{
    if(enabled)
        connect(ui->msgTableView->verticalScrollBar(), &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
    else
        disconnect(ui->msgTableView->verticalScrollBar(), &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
}

void MainWindow::on_TestPB_1_clicked()
{
    //this->msgModel->removeRow(3,QModelIndex());
}

void MainWindow::on_actionOpen_Error_Log_triggered()
{
    //this->errLogViewDiag->show();
}

void MainWindow::messageReceived(CAN_PacketPtr ptr)
{
    if( ptr->type() == CAN_Packet::Data_Frame )
    {
        emit dataReceived(qSharedPointerDynamicCast<Data_Packet>(ptr));
    }
    else if( ptr->type() == CAN_Packet::Error_Frame )
    {
        currErrCntr++;
        totalErrCntr++;
        ui->actionOpen_Error_Log->setText(QString("Show Error Log (%1/%2)").arg(totalErrCntr).arg(currErrCntr));
        emit errorReceived(qSharedPointerDynamicCast<Error_Packet>(ptr));
    }
}
