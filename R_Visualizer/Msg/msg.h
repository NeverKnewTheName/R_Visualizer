#ifndef MSG_H
#define MSG_H

class QJsonObject;
#include <QDateTime>

#include <QMetaType>
#include <QVector>

#include <QSize>

typedef QVector<quint8> DataByteVect, *PDataByteVect;
Q_DECLARE_METATYPE(DataByteVect)

typedef struct _MsgData
{
    DataByteVect DataBytes;
    unsigned int DataSizeInBytes;
}MsgDataStruc, *PMsgDataStruc;

Q_DECLARE_METATYPE(MsgDataStruc)

typedef quint16 MsgIDType;

typedef quint16 MsgCodeType;

class Msg
{
public:
    Msg();
    Msg(const Msg &other);
    Msg(const QDateTime &timestamp, const MsgIDType id, const MsgCodeType code, DataByteVect dataBytes);
    ~Msg();

    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime &value);

    MsgIDType getId() const;
    void setId(const MsgIDType value);

    MsgCodeType getCode() const;
    void setCode(const MsgCodeType value);

    PMsgDataStruc getData();
    QByteArray getDataAsByteArray() const;
    void setData(const DataByteVect dataBytes);
    void setDataByte(const quint8 index, const quint8 dataByte);

    QString getMessageAsString() const;
    QString getDataAsString() const;

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT() const;

    MsgDataStruc getMsgData() const;

    QSize getMsgSizeHint() const;

    void setMsgSizeHint(const QSize &value);

private:
    QDateTime MsgTimestamp;
    MsgIDType MsgID;
    MsgCodeType MsgCode;
    MsgDataStruc MsgData;
    QSize msgSizeHint;
};

Q_DECLARE_METATYPE(Msg)

#endif // MSG_H
