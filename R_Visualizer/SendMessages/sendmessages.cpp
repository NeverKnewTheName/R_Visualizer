#include "sendmessages.h"
#include "ui_sendmessages.h"

#include "msgdelegate.h"
#include "csvmsgpackethandler.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>

#include <QTimer>
#include <QThread>
#include <QDebug>

SendMessages::SendMessages(IDModel *idModel, MsgTypeModel *msgTypeModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMessages),
    idModel(idModel),
    msgTypeModel(msgTypeModel)
{
    ui->setupUi(this);
    this->msgPcktModel = new MsgModel(this);

    this->initMsgPacketTableView();

    // scroll to the bottom as soon as a new row is inserted by
    // connecting the signal, which is fired once a row is inserted, with the scrollToBottom slot
    connect(this->msgPcktModel, &MsgModel::rowsInserted, ui->sndPcktTableView, &QTableView::scrollToBottom);
    connect(this->msgPcktModel, &MsgModel::rowsInserted, ui->sndPcktTableView, &QTableView::resizeRowsToContents);
    connect(this->msgTypeModel, &MsgTypeModel::internalModelChanged, ui->sndPcktTableView, &QTableView::reset);
    connect(this->msgTypeModel, &MsgTypeModel::internalModelChanged, ui->sndPcktTableView, &QTableView::resizeRowsToContents);
    connect(this->idModel, &IDModel::internalModelChanged, ui->sndPcktTableView, &QTableView::reset);
    connect(this->idModel, &IDModel::internalModelChanged, ui->sndPcktTableView, &QTableView::resizeRowsToContents);
}

SendMessages::~SendMessages()
{
    delete ui;
}

void SendMessages::initMsgPacketTableView()
{
    ui->sndPcktTableView->setModel(this->msgPcktModel);
    ui->sndPcktTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->msgTableView->horizontalHeader()->setStretchLastSection(true);
    ui->sndPcktTableView->verticalHeader()->hide();
    ui->sndPcktTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->sndPcktTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->sndPcktTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->sndPcktTableView->setItemDelegate( new MsgDelegate(this->msgTypeModel, this->idModel, ui->sndPcktTableView));
}

void SendMessages::emitSendMsg()
{
//    emit sigSendCANPacket(packet);
}

void SendMessages::applyRole(UserRoleMngr::UserRole roleToSwitchTo)
{
    if(roleToSwitchTo == UserRoleMngr::NormalUserRole)
    {
        ui->sndPcktAddBtn->setVisible(false);
        ui->sndPcktRmvBtn->setVisible(false);
        ui->sndPcktStoreBtn->setVisible(false);
        ui->sndPcktTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }
    else if(roleToSwitchTo == UserRoleMngr::AdminRole)
    {
        ui->sndPcktAddBtn->setVisible(true);
        ui->sndPcktRmvBtn->setVisible(true);
        ui->sndPcktStoreBtn->setVisible(true);
    }
}

void SendMessages::on_sndPcktLoadBtn_clicked()
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

void SendMessages::on_sndPcktStoreBtn_clicked()
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

void SendMessages::on_sndMsgSendBtn_clicked()
{
    Data_Packet::Frame frame;
    frame.ID_Standard = ui->sndMsgIDLineEdit->text().toInt(0,16);
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

    QByteArray dataToSend;
    dataToSend.append((ui->sndMsgCodeLineEdit->text().toInt(0,16)));
    dataToSend.append(ui->sndMsgMsgLineEdit->text().toInt(0,16));

    qDebug() << dataToSend;
    frame.data = dataToSend;

    CAN_PacketPtr packet = CAN_PacketPtr(new Data_Packet());
    qSharedPointerDynamicCast<Data_Packet>(packet)->setFrame(frame);
    //this->m_deviceHandler->sltSendPacket(packet);
    qDebug() << "Send CAN message";
    emit sigSendCANPacket(packet);
    //QTimer::singleShot(0,this, &SendMessages::emitSendMsg);
}

void SendMessages::on_sndPcktSendBtn_clicked()
{
    QVector<Msg*> msgsToSend = this->msgPcktModel->getMsgs();
    for(Msg *msg : msgsToSend)
    {
        Data_Packet::Frame frame;
        frame.ID_Standard = msg->getId();
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

        frame.DLC = 8;

        QByteArray dataToSend = msg->getDataAsByteArray();
        frame.data = dataToSend;

        CAN_PacketPtr packet = CAN_PacketPtr(new Data_Packet());
        qSharedPointerDynamicCast<Data_Packet>(packet)->setFrame(frame);
        //this->m_deviceHandler->sltSendPacket(packet);
        qDebug() << "Send CAN message";
        emit sigSendCANPacket(packet);
        //QTimer::singleShot(0,this, &SendMessages::emitSendMsg);

    }
}
