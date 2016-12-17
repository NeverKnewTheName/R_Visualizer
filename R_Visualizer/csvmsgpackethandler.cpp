#include "csvmsgpackethandler.h"

#include <QDebug>
#include <QRegularExpression>

CsvMsgPacketHandler::CsvMsgPacketHandler()
{

}

CsvMsgPacketHandler::CsvMsgPacketHandler(QString &csvMsgPacketString)
{
    this->parseCsvMsgPacket(csvMsgPacketString);
}

CsvMsgPacketHandler::~CsvMsgPacketHandler()
{

}

HugeQVector<Msg> CsvMsgPacketHandler::parseCsvMsgPacket(QString &csvMsgPacketString)
{
    HugeQVector<Msg> msgs;
    QStringList msgsFromPacket = csvMsgPacketString.split("\n");
    QString codeLine = msgsFromPacket.at(0);
    msgsFromPacket.removeAt(0);
    QString code = codeLine.split(";").at(0);

    qDebug() << "RegEx extracted CODE: " << code.toInt(0, 16);

    DataByteVect dataBytes;
    dataBytes.append(static_cast<quint8>(0xd));
    dataBytes.append(static_cast<quint8>(0x84));
    msgs.append(new Msg(QDateTime(), static_cast<MsgIDType>(0xFFu), static_cast<MsgCodeType>(code.toInt(0,16)), dataBytes));

    for(auto &msg : msgsFromPacket )
    {
        // first line is code;
        // other lines contain: ID(2) - DATA(2)
        if(msg.isEmpty())
            continue;
        QStringList msgAsString = msg.split(";");
        qDebug() << "msgAsString size: " << msgAsString.size();
        QString recvrIDString = msgAsString.at(0);
        unsigned int recvrID = recvrIDString.toInt();
        qDebug() << "Receiver ID" << recvrID;
        qDebug() << "Receiver ID HIGH" << ((recvrID >> 8) & 0xFFu );
        qDebug() << "Recevier ID LOW" << (recvrID & 0xFFu);
        QString dataHigh = msgAsString.at(1) + msgAsString.at(2) + msgAsString.at(3) + msgAsString.at(4) + msgAsString.at(5) + msgAsString.at(6) + msgAsString.at(7) + msgAsString.at(8);
        qDebug() << "Data High: " << dataHigh << " - " << dataHigh.toInt(0,2);
        QString dataLow = msgAsString.at(9) + msgAsString.at(10) + msgAsString.at(11) + msgAsString.at(12) + msgAsString.at(13);
        qDebug() << "Data Low: " << dataLow << " - " << dataLow.toInt(0,2);

        dataBytes.clear();
        dataBytes.append(static_cast<quint8>(((recvrID >> 8) & 0xFFu )));
        dataBytes.append(static_cast<quint8>((recvrID & 0xFFu)));
        dataBytes.append(static_cast<quint8>(dataHigh.toInt(0,2)));
        dataBytes.append(static_cast<quint8>(dataLow.toInt(0,2)));

        qDebug() << "MsgData";
        qDebug() << "RecvID LOW:" << dataBytes.at(0);
        qDebug() << "RecvID HIGH:" << dataBytes.at(1);
        msgs.append(new Msg(QDateTime(), static_cast<MsgIDType>(0xFFu), static_cast<MsgCodeType>(0x0B), dataBytes));
    }
    return msgs;
}

QString CsvMsgPacketHandler::parseToString(HugeQVector<Msg> msgs)
{
    if(!msgs.size())
        return QString("");

    QString csvFile = QString("0x").append(QString::number(msgs.at(0)->getCode(),16));
    csvFile.append(QString(";;;;;;;;;;;;;\n"));
    msgs.remove(0);
    int size = msgs.size();
    for(int i = 0; i < size; i++)
    {
        Msg *msg = msgs.at(i);
        PMsgDataStruc msgData = msg->getData();

        csvFile.append(QString("%1;%2;%3;%4;%5;%6;%7;%8;%9;%10;%11;%12;%13;%14\n")
                       .arg((msgData->DataBytes.at(0) << 8) + msgData->DataBytes.at(1))     //1
                       .arg((msgData->DataBytes.at(2) & 0x80) >> 7)              //2
                       .arg((msgData->DataBytes.at(2) & 0x40) >> 6)              //3
                       .arg((msgData->DataBytes.at(2) & 0x20) >> 5)              //4
                       .arg((msgData->DataBytes.at(2) & 0x10) >> 4)              //5
                       .arg((msgData->DataBytes.at(2) & 0x08) >> 3)              //6
                       .arg((msgData->DataBytes.at(2) & 0x04) >> 2)              //7
                       .arg((msgData->DataBytes.at(2) & 0x02) >> 1)              //8
                       .arg((msgData->DataBytes.at(2) & 0x01))                   //9
                       .arg((msgData->DataBytes.at(3) & 0x10) >> 4)              //10
                       .arg((msgData->DataBytes.at(3) & 0x08) >> 3)              //11
                       .arg((msgData->DataBytes.at(3) & 0x04) >> 2)              //12
                       .arg((msgData->DataBytes.at(3) & 0x02) >> 1)              //13
                       .arg((msgData->DataBytes.at(3) & 0x01))                   //14
                       );
    }
    return csvFile;
}


