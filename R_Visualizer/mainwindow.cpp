#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "msgdelegate.h"
#include "msgproxymodel.h"

#include "csvmsgpackethandler.h"

#include "devicehandler.h"

#include <QFile>
#include <QFileDialog>

#include <QDateTime>
#include <QMessageBox>


#define __DEBUG__

#ifdef __DEBUG__
#include <QDebug>
#endif //__DEBUG__

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->currentFileName = "";

    /*
     * INIT MODELS
     */

    msgTypeModel = new MsgTypeModel(this);
    connect(msgTypeModel, &MsgTypeModel::internalModelChanged, ui->msgTableView, &QTableView::reset);
    connect(msgTypeModel, &MsgTypeModel::internalModelChanged, ui->msgTableView, &QTableView::resizeRowsToContents);

    idModel = new IDModel(this);
    connect(idModel, &IDModel::internalModelChanged, ui->msgTableView, &QTableView::reset);
    connect(idModel, &IDModel::internalModelChanged, ui->msgTableView, &QTableView::resizeRowsToContents);

    this->sysOvrvwWidget = new SystemOverview(this);
    ui->tabWidget->addTab(this->sysOvrvwWidget, QString("System Overview"));

    this->sndMsgsWidget = new SendMessages(this->idModel, this->msgTypeModel, this);
    ui->tabWidget->addTab(this->sndMsgsWidget, QString("Send Messages"));

    this->msgConfigWidget = new MessageConfig(this->idModel, this->msgTypeModel, this);
    ui->tabWidget->addTab(this->msgConfigWidget, QString("Message Configuration"));

    connect(this->msgConfigWidget, &MessageConfig::sgnlIdAddFinished, this, &MainWindow::idAddFinished);
    connect(this->msgConfigWidget, &MessageConfig::sgnlMsgTypeAddFinished, this, &MainWindow::msgTypeAddFinished);


    this->initMsgsTableView();
    //    this->msgModel->setIDModel(this->idModel);
    //    this->msgModel->setMsgTypeModel(this->msgTypeModel);
    //this->initVisualizerGraphicsView();

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
    connect(this->sndMsgsWidget, &SendMessages::sigSendCANPacket, m_deviceHandler, &DeviceHandler::sltSendPacket);
    connect(m_deviceHandler, &DeviceHandler::sigPacketReceived, this->msgModel, &MsgModel::messageReceived);
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
    MsgDataT msgData = { 0x2, cntr, 0x0,cntr*2,0x0,cntr,0x4*cntr,cntr};
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xF0,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xF0,msgData));
    msgData = { 0x3, cntr, 0x0,cntr*2,0x0,cntr,0x4*cntr,cntr};
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xF0,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,msgData));
}

void MainWindow::on_actionOpen_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    currentFileName = openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    //ToDO
    // read file content
    msgModel->parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
    // parse file
    // populate ui
    // close file
    jsonOpenFile.close();
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
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    jsonSaveFile.write(this->msgModel->parseToJSON()); //ToDO check for error (-1)
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MainWindow::on_actionConnect_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__
    if (m_deviceHandler->devices().isEmpty())
    {
        QMessageBox::information(this, tr("Kein Gerät gefunden"), tr("Bitte schließen Sie ein Gerät an!"), QMessageBox::Cancel);
        return;
    }

    HID_Device device = m_deviceHandler->devices()[0];
    if (m_deviceHandler->connectTo(device))
    {
        qDebug() << "COnnected";
        m_deviceHandler->sltStartCapture();
        //m_state = Connected;
        //updateActionStates();
        //ui->statusBar->showMessage(tr("Eine Verbindung zu dem Gerät %1 wurde hergestellt. Die Analyse kann nun gestartet werden.").arg(device.product));
    }
    else
    {
        qDebug() << "Connection failed";
        //ui->statusBar->showMessage(tr("Eine Verbindung zu dem Gerät %1 konnte nicht hergestellt werden. Das Gerät ist nicht betriebsbereit.").arg(device.product));
    }
}

void MainWindow::on_actionStart_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

}

void MainWindow::on_actionStop_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

}

void MainWindow::initMsgsTableView()
{
    this->msgModel = new MsgModel(this);
    MsgProxyModel *msgProxyModel = new MsgProxyModel(this);
    msgProxyModel->setSourceModel(this->msgModel);
    connect(this->msgModel, &MsgModel::rowsInserted, msgProxyModel, &MsgProxyModel::newEntryInSourceModel);

    ui->msgTableView->setModel(msgProxyModel);
    ui->msgTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->msgTableView->horizontalHeader()->setStretchLastSection(true);
    ui->msgTableView->verticalHeader()->hide();
    ui->msgTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->msgTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->msgTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //ui->msgTableView->setItemDelegate(new MsgDelegate(ui->msgTableView));
    ui->msgTableView->setItemDelegate( new MsgDelegate(this->msgTypeModel, this->idModel, ui->msgTableView));
    //ui->msgTableView->setItemDelegateForColumn(1, new msgIDDelegate(this->idModel, ui->msgTableView));
    // scroll to the bottom as soon as a new row is inserted by
    // connecting the signal, which is fired once a row is inserted, with the scrollToBottom slot
    connect(msgModel, &MsgModel::rowsInserted, ui->msgTableView, &QTableView::scrollToBottom);
    connect(msgModel, &MsgModel::rowsInserted, ui->msgTableView, &QTableView::resizeRowsToContents);
}


void MainWindow::idAddFinished(const int id, const QString name, const QColor color)
{
    idModel->add(id, new IDRep( name, color));
}


void MainWindow::msgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color)
{
    msgTypeModel->add(code, new MsgTypeRep(code, codeName, messageFormat, color));
}

void MainWindow::applyRole(UserRoleMngr::UserRole roleToSwitchTo)
{
    if(roleToSwitchTo == UserRoleMngr::NormalUserRole)
    {


    }
    else if(roleToSwitchTo == UserRoleMngr::AdminRole)
    {


    }
}


void MainWindow::on_actionSwitch_User_Role_triggered()
{
    UserRoleMngr::UserRole role = this->userRoleMngr->getCurrentRole();
    if( role == UserRoleMngr::NormalUserRole )
    {
        role = UserRoleMngr::AdminRole;
        ui->actionSwitch_User_Role->setIcon(QIcon(":/GUI/Icons/Icons/UserNormal-32.png"));
        ui->actionSwitch_User_Role->setToolTip(QString("Switch to User Role"));
        ui->actionSwitch_User_Role->setText(QString("Switch to User Role"));
    }
    else if( role == UserRoleMngr::AdminRole )
    {
        role = UserRoleMngr::NormalUserRole;
        ui->actionSwitch_User_Role->setIcon(QIcon(":/GUI/Icons/Icons/UserAdmin-32.png"));
        ui->actionSwitch_User_Role->setToolTip(QString("Switch to Admin Role"));
        ui->actionSwitch_User_Role->setText(QString("Switch to Admin Role"));
    }

    emit this->switchUserRoles(role);
}