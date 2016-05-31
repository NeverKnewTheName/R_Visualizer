#ifndef CSVMSGPACKETHANDLER_H
#define CSVMSGPACKETHANDLER_H

#include "msg.h"
#include <QVector>

class CsvMsgPacketHandler
{
public:
    CsvMsgPacketHandler();
    CsvMsgPacketHandler(QString &csvMsgPacketString);
    ~CsvMsgPacketHandler();

    QVector<Msg *> parseCsvMsgPacket(QString &csvMsgPacketString);

    QString parseToString(QVector<Msg *> msgs);

private:
};

#endif // CSVMSGPACKETHANDLER_H
