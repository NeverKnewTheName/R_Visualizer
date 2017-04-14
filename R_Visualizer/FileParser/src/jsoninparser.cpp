#include "jsoninparser.h"

#include "MsgStreamModel.h"
#include "msgstorage.h"
#include "sendmsgmodel.h"
#include "Msg.h"
#include "MsgIDRep.h"
#include "MsgCodeRep.h"
#include "MsgDataRep.h"
#include "filteridstore.h"
#include "filtercodestore.h"
#include "filtertimestampstore.h"
#include "sysovrvobject.h"
#include "sysovrvtextlabel.h"
#include "sysovrvtrigger.h"
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

/* void JsonInParser::visit(MessageStream &visitor) */
/* { */
/* } */

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

void JsonInParser::visit(TimestampedMsgStorage &visitor)
{
    QJsonArray tempJsonArray = currentJsonValuePtr->toArray();
    const int tempJsonArraySize = tempJsonArray.size();
    for(int i = 0; i < tempJsonArraySize; ++i)
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray.at(i).toObject()));
        TimestampedMsg newMsg;
        newMsg.accept(this);
        visitor.appendMsg(newMsg);
    }
}

/* void JsonInParser::visit(SendMessages &visitor) */
/* { */
/* } */

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
    visitor.setMsgID(MsgIDType(tempJsonObject["MsgID"].toInt()));
    visitor.setMsgCode(MsgCodeType(tempJsonObject["MsgCode"].toInt()));
    const QJsonArray &tempJsonArray = tempJsonObject["MsgData"].toArray();
    const int tempJsonArraySize = tempJsonArray.size();
    MsgDataType tempMsgData;
    for(int i = 0; i < tempJsonArraySize; ++i)
    {
        tempMsgData.append(MsgDataByteType(tempJsonArray.at(i).toInt()));
    }
    visitor.setMsgData(tempMsgData);
}

void JsonInParser::visit(TimestampedMsg &visitor)
{
    const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject();
    visitor.setTimestamp(
            QDateTime::fromString(
                tempJsonObject["MsgTimestamp"].toString(),
                QString("dd.MM.yyyy - hh:mm:ss.zzz")
                )
            );
    Msg originalMsg;
    originalMsg.accept(this);
    visitor.setOriginalMsg(originalMsg);
}

/* void JsonInParser::visit(MessageConfig &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(IDModel &visitor) */
/* { */
/*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */

/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); */
/*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/*         IDRep newIDRep; */
/*         newIDRep.accept(this); */
/*         visitor.add(newIDRep); */
/*     } */
/* } */

void JsonInParser::visit(MsgIDRep &visitor)
{
    const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject();

    visitor.setID(MsgIDType(tempJsonObject["IDRepID"].toInt()));
    visitor.setPlainTextAlias(tempJsonObject["IDRepName"].toString());
    visitor.setColorRepresentation(QColor(tempJsonObject["IDRepColor"].toString()));
}

/* void JsonInParser::visit(MsgTypeModel &visitor) */
/* { */
/*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */

/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); */
/*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/*         MsgTypeRep newMsgTypeRep; */
/*         newMsgTypeRep.accept(this); */
/*         visitor.add(newMsgTypeRep); */
/*     } */
/* } */

void JsonInParser::visit(MsgCodeRep &visitor)
{
    const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject();

    visitor.setCode(MsgCodeType(tempJsonObject["MsgTypeRepCode"].toInt()));
    visitor.setPlainTextAlias(tempJsonObject["MsgTypeRepName"].toString());
    /* visitor.setMessageFormat(tempJsonObject["MsgTypeRepMessageFormat"].toString()); */
    visitor.setColorRepresentation(QColor(tempJsonObject["MsgTypeRepColor"].toString()));
}

void JsonInParser::visit(MsgDataRep &visitor)
{
}

/* void JsonInParser::visit(MessageFilter &visitor) */
/* { */
/* } */

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

/* void JsonInParser::visit(SystemOverview &visitor) */
/* { */
/* } */

void JsonInParser::visit(SysOvrvObject &visitor)
{
    const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject();
    //SysOvrvObject::ObjShapeType shape = static_cast<SysOvrvObject::ObjShapeType>(
    //        tempJsonObject["ObjShape"]
    //        );
    /* SysOvrvObject *newSysOvrvObject */
    //DANG IT! Inheritance model does not work here...
}

void JsonInParser::visit(SysOvrvTextLabel &visitor)
{
}

void JsonInParser::visit(SysOvrvTrigger &visitor)
{
}

/* void JsonInParser::visit(ErrorLogView &visitor) */
/* { */
/* } */

void JsonInParser::visit(ErrLogModel &visitor)
{
}

void JsonInParser::visit(ErrorLogEntry &visitor)
{
}

