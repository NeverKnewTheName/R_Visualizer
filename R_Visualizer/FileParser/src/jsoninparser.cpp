#include "jsoninparser.h"

#include "Msg.h"
#include "TimestampedMsg.h"
/* #include "MsgStreamStore.h" */
/* #include "msgstorage.h" */
/* #include "SendMsgPackageStore.h" */
#include "MsgIDMappingStore.h"
#include "MsgIDMapping.h"
#include "MsgCodeMappingStore.h"
#include "MsgCodeMapping.h"
#include "MsgDataMappingStore.h"
#include "MsgDataMapping.h"
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

/* void JsonInParser::visit(MsgStreamStore &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(MsgStorage &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(TimestampedMsgStorage &visitor) */
/* { */
/* } */

/* void JsonInParser::visit(SendMsgPackageStore &visitor) */
/* { */
/* } */

void JsonInParser::visit(MsgIDMappingStore &visitor)
{
}

void JsonInParser::visit(MsgIDMapping &visitor)
{
}

void JsonInParser::visit(MsgCodeMappingStore &visitor)
{
}

void JsonInParser::visit(MsgCodeMapping &visitor)
{
}

void JsonInParser::visit(MsgDataMappingStore &visitor)
{
}

void JsonInParser::visit(MsgDataMapping &visitor)
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
/* /1*         IDMapping newIDMapping; *1/ */
/* /1*         newIDMapping.accept(this); *1/ */
/* /1*         visitor.add(newIDMapping); *1/ */
/* /1*     } *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(MsgIDMapping &visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */

/*     visitor.setID(MsgIDType(tempJsonObject["IDMappingID"].toInt())); */
/*     visitor.setPlainTextAlias(tempJsonObject["IDMappingName"].toString()); */
/*     visitor.setColorMappingresentation(QColor(tempJsonObject["IDMappingColor"].toString())); */
/* } */

/* /1* void JsonInParser::visit(MsgTypeModel &visitor) *1/ */
/* /1* { *1/ */
/* /1*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); *1/ */
/* /1*     const int tempJsonArraySize = tempJsonArray.size(); *1/ */

/* /1*     for(int i = 0; i < tempJsonArraySize; ++i) *1/ */
/* /1*     { *1/ */
/* /1*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); *1/ */
/* /1*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); *1/ */
/* /1*         MsgTypeMapping newMsgTypeMapping; *1/ */
/* /1*         newMsgTypeMapping.accept(this); *1/ */
/* /1*         visitor.add(newMsgTypeMapping); *1/ */
/* /1*     } *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(MsgCodeMapping &visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */

/*     visitor.setCode(MsgCodeType(tempJsonObject["MsgTypeMappingCode"].toInt())); */
/*     visitor.setPlainTextAlias(tempJsonObject["MsgTypeMappingName"].toString()); */
/*     /1* visitor.setMessageFormat(tempJsonObject["MsgTypeMappingMessageFormat"].toString()); *1/ */
/*     visitor.setColorMappingresentation(QColor(tempJsonObject["MsgTypeMappingColor"].toString())); */
/* } */

/* void JsonInParser::visit(MsgDataMapping &visitor) */
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

