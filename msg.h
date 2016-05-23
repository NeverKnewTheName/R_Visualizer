#ifndef MSG_H
#define MSG_H

#include <QJsonObject>

class Msg
{
public:
    Msg();
    Msg(int timestamp, int id, int message);

    int getTimestamp() const;
    void setTimestamp(int value);

    int getId() const;
    void setId(int value);

    int getCode() const;
    void setCode(int value);

    int getMessage() const;
    void setMessage(int value);

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT();


private:
    int timestamp;
    int id;
    int code;
    int message;
};

#endif // MSG_H
