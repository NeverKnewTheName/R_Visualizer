#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "idadddialog.h"
#include "msgtypeadddialog.h"

#include "msgdelegate.h"
#include "msgiddelegate.h"

#include "ideditordelegate.h"
#include "msgtypeeditordelegate.h"

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

    this->initIDTableView();
    this->initMsgTypeTableView();
    this->initMsgsTableView();
    this->initMsgPacketTableView();
    //    this->msgModel->setIDModel(this->idModel);
    //    this->msgModel->setMsgTypeModel(this->msgTypeModel);
    this->initVisualizerGraphicsView();

    this->userRoleMngr = new UserRoleMngr(this);
    ui->actionSwitch_User_Role->setIcon(QIcon(":/GUI/Icons/Icons/UserAdmin-32.png"));
    ui->actionSwitch_User_Role->setToolTip(QString("Switch to Admin Role"));
    ui->actionSwitch_User_Role->setText(QString("Switch to Admin Role"));
    connect(this, &MainWindow::switchUserRoles, this->userRoleMngr, &UserRoleMngr::switchRoles);
    connect(this, &MainWindow::switchUserRoles, this, &MainWindow::applyRole);

    emit switchUserRoles(UserRoleMngr::NormalUserRole);

    m_deviceHandler = new DeviceHandler();
    connect(this, &MainWindow::sigSendCANPacket, m_deviceHandler, &DeviceHandler::sltSendPacket);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete square;
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
    msgModel = new MsgModel(this);

    ui->msgTableView->setModel(msgModel);
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

void MainWindow::initIDTableView()
{
    idModel = new IDModel(this);
    ui->idTableView->setModel(idModel);
    ui->idTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->idTableView->verticalHeader()->hide();
    ui->idTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    ui->idTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->idTableView->setItemDelegate(new IDEditorDelegate(ui->idTableView));

    //ToDO scrollToBottom might not be the best slot to address....
    connect(idModel, &IDModel::rowsInserted, ui->idTableView, &QTableView::scrollToBottom);
    connect(idModel, &IDModel::internalModelChanged, ui->msgTableView, &QTableView::reset);
    connect(idModel, &IDModel::internalModelChanged, ui->sndPcktTableView, &QTableView::reset);
    connect(idModel, &IDModel::internalModelChanged, ui->msgTableView, &QTableView::resizeRowsToContents);
    connect(idModel, &IDModel::internalModelChanged, ui->sndPcktTableView, &QTableView::resizeRowsToContents);
    //DEBUG//
    //    idModel->add(0xFF, new IDRep(0xFF00, QString("Master"), QColor(Qt::blue)));
    //    idModel->add(0xF0, new IDRep(0xF000, QString("PC"), QColor(Qt::green)));
    //DEBUG//
}

void MainWindow::initMsgTypeTableView()
{
    msgTypeModel = new MsgTypeModel(this);
    ui->msgTypeTableView->setModel(msgTypeModel);
    ui->msgTypeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->msgTypeTableView->verticalHeader()->hide();
    ui->msgTypeTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    ui->msgTypeTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->msgTypeTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    ui->msgTypeTableView->setItemDelegate(new MsgTypeEditorDelegate(ui->msgTypeTableView));

    //ToDO scrollToBottom might not be the best slot to address....
    connect(msgTypeModel, &MsgTypeModel::rowsInserted, ui->msgTypeTableView, &QTableView::scrollToBottom);
    connect(msgTypeModel, &MsgTypeModel::internalModelChanged, ui->msgTableView, &QTableView::reset);
    connect(msgTypeModel, &MsgTypeModel::internalModelChanged, ui->sndPcktTableView, &QTableView::reset);
    connect(msgTypeModel, &MsgTypeModel::internalModelChanged, ui->msgTableView, &QTableView::resizeRowsToContents);
    connect(msgTypeModel, &MsgTypeModel::internalModelChanged, ui->sndPcktTableView, &QTableView::resizeRowsToContents);
    //DEBUG//
    //    msgTypeModel->add(new MsgTypeRep(0x02, QString("Start"), QColor(Qt::green)));
    //    msgTypeModel->add(new MsgTypeRep(0x03, QString("Stop"), QColor(Qt::red)));
    //DEBUG//
}

void MainWindow::initMsgPacketTableView()
{
    msgPcktModel = new MsgModel(this);

    ui->sndPcktTableView->setModel(msgPcktModel);
    ui->sndPcktTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->msgTableView->horizontalHeader()->setStretchLastSection(true);
    ui->sndPcktTableView->verticalHeader()->hide();
    ui->sndPcktTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->sndPcktTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->sndPcktTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //ui->msgTableView->setItemDelegate(new MsgDelegate(ui->msgTableView));
    ui->sndPcktTableView->setItemDelegate( new MsgDelegate(this->msgTypeModel, this->idModel, ui->msgTableView));
    //ui->sndPcktTableView->setItemDelegateForColumn(1, new msgIDDelegate(this->idModel, ui->msgTableView));
    // scroll to the bottom as soon as a new row is inserted by
    // connecting the signal, which is fired once a row is inserted, with the scrollToBottom slot
    connect(msgModel, &MsgModel::rowsInserted, ui->sndPcktTableView, &QTableView::scrollToBottom);
    connect(msgModel, &MsgModel::rowsInserted, ui->sndPcktTableView, &QTableView::resizeRowsToContents);
}

void MainWindow::initVisualizerGraphicsView()
{
    //create a new scene
    scene = new QGraphicsScene(this);
    //set the graphicsview to the newly created scene
    ui->visualizerGraphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(6);

    ellipse = scene->addEllipse(10,10,100,100,blackPen,redBrush);
    rect = scene->addRect(-100,-100,50,50,blackPen,blueBrush);

    rect->setFlag(QGraphicsItem::ItemIsMovable);

    square = new MySquare();
    scene->addItem(square);
}

void MainWindow::on_idStoreBtn_clicked()
{

    QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
    qDebug() << saveLoc;
    QFile jsonSaveFile(saveLoc);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    }
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    jsonSaveFile.write(this->idModel->parseToJSON()); //ToDO check for error (-1)
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MainWindow::on_idLoadBtn_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    //ToDO
    // read file content
    idModel->parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
    // parse file
    // populate ui
    // close file
    jsonOpenFile.close();
}

void MainWindow::on_msgTypeSoreBtn_clicked()
{
    QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
    qDebug() << saveLoc;
    QFile jsonSaveFile(saveLoc);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    }
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    jsonSaveFile.write(this->msgTypeModel->parseToJSON()); //ToDO check for error (-1)
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MainWindow::on_msgTypeLoadBtn_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    //ToDO
    // read file content
    msgTypeModel->parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
    // parse file
    // populate ui
    // close file
    jsonOpenFile.close();
}

void MainWindow::on_idAddBtn_clicked()
{
    IDAddDialog *idAddDialogg = new IDAddDialog(this);
    connect(idAddDialogg, &IDAddDialog::commit, this, &MainWindow::idAddFinished);
    idAddDialogg->exec();
}

void MainWindow::idAddFinished(const int id, const QString name, const QColor color)
{
    idModel->add(id, new IDRep( name, color));
}

void MainWindow::on_msgTypeAddBtn_clicked()
{
    MsgTypeAddDialog *msgTypeAddDialogg = new MsgTypeAddDialog(this);
    connect(msgTypeAddDialogg, &MsgTypeAddDialog::commit, this, &MainWindow::msgTypeAddFinished);
    msgTypeAddDialogg->exec();
}

void MainWindow::msgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color)
{
    msgTypeModel->add(code, new MsgTypeRep(code, codeName, messageFormat, color));
}

void MainWindow::applyRole(UserRoleMngr::UserRole roleToSwitchTo)
{
    if(roleToSwitchTo == UserRoleMngr::NormalUserRole)
    {
        ui->idAddBtn->setVisible(false);
        ui->idRmvBtn->setVisible(false);
        ui->idStoreBtn->setVisible(false);
        ui->idTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->msgTypeAddBtn->setVisible(false);
        ui->msgTypeRmvBtn->setVisible(false);
        ui->msgTypeSoreBtn->setVisible(false);
        ui->msgTypeTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->sndPcktAddBtn->setVisible(false);
        ui->sndPcktRmvBtn->setVisible(false);
        ui->sndPcktStoreBtn->setVisible(false);
        ui->sndPcktTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }
    else if(roleToSwitchTo == UserRoleMngr::AdminRole)
    {
        ui->idAddBtn->setVisible(true);
        ui->idRmvBtn->setVisible(true);
        ui->idStoreBtn->setVisible(true);
        ui->idTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
        ui->msgTypeAddBtn->setVisible(true);
        ui->msgTypeRmvBtn->setVisible(true);
        ui->msgTypeSoreBtn->setVisible(true);
        ui->msgTypeTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
        ui->sndPcktAddBtn->setVisible(true);
        ui->sndPcktRmvBtn->setVisible(true);
        ui->sndPcktStoreBtn->setVisible(true);
    }
}


void MainWindow::on_idRmvBtn_clicked()
{
    QModelIndexList selection = ui->idTableView->selectionModel()->selectedRows();
    for(auto &selectedItem : selection)
    {
        qDebug() << "Remove row: " << selectedItem.row() << " from IDModel";
        this->idModel->removeRow(selectedItem.row(), QModelIndex());
    }
}

void MainWindow::on_msgTypeRmvBtn_clicked()
{
    QModelIndexList selection = ui->msgTypeTableView->selectionModel()->selectedRows();
    for(auto &selectedItem : selection)
    {
        qDebug() << "Remove row: " << selectedItem.row() << " from MsgTypeModel";
        this->msgTypeModel->removeRow(selectedItem.row(), QModelIndex());
    }
}

void MainWindow::on_sndPcktLoadBtn_clicked()
{
    QString fileFormat;
    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), QString("CSV File (*.csv);;JSON File (*.json)"),&fileFormat);
    qDebug() << openLoc;
    QFile csvOpenFile(openLoc);
    if(!csvOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << csvOpenFile.fileName();
    }
    //ToDO
    // read file content
    if(!fileFormat.compare(QString("CSV File (*.csv)")))
    {
        CsvMsgPacketHandler csvMsgPacketParser;
        QString msgPacket = QString(csvOpenFile.readAll());
        this->msgPcktModel->setMsgs(csvMsgPacketParser.parseCsvMsgPacket(msgPacket));
    } else if(!fileFormat.compare(QString("JSON File (*.json)")))
    {
        this->msgPcktModel->parseFromJSON(csvOpenFile.readAll());
    }
    csvOpenFile.close();
    //    for( Msg *msg : csvMsgPacketParser.getMsgs())
    //    {
    //        qDebug() << msg->getDataAsString();
    //    }
    //    ui->sndPcktTableView->reset();
    // parse file
    // populate ui
    // close file
}

void MainWindow::on_sndPcktStoreBtn_clicked()
{
    QString fileFormat;
    QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), QString("CSV File (*.csv);;JSON File (*.json)"),&fileFormat);
    qDebug() << saveLoc;
    QFile csvSaveFile(saveLoc);
    if(!csvSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << csvSaveFile.fileName();
    }
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    if(!fileFormat.compare(QString("CSV File (*.csv)")))
    {
        CsvMsgPacketHandler csvMsgPacketParser;
        csvSaveFile.write(csvMsgPacketParser.parseToString(this->msgPcktModel->getMsgs()).toUtf8()); //ToDO check for error (-1)
        // close file
    } else if(!fileFormat.compare(QString("JSON File (*.json)")))
    {
        csvSaveFile.write(this->msgPcktModel->parseToJSON());
    }
    csvSaveFile.flush(); //always flush after write!
    csvSaveFile.close();
}

void MainWindow::on_sndMsgSendBtn_clicked()
{
    Data_Packet::Frame frame;
    frame.ID_Standard = 0xF0;
    //    if (ui->cbIDE->isChecked())
    //    {
    //        frame.IDE = 1;
    //        frame.SRR = 1;
    //        frame.ID_Extended = ui->sbIDExt->value();
    //    }
    //    else
    //    {
    frame.IDE = 0;
    frame.SRR = 0;
    frame.ID_Extended = 0;
    //    }

    frame.RTR = 0;

    frame.DLC = 4;

    frame.data = QByteArray::fromHex("0xF1234F");

    CAN_PacketPtr packet = CAN_PacketPtr(new Data_Packet());
    qSharedPointerDynamicCast<Data_Packet>(packet)->setFrame(frame);
    //this->m_deviceHandler->sltSendPacket(packet);
    emit sigSendCANPacket(packet);
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
