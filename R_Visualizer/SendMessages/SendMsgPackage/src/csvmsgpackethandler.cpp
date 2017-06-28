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
    QStringList codeStringList = codeLine.split(";");
    QString code = codeStringList.at(0);

    MsgDataType dataBytes;
    dataBytes.append(MsgDataByteType(codeStringList.size()-1));
    dataBytes.append(MsgDataByteType(msgsFromPacket.size()));
    msgs.append(
            Msg(
                MsgIDType(0xFFu),
                MsgCodeType(code.toInt(0,16)),
                dataBytes
                )
            );

    int rowCntr = 0;

    for(auto &msg : msgsFromPacket )
    {
        // first line is code;
        // other lines contain: ID(2) - DATA(2)
        if(msg.isEmpty())
        {
            continue;
        }

        rowCntr++;
        QStringList msgAsString = msg.split(";");
        QString recvrIDString = msgAsString.at(0);
        unsigned int recvrID = recvrIDString.toInt();

        const int nrOfColumns = msgAsString.size() - 1; // -1 for the address

        quint16 cell = 0;
        for(int i = 1; i <= 16; ++i)
        {
            if(i < nrOfColumns)
            {
                cell |= msgAsString.at(i).toInt(0,10) << (16-i);
            }
        }

        dataBytes.clear();
        dataBytes.append(MsgDataByteType(((recvrID >> 8) & 0xFFu )));
        dataBytes.append(MsgDataByteType((recvrID & 0xFFu)));
        dataBytes.append(MsgDataByteType((cell >> 8) & 0xFFu));
        dataBytes.append(MsgDataByteType(cell & 0xFFu));

        msgs.append(
                Msg(
                    MsgIDType(0xFFu),
                    MsgCodeType(0x0B),
                    dataBytes
                    )
                );
    }

    MsgDataType msgDataFirstRow = msgs.at(0).getMsgData();
    msgDataFirstRow.replace(1,MsgDataByteType(rowCntr));
    msgs[0].setMsgData(msgDataFirstRow);

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


