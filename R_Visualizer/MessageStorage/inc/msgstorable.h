#ifndef MSGSTORABLE_H
#define MSGSTORABLE_H

#include <QJsonObject>

class IMsgStorable
{
private:
    

public:
    IMsgStorable(){}
    virtual ~IMsgStorable(){}

    virtual QJsonObject ParseToJson() const = 0;
    virtual void ParseFromJson(const QJsonObject &jsonObj) = 0;
};

#endif /* MSGSTORABLE_H */
