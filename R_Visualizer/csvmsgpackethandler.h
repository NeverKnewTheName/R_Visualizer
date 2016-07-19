#ifndef CSVMSGPACKETHANDLER_H
#define CSVMSGPACKETHANDLER_H

#include "hugeqvector.h"
#include "msg.h"
#include <QVector>

class CsvMsgPacketHandler
{
public:
    CsvMsgPacketHandler();
    CsvMsgPacketHandler(QString &csvMsgPacketString);
    ~CsvMsgPacketHandler();

    HugeQVector<Msg> parseCsvMsgPacket(QString &csvMsgPacketString);

    QString parseToString(HugeQVector<Msg> msgs);

private:
};

#endif // CSVMSGPACKETHANDLER_H
