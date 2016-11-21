#ifndef MSG_H
#define MSG_H

class QJsonObject;
#include <QDateTime>

#include <QMetaType>
#include <QVector>

typedef QVector<quint8> DataByteVect, *PDataByteVect;
Q_DECLARE_METATYPE(DataByteVect)

typedef struct _MsgData
{
    DataByteVect DataBytes;
    unsigned int DataSizeInBytes;
}MsgDataStruc, *PMsgDataStruc;

Q_DECLARE_METATYPE(MsgDataStruc)

class Msg
{
public:
    Msg();
    Msg(const Msg &other);
    Msg(QDateTime timestamp, quint16 id, quint16 code, DataByteVect dataBytes);
    ~Msg();

    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime value);

    quint16 getId() const;
    void setId(const quint16 value);

    quint16 getCode() const;
    void setCode(const quint16 value);

    PMsgDataStruc getData();
    QByteArray getDataAsByteArray() const;
    void setData(const DataByteVect dataBytes);
    void setDataByte(quint8 index, quint8 dataByte);

    QString getMessageAsString() const;
    QString getDataAsString() const;

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT() const;

    MsgDataStruc getMsgData() const;

private:
    QDateTime MsgTimestamp;
    quint16 MsgID;
    quint16 MsgCode;
    MsgDataStruc MsgData;
};

Q_DECLARE_METATYPE(Msg)

#endif // MSG_H
