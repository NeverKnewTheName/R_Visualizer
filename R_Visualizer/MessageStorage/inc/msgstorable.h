#ifndef MSGSTORABLE_H
#define MSGSTORABLE_H

#include <QJsonObject>

class IMsgStorable
{
private:
    

public:
    IMsgStorable();
    virtual ~IMsgStorable();

    virtual QJsonObject ParseToJson() const;
    virtual void ParseFromJson(const QJsonObject &jsonObj);
};

#endif /* MSGSTORABLE_H */
