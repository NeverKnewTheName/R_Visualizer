#include "jsoninparser.h"

#include "Msg.h"
#include "TimestampedMsg.h"
#include "MsgStreamStore.h"
#include "msgstorage.h"
#include "SendMsgPackageStore.h"
#include "MsgIDMappingStore.h"
#include "MsgIDRep.h"
#include "MsgCodeMappingStore.h"
#include "MsgCodeRep.h"
#include "MsgDataMappingStore.h"
#include "MsgDataRep.h"
#include "MsgIDFilterStore.h"
#include "MsgCodeFilterStore.h"
#include "MsgTimestampFilter.h"

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

void JsonInParser::visit(Msg &visitor)
{
}

void JsonInParser::visit(TimestampedMsg &visitor)
{
}

void JsonInParser::visit(MsgStreamStore &visitor)
{
}

void JsonInParser::visit(MsgStorage &visitor)
{
}

void JsonInParser::visit(TimestampedMsgStorage &visitor)
{
}

void JsonInParser::visit(SendMsgPackageStore &visitor)
{
}

void JsonInParser::visit(MsgIDMappingStore &visitor)
{
}

void JsonInParser::visit(MsgIDRep &visitor)
{
}

void JsonInParser::visit(MsgCodeMappingStore &visitor)
{
}

void JsonInParser::visit(MsgCodeRep &visitor)
{
}

void JsonInParser::visit(MsgDataMappingStore &visitor)
{
}

void JsonInParser::visit(MsgDataRep &visitor)
{
}

void JsonInParser::visit(MsgIDFilterStore &visitor)
{
}

void JsonInParser::visit(MsgCodeFilterStore &visitor)
{
}

void JsonInParser::visit(MsgTimestampFilter &visitor)
{
}

/* void JsonInParser::visit(SysOvrvObject &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(SysOvrvTextLabel &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(SysOvrvTrigger &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(ErrLogModel &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(ErrorLogEntry &visitor) */
/* { */
/* } */







/////////////////////////////////////////////////////END//////////////////////
/* void JsonInParser::visit(MsgStreamModel &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(MsgStorage &visitor) */
/* { */
/*     QJsonArray tempJsonArray = currentJsonValuePtr->toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray.at(i).toObject())); */
/*         Msg newMsg; */
/*         newMsg.accept(this); */
/*         visitor.appendMsg(newMsg); */
/*     } */
/* } */

/* void JsonInParser::visit(TimestampedMsgStorage &visitor) */
/* { */
/*     QJsonArray tempJsonArray = currentJsonValuePtr->toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray.at(i).toObject())); */
/*         TimestampedMsg newMsg; */
/*         newMsg.accept(this); */
/*         visitor.appendMsg(newMsg); */
/*     } */
/* } */

/* /1* void JsonInParser::visit(SendMessages &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(SendMsgPackageStore &visitor) */
/* { */
/*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */

/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); */
/*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/*         Msg newMsg; */
/*         newMsg.accept(this); */
/*         visitor.appendMsg(PrettyMsg<Msg>(newMsg)); */
/*     } */
/* } */

/* void JsonInParser::visit(Msg &visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */
/*     visitor.setMsgID(MsgIDType(tempJsonObject["MsgID"].toInt())); */
/*     visitor.setMsgCode(MsgCodeType(tempJsonObject["MsgCode"].toInt())); */
/*     const QJsonArray &tempJsonArray = tempJsonObject["MsgData"].toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     MsgDataType tempMsgData; */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         tempMsgData.append(MsgDataByteType(tempJsonArray.at(i).toInt())); */
/*     } */
/*     visitor.setMsgData(tempMsgData); */
/* } */

/* void JsonInParser::visit(TimestampedMsg &visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */
/*     visitor.setTimestamp( */
/*             QDateTime::fromString( */
/*                 tempJsonObject["MsgTimestamp"].toString(), */
/*                 QString("dd.MM.yyyy - hh:mm:ss.zzz") */
/*                 ) */
/*             ); */
/*     Msg originalMsg; */
/*     originalMsg.accept(this); */
/*     visitor.setOriginalMsg(originalMsg); */
/* } */

/* /1* void JsonInParser::visit(MessageConfig &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* /1* void JsonInParser::visit(IDModel &visitor) *1/ */
/* /1* { *1/ */
/* /1*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); *1/ */
/* /1*     const int tempJsonArraySize = tempJsonArray.size(); *1/ */

/* /1*     for(int i = 0; i < tempJsonArraySize; ++i) *1/ */
/* /1*     { *1/ */
/* /1*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); *1/ */
/* /1*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); *1/ */
/* /1*         IDRep newIDRep; *1/ */
/* /1*         newIDRep.accept(this); *1/ */
/* /1*         visitor.add(newIDRep); *1/ */
/* /1*     } *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(MsgIDRep &visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */

/*     visitor.setID(MsgIDType(tempJsonObject["IDRepID"].toInt())); */
/*     visitor.setPlainTextAlias(tempJsonObject["IDRepName"].toString()); */
/*     visitor.setColorRepresentation(QColor(tempJsonObject["IDRepColor"].toString())); */
/* } */

/* /1* void JsonInParser::visit(MsgTypeModel &visitor) *1/ */
/* /1* { *1/ */
/* /1*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); *1/ */
/* /1*     const int tempJsonArraySize = tempJsonArray.size(); *1/ */

/* /1*     for(int i = 0; i < tempJsonArraySize; ++i) *1/ */
/* /1*     { *1/ */
/* /1*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); *1/ */
/* /1*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); *1/ */
/* /1*         MsgTypeRep newMsgTypeRep; *1/ */
/* /1*         newMsgTypeRep.accept(this); *1/ */
/* /1*         visitor.add(newMsgTypeRep); *1/ */
/* /1*     } *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(MsgCodeRep &visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */

/*     visitor.setCode(MsgCodeType(tempJsonObject["MsgTypeRepCode"].toInt())); */
/*     visitor.setPlainTextAlias(tempJsonObject["MsgTypeRepName"].toString()); */
/*     /1* visitor.setMessageFormat(tempJsonObject["MsgTypeRepMessageFormat"].toString()); *1/ */
/*     visitor.setColorRepresentation(QColor(tempJsonObject["MsgTypeRepColor"].toString())); */
/* } */

/* void JsonInParser::visit(MsgDataRep &visitor) */
/* { */
/* } */

/* /1* void JsonInParser::visit(MessageFilter &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(FilterIDStore &visitor) */
/* { */
/*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); */

/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); */
/*         visitor.addID(static_cast<MsgIDType>(tempJsonObject["FilterID"].toInt())); */
/*     } */
/* } */

/* void JsonInParser::visit(FilterCodeStore &visitor) */
/* { */
/*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); */

/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); */
/*         visitor.addCode(static_cast<MsgCodeType>(tempJsonObject["FilterCode"].toInt())); */
/*     } */
/* } */

/* void JsonInParser::visit(FilterTimestampStore &visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */
/*     visitor.setTimestampFilterFrom( */
/*             QDateTime::fromString( */
/*                 tempJsonObject["FilterTimestampFrom"].toString(), */
/*                 QString("dd.MM.yyyy - hh:mm:ss.zzz") */
/*                 ) */
/*             ); */
/*     visitor.setTimestampFilterTo( */
/*             QDateTime::fromString( */
/*                 tempJsonObject["FilterTimestampTo"].toString(), */
/*                 QString("dd.MM.yyyy - hh:mm:ss.zzz") */
/*                 ) */
/*             ); */
/* } */

/* /1* void JsonInParser::visit(SystemOverview &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(SysOvrvObject &visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */
/*     //SysOvrvObject::ObjShapeType shape = static_cast<SysOvrvObject::ObjShapeType>( */
/*     //        tempJsonObject["ObjShape"] */
/*     //        ); */
/*     /1* SysOvrvObject *newSysOvrvObject *1/ */
/*     //DANG IT! Inheritance model does not work here... */
/* } */

/* void JsonInParser::visit(SysOvrvTextLabel &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(SysOvrvTrigger &visitor) */
/* { */
/* } */

/* /1* void JsonInParser::visit(ErrorLogView &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(ErrLogModel &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(ErrorLogEntry &visitor) */
/* { */
/* } */

