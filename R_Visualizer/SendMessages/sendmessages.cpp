#include "sendmessages.h"
#include "ui_sendmessages.h"

#include "msgdelegate.h"
#include "csvmsgpackethandler.h"
#include "idcompleter.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>

#include <QTimer>
#include <QThread>

#include <QCompleter>

#include <QDebug>

SendMessages::SendMessages(IDModel *idModel, MsgTypeModel *msgTypeModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMessages),
    idModel(idModel),
    msgTypeModel(msgTypeModel)
{
    ui->setupUi(this);
    inputMasks << "\\0\\xhh hh hh hh hh hh hh"/*HEX*/
               << "00000000000000000"/*DEC*/
               << "\\0\\bbbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb"/*BIN*/;

    QStringList items;
    items << "Hex" << "Dec" << "Bin";
    ui->msgDataFormatComboBox->addItems(items);

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

    //    IDCompleter *idCompleter = new IDCompleter(this);
    //    ui->sndMsgIDLineEdit->setCompleter(idCompleter->getCompleter());
    QCompleter *idCompleter = new QCompleter(this);
    idCompleter->setModel(this->idModel);
    idCompleter->setCompletionColumn(1);
    idCompleter->setCompletionRole(Qt::DisplayRole);
    idCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->sndMsgIDLineEdit->setCompleter(idCompleter);
    connect(ui->sndMsgIDLineEdit, &QLineEdit::textChanged, this, &SendMessages::idChanged);


    QCompleter *codeCompleter = new QCompleter(this);
    codeCompleter->setModel(this->msgTypeModel);
    codeCompleter->setCompletionColumn(1);
    codeCompleter->setCompletionRole(Qt::DisplayRole);
    codeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->sndMsgCodeLineEdit->setCompleter(codeCompleter);
    connect(ui->sndMsgCodeLineEdit, &QLineEdit::textChanged, this, &SendMessages::codeChanged);

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

QString SendMessages::parseToString(qulonglong number)
{
    int idNumericalBase = ui->msgDataFormatComboBox->currentIndex();
    if(idNumericalBase == 0)
    {
        idNumericalBase = 16;
    }
    else if(idNumericalBase == 1)
    {
        idNumericalBase = 10;
    }
    else if(idNumericalBase == 2)
    {
        idNumericalBase = 2;
    }
    return QString::number(number, idNumericalBase);
}

qulonglong SendMessages::parseToNumber(QString numericalString)
{
    int idNumericalBase;
    if(numericalString.contains("0x"))
    {
        idNumericalBase = 16;
    }
    else if(numericalString.contains("0b"))
    {
        idNumericalBase = 2;
        numericalString.replace(" ","").replace("0b","");
        qDebug() << numericalString;
    }
    else
    {
        idNumericalBase = 10;
    }
    return numericalString.toULongLong(0, idNumericalBase);
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
    QString lineEditContent = ui->sndMsgIDLineEdit->text();
    bool conversionOK;
    quint16 msgID;
    quint8 msgCode;
    quint64 msgData;

    msgID = lineEditContent.toInt(&conversionOK, (lineEditContent.startsWith("0x")) ? 16 : 0);
    if(!conversionOK)
    {
        msgID = idModel->getIDToName(lineEditContent);
    }

    frame.ID_Standard = msgID;
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

    QByteArray dataToSend;

    lineEditContent = ui->sndMsgCodeLineEdit->text();
    msgCode = lineEditContent.toInt(&conversionOK, (lineEditContent.startsWith("0x")) ? 16 : 0);
    if(!conversionOK)
    {
        msgCode = msgTypeModel->getCodeToName(lineEditContent);
    }

    qDebug() << "Msg Code: " << msgCode;
    dataToSend.append(msgCode);

    lineEditContent = ui->sndMsgMsgLineEdit->text();
    QStringList dataBytes;
    switch(ui->msgDataFormatComboBox->currentIndex())
    {
    case 0/*HEX*/:
        lineEditContent.replace(QString("0x"),"");
        dataBytes = lineEditContent.split(" ");
        for( QString &byte : dataBytes )
        {
            dataToSend.append(byte.toInt(0,16));
        }
        break;
    case 1/*DEC*/:
    {
        QByteArray extractedBytes = QString::number(lineEditContent.toULongLong(), 16).toLatin1();
        for( auto &byte : extractedBytes )
        {
            dataToSend.append(byte);
        }
    }
        break;
    case 2/*BIN*/:
        lineEditContent.replace(QString("0b"),"");
        dataBytes = lineEditContent.split(" ");
        for( QString &byte : dataBytes )
        {
            dataToSend.append(byte.toInt(0,2));
        }
        break;
    }

    //dataToSend.append(QByteArray::number(msgData, 10));
    qDebug() << "Data to send" << dataToSend.at(0);
    qDebug() << "Data to send size" << dataToSend.size();
    qDebug() << "Data to send" << dataToSend;

    frame.DLC = dataToSend.size();

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

void SendMessages::idChanged(const QString &newIDName)
{
    QColor newBackground = idModel->getColorToID(idModel->getIDToName(newIDName));
    if(!newBackground.isValid())
        newBackground = QColor(Qt::white);

    ui->sndMsgIDLineEdit->setStyleSheet(QString("QLineEdit { background : %1;}").arg(newBackground.name()));
}

void SendMessages::codeChanged(const QString &newCodeName)
{
    QColor newBackground = msgTypeModel->getColorToCode(msgTypeModel->getCodeToName(newCodeName));
    if(!newBackground.isValid())
        newBackground = QColor(Qt::white);

    ui->sndMsgCodeLineEdit->setStyleSheet(QString("QLineEdit { background : %1;}").arg(newBackground.name()));
}

void SendMessages::on_msgDataFormatComboBox_currentIndexChanged(int index)
{
    int enteredNumber = this->parseToNumber(ui->sndMsgMsgLineEdit->text());
    ui->sndMsgMsgLineEdit->setInputMask(inputMasks.at(index));
    ui->sndMsgMsgLineEdit->setText(this->parseToString(enteredNumber));
    ui->sndMsgMsgLineEdit->setFocus();
    ui->sndMsgMsgLineEdit->setCursorPosition(0);
    ui->sndMsgMsgLineEdit->selectAll();
}
