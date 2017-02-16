#include "jsoninparser.h"

#include "messagestream.h"
#include "msgstreammodel.h"
#include "msgstorage.h"
#include "sendmessages.h"
#include "sendmsgmodel.h"
#include "msg.h"
#include "messageconfig.h"
#include "idmodel.h"
#include "idrep.h"
#include "msgtypemodel.h"
#include "msgtyperep.h"
#include "messagefilter.h"
#include "filteridstore.h"
#include "filtercodestore.h"
#include "filtertimestampstore.h"
#include "systemoverview.h"
#include "sysovrvobject.h"
#include "sysovrvtextlabel.h"
#include "sysovrvtrigger.h"
#include "errlogview.h"
#include "errorlogentry.h"


#include <QDebug>

JsonInParser::JsonInParser()
{
}

JsonInParser::~JsonInParser()
{
}

void JsonInParser::setJsonDocument(const QJsonDocument &jsonDoc)
{
    if(jsonDoc.isObject())
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(jsonDoc.object()));
    }
    else if(jsonDoc.isArray())
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(jsonDoc.array()));
    }
}

void JsonInParser::visit(MessageStream &visitor)
{
}

void JsonInParser::visit(MsgStreamModel &visitor)
{
}

void JsonInParser::visit(MsgStorage &visitor)
{
    QJsonArray tempJsonArray = currentJsonValuePtr->toArray();
    const int tempJsonArraySize = tempJsonArray.size();
    for(int i = 0; i < tempJsonArraySize; ++i)
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray.at(i).toObject()));
        Msg newMsg;
        newMsg.accept(this);
        visitor.appendMsg(newMsg);
    }
}

void JsonInParser::visit(SendMessages &visitor)
{
}

void JsonInParser::visit(SendMsgModel &visitor)
{
    const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray();
    const int tempJsonArraySize = tempJsonArray.size();

    for(int i = 0; i < tempJsonArraySize; ++i)
    {
        const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject();
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject));
        Msg newMsg;
        newMsg.accept(this);
        visitor.appendMsg(PrettyMsg(newMsg));
    }
}

void JsonInParser::visit(Msg &visitor)
{
    const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject();
    visitor.setId(static_cast<MsgIDType>(tempJsonObject["MsgID"].toInt()));
    visitor.setCode(static_cast<MsgCodeType>(tempJsonObject["MsgCode"].toInt()));
    visitor.setTimestamp(
            QDateTime::fromString(
                tempJsonObject["MsgTimestamp"].toString(), 
                QString("dd.MM.yyyy - hh:mm:ss.zzz")
                )
            );
    const QJsonArray &tempJsonArray = tempJsonObject["MsgData"].toArray();
    const int tempJsonArraySize = tempJsonArray.size();
    DataByteVect tempDataByteVect;
    for(int i = 0; i < tempJsonArraySize; ++i)
    {
        tempDataByteVect.append(static_cast<quint8>(tempJsonArray.at(i).toInt()));
    }
    visitor.setData(tempDataByteVect);
}

void JsonInParser::visit(MessageConfig &visitor)
{
}

void JsonInParser::visit(IDModel &visitor)
{
    const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray();
    const int tempJsonArraySize = tempJsonArray.size();

    for(int i = 0; i < tempJsonArraySize; ++i)
    {
        const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject();
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject));
        IDRep newIDRep;
        newIDRep.accept(this);
        visitor.add(newIDRep);
    }
}

void JsonInParser::visit(IDRep &visitor)
{
    const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject();

    visitor.setId(static_cast<MsgIDType>(tempJsonObject["IDRepID"].toInt()));
    visitor.setName(tempJsonObject["IDRepName"].toString());
    visitor.setColor(QColor(tempJsonObject["IDRepColor"].toString()));
}

void JsonInParser::visit(MsgTypeModel &visitor)
{
    const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray();
    const int tempJsonArraySize = tempJsonArray.size();

    for(int i = 0; i < tempJsonArraySize; ++i)
    {
        const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject();
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject));
        MsgTypeRep newMsgTypeRep;
        newMsgTypeRep.accept(this);
        visitor.add(newMsgTypeRep);
    }
}

void JsonInParser::visit(MsgTypeRep &visitor)
{
    const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject();

    visitor.setCode(static_cast<MsgCodeType>(tempJsonObject["MsgTypeRepCode"].toInt()));
    visitor.setCodeName(tempJsonObject["MsgTypeRepName"].toString());
    visitor.setMessageFormat(tempJsonObject["MsgTypeRepMessageFormat"].toString());
    visitor.setColor(QColor(tempJsonObject["MsgTypeRepColor"].toString()));
}

void JsonInParser::visit(MessageFilter &visitor)
{
}

void JsonInParser::visit(FilterIDStore &visitor)
{
    const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray();

    const int tempJsonArraySize = tempJsonArray.size();
    for(int i = 0; i < tempJsonArraySize; ++i)
    {
        const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject();
        visitor.addID(static_cast<MsgIDType>(tempJsonObject["FilterID"].toInt()));
    }
}

void JsonInParser::visit(FilterCodeStore &visitor)
{
    const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray();

    const int tempJsonArraySize = tempJsonArray.size();
    for(int i = 0; i < tempJsonArraySize; ++i)
    {
        const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject();
        visitor.addCode(static_cast<MsgCodeType>(tempJsonObject["FilterCode"].toInt()));
    }
}

void JsonInParser::visit(FilterTimestampStore &visitor)
{
    const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject();
    visitor.setTimestampFilterFrom(
            QDateTime::fromString(
                tempJsonObject["FilterTimestampFrom"].toString(),
                QString("dd.MM.yyyy - hh:mm:ss.zzz")
                )
            );
    visitor.setTimestampFilterTo(
            QDateTime::fromString(
                tempJsonObject["FilterTimestampTo"].toString(),
                QString("dd.MM.yyyy - hh:mm:ss.zzz")
                )
            );
}

void JsonInParser::visit(SystemOverview &visitor)
{
}

void JsonInParser::visit(SysOvrvObject &visitor)
{
}

void JsonInParser::visit(SysOvrvTextLabel &visitor)
{
}

void JsonInParser::visit(SysOvrvTrigger &visitor)
{
}

void JsonInParser::visit(ErrorLogView &visitor)
{
}

void JsonInParser::visit(ErrLogModel &visitor)
{
}

void JsonInParser::visit(ErrorLogEntry &visitor)
{
}

