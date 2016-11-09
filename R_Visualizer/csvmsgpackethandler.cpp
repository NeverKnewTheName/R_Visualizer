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
    MsgDataT msgData = {
        static_cast<quint8>(code.toInt(0, 16)),
        static_cast<quint8>(0xd),
        static_cast<quint8>(0x84),
        static_cast<quint8>(0),
        static_cast<quint8>(0),
        static_cast<quint8>(0),
        static_cast<quint8>(0),
        static_cast<quint8>(0)
    };

    msgs.append(new Msg(QDateTime(), 0xFF, msgData));
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
        msgData = {
            static_cast<quint8>(0x0B),
            static_cast<quint8>(((recvrID >> 8) & 0xFFu )),
            static_cast<quint8>((recvrID & 0xFFu)),
            static_cast<quint8>(dataHigh.toInt(0,2)),
            static_cast<quint8>(dataLow.toInt(0,2)),
            static_cast<quint8>(0),
            static_cast<quint8>(0),
            static_cast<quint8>(0)
        };
        qDebug() << "MsgData";
        qDebug() << "RecvID LOW:" << msgData.data0;
        qDebug() << "RecvID HIGH:" << msgData.data1;
        msgs.append(new Msg(QDateTime(), 0xFFu, msgData));
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
        MsgDataT msgData = msg->getData();
        qDebug() << "data0: " << msgData.data0;
        qDebug() << "data1: " << msgData.data1;
        qDebug() << "data2: " << msgData.data2;
        qDebug() << "data3: " << msgData.data3;
        qDebug() << "data4: " << msgData.data4;
        qDebug() << "data5: " << msgData.data5;
        qDebug() << "data6: " << msgData.data6;

        csvFile.append(QString("%1;%2;%3;%4;%5;%6;%7;%8;%9;%10;%11;%12;%13;%14\n")
                       .arg((msgData.data0 << 8) + msgData.data1)     //1
                       .arg((msgData.data2 & 0x80) >> 7)              //2
                       .arg((msgData.data2 & 0x40) >> 6)              //3
                       .arg((msgData.data2 & 0x20) >> 5)              //4
                       .arg((msgData.data2 & 0x10) >> 4)              //5
                       .arg((msgData.data2 & 0x08) >> 3)              //6
                       .arg((msgData.data2 & 0x04) >> 2)              //7
                       .arg((msgData.data2 & 0x02) >> 1)              //8
                       .arg((msgData.data2 & 0x01))                   //9
                       .arg((msgData.data3 & 0x10) >> 4)              //10
                       .arg((msgData.data3 & 0x08) >> 3)              //11
                       .arg((msgData.data3 & 0x04) >> 2)              //12
                       .arg((msgData.data3 & 0x02) >> 1)              //13
                       .arg((msgData.data3 & 0x01))                   //14
                       );
    }
    return csvFile;
}


