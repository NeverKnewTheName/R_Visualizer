#include "msg.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>

IncomingMsg::IncomingMsg( const QDateTime &timestamp, const MsgIDType &id, const MsgCodeType &code, const DataByteVect &dataBytes ) :
    Msg(id, code, dataBytes),
    MsgTimestamp(timestamp)
{
}

IncomingMsg::~IncomingMsg()
{
}

const QDateTime &IncomingMsg::GetMsgTimeStamp() const
{
    return this->MsgTimestamp;
}

QJsonObject IncomingMsg::ParseToJson() const
{
    QJsonObject msgJsonObj = Msg::ParseToJson();
    msgJsonObj["MsgTimestamp"] = MsgTimestamp.toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));

    return msgJsonObj;
}

void IncomingMsg::ParseFromJson( const QJsonObject &jsonObj )
{
    Msg::ParseToJson(jsonObj);
    MsgTimestamp = QDateTime::fromString(jsonMsg["MsgTimestamp"].toString(),QString("dd.MM.yyyy - hh:mm:ss.zzz"));
}

