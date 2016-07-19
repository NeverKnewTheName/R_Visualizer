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
               << "000 000 000 000 000 000 000 000"/*DEC Data*/
               << "00000000000000000"/*DEC Value*/
               << "\\0\\bbbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb"/*BIN*/;

    QStringList items;
    items << "Hex" << "Dec Data" << "Dec Value" << "Bin";
    ui->msgDataFormatComboBox->addItems(items);

    currentDataFormatIndex = ui->msgDataFormatComboBox->currentIndex();

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

QByteArray SendMessages::extractMsgData(QString msgDataString, int formatIndex)
{
    QByteArray extractedDataBytes;
    QStringList dataBytes;
    msgDataString = msgDataString.simplified();

    switch(formatIndex)
    {
    case 0/*HEX*/:
        msgDataString.replace(QString("0x"),"");
        if(msgDataString.isEmpty())
            break;
        dataBytes = msgDataString.split(" ");
        for( QString &byte : dataBytes )
        {
            extractedDataBytes.append(byte.toInt(0,16));
        }
        break;
    case 1/*DEC Data*/:
    {
        if(msgDataString.isEmpty())
            break;
        dataBytes = msgDataString.split(" ");
        for( auto &byte : dataBytes )
        {
            quint8 byteVal = byte.toInt(0,10);
            extractedDataBytes.append(byteVal);
        }
    }
        break;
    case 2/*DEC Value*/:
    {
        qulonglong extractedNumber = msgDataString.toULongLong(0,10);

        if(!extractedNumber)
            break;
        extractedDataBytes.prepend((extractedNumber & 0x00000000000000FF)>>0x00);

        if(!(extractedNumber & 0xFFFFFFFFFFFFFF00))
            break;
        extractedDataBytes.prepend((extractedNumber & 0x000000000000FF00)>>0x08);

        if(!(extractedNumber & 0xFFFFFFFFFFFF0000))
            break;
        extractedDataBytes.prepend((extractedNumber & 0x0000000000FF0000)>>0x10);

        if(!(extractedNumber & 0xFFFFFFFFFF000000))
            break;
        extractedDataBytes.prepend((extractedNumber & 0x00000000FF000000)>>0x18);

        if(!(extractedNumber & 0xFFFFFFFF00000000))
            break;
        extractedDataBytes.prepend((extractedNumber & 0x000000FF00000000)>>0x20);

        if(!(extractedNumber & 0xFFFFFF0000000000))
            break;
        extractedDataBytes.prepend((extractedNumber & 0x0000FF0000000000)>>0x28);

        if(!(extractedNumber & 0xFFFF000000000000))
            break;
        extractedDataBytes.prepend((extractedNumber & 0x00FF000000000000)>>0x30);

        if(!(extractedNumber & 0xFF00000000000000))
            break;
        extractedDataBytes.prepend((extractedNumber & 0xFF00000000000000)>>0x38);
    }
        break;
    case 3/*BIN*/:
        msgDataString.replace(QString("0b"),"");
        if(msgDataString.isEmpty())
            break;
        dataBytes = msgDataString.split(" ");
        for( QString &byte : dataBytes )
        {
            extractedDataBytes.append(byte.toInt(0,2));
        }
        break;
    }
    qDebug() << "Extracted Data:";
    for(auto byte : extractedDataBytes)
        qDebug() << byte;

    return extractedDataBytes;
}

QString SendMessages::createMsgData(QByteArray msgDataBytes, int formatIndex)
{
    QString newMsgDataString;

    switch(formatIndex)
    {
    case 0/*HEX*/:
        newMsgDataString.append("0x");
        for( auto &byte : msgDataBytes )
        {
            quint8 _8bitByte = byte;
            newMsgDataString.append(QString("%1").arg((uint)_8bitByte,2,16,QLatin1Char('0')));
            newMsgDataString.append(" ");
        }
        break;
    case 1/*DEC Data*/:
    {
        for( auto &byte : msgDataBytes )
        {
            quint8 _8bitByte = byte;
            newMsgDataString.append(QString("%1").arg((uint)_8bitByte,3,10));
            newMsgDataString.append(" ");
        }
    }
        break;
    case 2/*DEC Value*/:
    {
        qulonglong value = 0;
        unsigned int cntr = 0;
        unsigned int maxSize = msgDataBytes.size();
        while(cntr < maxSize)
        {
            int shift = (((maxSize-1) - cntr)*0x8u);
            qulonglong data = ((quint8)msgDataBytes.at(cntr));
            value += (data << shift);
            qDebug() << "Value" << value << "Counter" << cntr << "Shift" << shift << "Data Byte" << data;
            cntr++;
        }
        newMsgDataString.append(QString("%1").arg(value));
    }
        break;
    case 3/*BIN*/:
        newMsgDataString.append("0b");
        for( auto &byte : msgDataBytes )
        {
            quint8 _8bitByte = byte;
            newMsgDataString.append(QString("%1").arg((uint)_8bitByte,8,2,QLatin1Char('0')));
            newMsgDataString.append(" ");
        }
        break;
    }

    return newMsgDataString;
}

void SendMessages::convertMsgData(QString &msgDataString, int oldIndex, int newIndex)
{
    ui->sndMsgMsgLineEdit->setText(this->createMsgData(this->extractMsgData(msgDataString, oldIndex), newIndex));
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

    ui->sndPcktTableView->hideColumn(0);
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
    else if((idNumericalBase == 1) || (idNumericalBase == 2))
    {
        idNumericalBase = 10;
    }
    else if(idNumericalBase == 3)
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
    else
    {
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
    else
    {
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

    lineEditContent = ui->sndMsgMsgLineEdit->text().simplified();
    dataToSend = this->extractMsgData(lineEditContent, this->currentDataFormatIndex);

    lineEditContent = ui->sndMsgCodeLineEdit->text();
    msgCode = lineEditContent.toInt(&conversionOK, (lineEditContent.startsWith("0x")) ? 16 : 0);
    if(!conversionOK)
    {
        msgCode = msgTypeModel->getCodeToName(lineEditContent);
    }

    qDebug() << "Msg Code: " << msgCode;
    dataToSend.prepend(msgCode);

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
    HugeQVector<Msg> msgsToSend = this->msgPcktModel->getMsgs();
    int size = msgsToSend.size();
    for( int i = 0; i < size; i++)
    {
        Msg *msg = msgsToSend.at(i);
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
    QString msgData = ui->sndMsgMsgLineEdit->text();
    ui->sndMsgMsgLineEdit->setInputMask("");
    convertMsgData(msgData, currentDataFormatIndex, index);
    ui->sndMsgMsgLineEdit->setInputMask(inputMasks.at(index));
    ui->sndMsgMsgLineEdit->setFocus();
    ui->sndMsgMsgLineEdit->setCursorPosition(0);
    ui->sndMsgMsgLineEdit->selectAll();
    currentDataFormatIndex = index;
}

void SendMessages::on_sndPcktClrBtn_clicked()
{
    this->msgPcktModel->clear();
}

void SendMessages::on_sndMsgAddToPacketBtn_clicked()
{
    quint16 msgID;
    quint8 msgCode;
    QByteArray data;
    QString lineEditContent;
    bool conversionOK;

    lineEditContent = ui->sndMsgIDLineEdit->text();
    msgID = lineEditContent.toInt(&conversionOK, (lineEditContent.startsWith("0x")) ? 16 : 0);
    if(!conversionOK)
    {
        msgID = idModel->getIDToName(lineEditContent);
    }

    lineEditContent = ui->sndMsgMsgLineEdit->text().simplified();
    data = this->extractMsgData(lineEditContent, this->currentDataFormatIndex);

    lineEditContent = ui->sndMsgCodeLineEdit->text();
    msgCode = lineEditContent.toInt(&conversionOK, (lineEditContent.startsWith("0x")) ? 16 : 0);
    if(!conversionOK)
    {
        msgCode = msgTypeModel->getCodeToName(lineEditContent);
    }

    data.prepend(msgCode);

    this->msgPcktModel->addMsg(new Msg(QDateTime(),msgID,data));
}

void SendMessages::on_sndMsgMsgLineEdit_returnPressed()
{
    emit ui->sndMsgSendBtn->clicked();
}

void SendMessages::on_sndPcktRmvBtn_clicked()
{
    QItemSelectionModel *selectionModel = ui->sndPcktTableView->selectionModel();
    QModelIndexList selectionIndexList = selectionModel->selectedRows();
    if(selectionIndexList.size())
    {
        this->msgPcktModel->removeRows(selectionIndexList.first().row(), selectionIndexList.size());
    }
    //this->msgPcktModel->removeRow(ui->sndPcktTableView->selectionModel()->currentIndex().row());
}
