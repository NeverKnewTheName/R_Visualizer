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

    HugeQVector parseCsvMsgPacket(QString &csvMsgPacketString);

    QString parseToString(HugeQVector msgs);

private:
};

#endif // CSVMSGPACKETHANDLER_H
