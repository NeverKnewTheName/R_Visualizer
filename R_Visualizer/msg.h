#ifndef MSG_H
#define MSG_H

#include <QJsonObject>
#include <QDateTime>

#include <QMetaType>

typedef struct msgDataT
{
    quint8 code;
    quint8 data0;
    quint8 data1;
    quint8 data2;
    quint8 data3;
    quint8 data4;
    quint8 data5;
    quint8 data6;
}MsgDataT;

Q_DECLARE_METATYPE(MsgDataT)

class Msg
{
public:
    Msg();
    Msg(QDateTime timestamp, unsigned int id, MsgDataT &data);
    Msg(QDateTime timestamp, unsigned int id, QByteArray &data);
    Msg(QDateTime timestamp, unsigned int id, quint8 code, quint8 data0 = 0,quint8 data1 = 0,quint8 data2 = 0,quint8 data3 = 0,quint8 data4 = 0,quint8 data5 = 0,quint8 data6 = 0);

    QDateTime getTimestamp() const;
    void setTimestamp(QDateTime value);

    unsigned int getId() const;
    void setId(unsigned int value);

    MsgDataT getData() const;
    void setData(const MsgDataT &value);
    void setData(quint8 code, quint8 data0 = 0, quint8 data1 = 0, quint8 data2 = 0, quint8 data3 = 0, quint8 data4 = 0, quint8 data5 = 0, quint8 data6 = 0);

    quint8 getCode() const;
    void setCode(quint8 value);

    //unsigned int getMessage() const;
    void setMessage(quint8 data0 = 0, quint8 data1 = 0, quint8 data2 = 0, quint8 data3 = 0, quint8 data4 = 0, quint8 data5 = 0, quint8 data6 = 0);

    QString getMessageAsString() const;
    QString getDataAsString() const;

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT() const;


private:
    QDateTime timestamp;
    unsigned int id;
    MsgDataT data;
};

#endif // MSG_H
