#include "csvmsgpackethandler.h"

#include <QDebug>
#include <QRegularExpression>
#include <QDateTime>

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

CsvMsgPacketHandler::CsvMsgPacketHandler()
{

}

CsvMsgPacketHandler::~CsvMsgPacketHandler()
{

}

QVector<Msg> CsvMsgPacketHandler::parseCsvMsgPacket(QString &csvMsgPacketString)
{
    QVector<Msg> msgs;
    QStringList msgsFromPacket = csvMsgPacketString.split("\n");
    QString codeLine = msgsFromPacket.at(0);
    msgsFromPacket.removeAt(0);
    QString code = codeLine.split(";").at(0);

    qDebug() << "RegEx extracted CODE: " << code.toInt(0, 16);

    MsgDataType dataBytes;

    dataBytes.append(MsgDataByteType(0xd));
    dataBytes.append(MsgDataByteType(0x84));
    msgs.append(Msg(static_cast<MsgIDType>(0xFFu), static_cast<MsgCodeType>(code.toInt(0,16)), dataBytes));

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
        dataBytes.append(MsgDataByteType(((recvrID >> 8) & 0xFFu )));
        dataBytes.append(MsgDataByteType((recvrID & 0xFFu)));
        dataBytes.append(MsgDataByteType(dataHigh.toInt(0,2)));
        dataBytes.append(MsgDataByteType(dataLow.toInt(0,2)));

        qDebug() << "MsgData";
        qDebug() << "RecvID LOW:" << static_cast<QString>(dataBytes.at(0));
        qDebug() << "RecvID HIGH:" << static_cast<QString>(dataBytes.at(1));
        msgs.append(Msg(static_cast<MsgIDType>(0xFFu), static_cast<MsgCodeType>(0x0B), dataBytes));
    }
    return msgs;
}

QString CsvMsgPacketHandler::parseToString(QVector<Msg> msgs)
{
    if(!msgs.size())
        return QString("");

    QString csvFile = QString("0x").append(QString::number(static_cast<MsgCodeType::type>(msgs.at(0).getMsgCode()),16));
    csvFile.append(QString(";;;;;;;;;;;;;\n"));
    msgs.remove(0);
    int size = msgs.size();
    for(int i = 0; i < size; i++)
    {
        const Msg &msg = msgs.at(i);
        const MsgDataType &msgData = msg.getMsgData();

        csvFile.append(QString("%1;%2;%3;%4;%5;%6;%7;%8;%9;%10;%11;%12;%13;%14\n")
                       .arg(static_cast<QString>((msgData.at(0) << 8) + msgData.at(1)))     //1
                       .arg(static_cast<QString>((msgData.at(2) & MsgDataByteType(0x80)) >> 7))              //2
                       .arg(static_cast<QString>((msgData.at(2) & MsgDataByteType(0x40)) >> 6))              //3
                       .arg(static_cast<QString>((msgData.at(2) & MsgDataByteType(0x20)) >> 5))              //4
                       .arg(static_cast<QString>((msgData.at(2) & MsgDataByteType(0x10)) >> 4))              //5
                       .arg(static_cast<QString>((msgData.at(2) & MsgDataByteType(0x08)) >> 3))              //6
                       .arg(static_cast<QString>((msgData.at(2) & MsgDataByteType(0x04)) >> 2))              //7
                       .arg(static_cast<QString>((msgData.at(2) & MsgDataByteType(0x02)) >> 1))              //8
                       .arg(static_cast<QString>((msgData.at(2) & MsgDataByteType(0x01))))                   //9
                       .arg(static_cast<QString>((msgData.at(3) & MsgDataByteType(0x10)) >> 4))              //10
                       .arg(static_cast<QString>((msgData.at(3) & MsgDataByteType(0x08)) >> 3))              //11
                       .arg(static_cast<QString>((msgData.at(3) & MsgDataByteType(0x04)) >> 2))              //12
                       .arg(static_cast<QString>((msgData.at(3) & MsgDataByteType(0x02)) >> 1))              //13
                       .arg(static_cast<QString>((msgData.at(3) & MsgDataByteType(0x01))))                   //14
                       );
    }
    return csvFile;
}


