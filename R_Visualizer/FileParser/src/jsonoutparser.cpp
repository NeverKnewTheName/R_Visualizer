#include "jsonoutparser.h"

#include "Msg.h"
#include "TimestampedMsg.h"
#include "MsgStreamStore.h"
#include "msgstorage.h"
/* #include "SendMsgPackageStore.h" */
#include "MsgIDMappingStore.h"
#include "MsgIDMapping.h"
#include "MsgCodeMappingStore.h"
#include "MsgCodeMapping.h"
#include "MsgDataMappingStore.h"
#include "MsgDataMapping.h"
#include "MsgIDFilterStore.h"
#include "MsgCodeFilterStore.h"
#include "MsgTimespanFilter.h"

#include <QDebug>

JsonOutParser::JsonOutParser()
{
}

JsonOutParser::~JsonOutParser()
{

}

QJsonDocument JsonOutParser::getJsonDocument() const
{
    switch(currentJsonValuePtr->type())
    {
        case QJsonValue::Null:
            return QJsonDocument();
            break;
        case QJsonValue::Bool:
            return QJsonDocument({"BooleanValue", currentJsonValuePtr->toBool()});
            break;
        case QJsonValue::Double:
            return QJsonDocument({"DoubleValue", currentJsonValuePtr->toDouble()});
            break;
        case QJsonValue::String:
            return QJsonDocument({"StringValue", currentJsonValuePtr->toString()});
            break;
        case QJsonValue::Array:
            return QJsonDocument(currentJsonValuePtr->toArray());
            break;
        case QJsonValue::Object:
            return QJsonDocument(currentJsonValuePtr->toObject());
            break;
        case QJsonValue::Undefined:
            qDebug() << "UNDEFINED VALUE IN currentJsonValuePtr";
            break;
    }
    return QJsonDocument();
}

void JsonOutParser::visit(Msg &visitor)
{
}

void JsonOutParser::visit(TimestampedMsg &visitor)
{
}

void JsonOutParser::visit(MsgStreamStore &visitor)
{
}

void JsonOutParser::visit(MsgStorage &visitor)
{
}

void JsonOutParser::visit(TimestampedMsgStorage &visitor)
{
}

/* void JsonOutParser::visit(SendMsgPackageStore &visitor) */
/* { */
/* } */

void JsonOutParser::visit(MsgIDMappingStore &visitor)
{
}

void JsonOutParser::visit(MsgIDMapping &visitor)
{
}

void JsonOutParser::visit(MsgCodeMappingStore &visitor)
{
}

void JsonOutParser::visit(MsgCodeMapping &visitor)
{
}

void JsonOutParser::visit(MsgDataMappingStore &visitor)
{
}

void JsonOutParser::visit(MsgDataMapping &visitor)
{
}

void JsonOutParser::visit(MsgIDFilterStore &visitor)
{
}

void JsonOutParser::visit(MsgCodeFilterStore &visitor)
{
}

void JsonOutParser::visit(MsgTimespanFilter &visitor)
{
}



/* void JsonOutParser::visit(SysOvrvObject &visitor) */
/* { */
/* } */

/* void JsonOutParser::visit(SysOvrvTextLabel &visitor) */
/* { */
/* } */

/* void JsonOutParser::visit(SysOvrvTrigger &visitor) */
/* { */
/* } */

/* void JsonOutParser::visit(ErrLogModel &visitor) */
/* { */
/* } */

/* void JsonOutParser::visit(ErrorLogEntry &visitor) */
/* { */
/* } */




//////////////////////////////////////////////END/////////////////////////////
/* void JsonOutParser::visit(MsgStreamModel &visitor) */
/* { */
/* } */

/* void JsonOutParser::visit(MsgStorage &visitor) */
/* { */
/*     QJsonArray tempJsonArray; */
/*     /1* tempJsonObject["MsgStorageSaveLocation"] = QJsonValue(visitor.saveMsgStorage(QString(""))); *1/ */
/*     /1* currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); *1/ */
/*     const int msgStorageSize = visitor.size(); */
/*     for(int i = 0; i < msgStorageSize; ++i) */
/*     { */
/*         Msg msg = visitor.at(i); */
/*         msg.accept(this); */
/*         tempJsonArray.append(*currentJsonValuePtr); */
/*     } */
/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); */
/* } */

/* void JsonOutParser::visit(TimestampedMsgStorage &visitor) */
/* { */
/*     QJsonArray tempJsonArray; */
/*     /1* tempJsonObject["MsgStorageSaveLocation"] = QJsonValue(visitor.saveMsgStorage(QString(""))); *1/ */
/*     /1* currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); *1/ */
/*     const int msgStorageSize = visitor.size(); */
/*     for(int i = 0; i < msgStorageSize; ++i) */
/*     { */
/*         TimestampedMsg msg = visitor.at(i); */
/*         msg.accept(this); */
/*         tempJsonArray.append(*currentJsonValuePtr); */
/*     } */
/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); */
/* } */

/* /1* void JsonOutParser::visit(SendMessages &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonOutParser::visit(SendMsgPackageStore &visitor) */
/* { */
/*     QVector<PrettyMsg> prettyMsgs = visitor.getMsgPacket(); */
/*     QJsonArray tempJsonArray; */
/*     for(PrettyMsg &prettyMsg : prettyMsgs) */
/*     { */
/*         dynamic_cast<Msg&>(prettyMsg).accept(this); */
/*         tempJsonArray.append(*currentJsonValuePtr); */
/*     } */
/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); */
/* } */

/* void JsonOutParser::visit(Msg &visitor) */
/* { */
/*     QJsonObject tempJsonObject; */
/*     QJsonArray tempJsonDataArray; */

/*     tempJsonObject["MsgID"] = QJsonValue(static_cast<MsgIDType::type>(visitor.getMsgID())); */
/*     tempJsonObject["MsgCode"] = QJsonValue(static_cast<MsgCodeType::type>(visitor.getMsgCode())); */

/*     const MsgDataType &tempMsgData = visitor.getMsgData(); */
/*     const int tempMsgDataSize = tempMsgData.size(); */
/*     for(unsigned int i = 0; i < tempMsgDataSize; ++i) */
/*     { */
/*         tempJsonDataArray.append(QJsonValue(static_cast<MsgDataByteType::type>(tempMsgData.at(i)))); */
/*     } */
/*     tempJsonObject["MsgData"] = tempJsonDataArray; */

/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/* } */

/* void JsonOutParser::visit(TimestampedMsg &visitor) */
/* { */
/*     Msg originalMsg = visitor.getOriginalMsg(); */
/*     originalMsg.accept(this); */

/*     QJsonObject tempJsonObject = currentJsonValuePtr->toObject(); */
/*     tempJsonObject["MsgTimestamp"] = visitor.getTimestamp().toString( */
/*             QString("dd.MM.yyyy - hh:mm:ss.zzz") */
/*             ); */
/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>( */
/*             new QJsonValue(tempJsonObject) */
/*             ); */
/* } */

/* /1* void JsonOutParser::visit(MessageConfig &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* /1* void JsonOutParser::visit(IDModel &visitor) *1/ */
/* /1* { *1/ */
/* /1*     QJsonArray tempJsonArray; *1/ */
/* /1*     const int idModelSize = visitor.size(); *1/ */
/* /1*     for(int i = 0; i < idModelSize; ++i) *1/ */
/* /1*     { *1/ */
/* /1*         IDMapping idMapping = visitor.at(i); *1/ */
/* /1*         idMapping.accept(this); *1/ */
/* /1*         tempJsonArray.append(*currentJsonValuePtr); *1/ */
/* /1*     } *1/ */
/* /1*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); *1/ */
/* /1* } *1/ */

/* void JsonOutParser::visit(MsgIDMapping &visitor) */
/* { */
/*     QJsonObject tempJsonObject; */
/*     tempJsonObject["MsgIDMappingID"] = static_cast<int>( */
/*             static_cast<MsgIDType::type>( */
/*                 visitor.getID() */
/*                 ) */
/*             ); */
/*     tempJsonObject["MsgIDMappingName"] = visitor.getPlainTextAlias(); */
/*     tempJsonObject["MsgIDMappingColor"] = visitor.getColorMappingresentation().name(); */

/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/* } */

/* /1* void JsonOutParser::visit(MsgTypeModel &visitor) *1/ */
/* /1* { *1/ */
/* /1*     QJsonArray tempJsonArray; *1/ */
/* /1*     const int msgTypeModelSize = visitor.size(); *1/ */
/* /1*     for(int i = 0; i < msgTypeModelSize; ++i) *1/ */
/* /1*     { *1/ */
/* /1*         MsgTypeMapping msgTypeMapping = visitor.at(i); *1/ */
/* /1*         msgTypeMapping.accept(this); *1/ */
/* /1*         tempJsonArray.append(*currentJsonValuePtr); *1/ */
/* /1*     } *1/ */
/* /1*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); *1/ */
/* /1* } *1/ */

/* void JsonOutParser::visit(MsgCodeMapping &visitor) */
/* { */
/*     QJsonObject tempJsonObject; */
/*     tempJsonObject["MsgCodeMappingCode"] = static_cast<int>( */
/*             static_cast<MsgCodeType::type>( */
/*                 visitor.getCode() */
/*                 ) */
/*             ); */
/*     tempJsonObject["MsgCodeMappingName"] = visitor.getPlainTextAlias(); */
/*     /1* tempJsonObject["MsgCodeMappingMessageFormat"] = visitor.getMessageFormat(); *1/ */
/*     tempJsonObject["MsgCodeMappingColor"] = visitor.getColorMappingresentation().name(); */

/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/* } */

/* void JsonOutParser::visit(MsgDataMapping &visitor) */
/* { */
/* } */

/* /1* void JsonOutParser::visit(MessageFilter &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonOutParser::visit(FilterIDStore &visitor) */
/* { */
/*     QJsonArray tempJsonArray; */

/*     const int filterIDStoreSize = visitor.size(); */
/*     for(int i = 0; i < filterIDStoreSize; ++i) */
/*     { */
/*         QJsonObject tempJsonObject; */
/*         tempJsonObject["FilterID"] = QJsonValue(static_cast<MsgIDType::type>(visitor.at(i))); */
/*         tempJsonArray.append(tempJsonObject); */
/*     } */
/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); */
/* } */

/* void JsonOutParser::visit(FilterCodeStore &visitor) */
/* { */
/*     QJsonArray tempJsonArray; */

/*     const int filterCodeStoreSize = visitor.size(); */
/*     for(int i = 0; i < filterCodeStoreSize; ++i) */
/*     { */
/*         QJsonObject tempJsonObject; */
/*         tempJsonObject["FilterCode"] = QJsonValue(static_cast<MsgCodeType::type>(visitor.at(i))); */
/*         tempJsonArray.append(tempJsonObject); */
/*     } */
/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); */
/* } */

/* void JsonOutParser::visit(FilterTimestampStore &visitor) */
/* { */
/*     QJsonObject tempJsonObject; */
/*     tempJsonObject["FilterTimestampFrom"] = QJsonValue(visitor.getTimestampFilterFrom().toString("dd.MM.yyyy - hh:mm:ss.zzz")); */
/*     tempJsonObject["FilterTimestampTo"] = QJsonValue(visitor.getTimestampFilterTo().toString("dd.MM.yyyy - hh:mm:ss.zzz")); */

/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/* } */

/* /1* void JsonOutParser::visit(SystemOverview &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonOutParser::visit(SysOvrvObject &visitor) */
/* { */
/*     //QJsonObject tempJsonObject; */
/*     //tempJsonObject["ObjName"] = visitor.getObjName(); */
/*     //tempJsonObject["ObjShape"] = static_cast<int>(visitor.getShape()); */
/* // */
/*     //const QColor &objColor = visitor.getObjColor(); */
/*     //tempJsonObject["ObjColor"] = objColor.name(QColor::HexArgb); */
/* // */
/*     //QJsonObject objSizeJsonObj; */
/*     //const QRectF &objBoundingRect = visitor.boundingRect(); */
/*     //objSizeJsonObj["ObjWidth"] = static_cast<double>(objBoundingRect.width()); */
/*     //objSizeJsonObj["ObjHeight"] = static_cast<double>(objBoundingRect.height()); */
/*     //tempJsonObject["ObjSize"] = objSizeJsonObj; */
/* // */
/*     //OJsonObject objPosJsonObj; */
/*     //objSizeJsonObj["XPos"] = static_cast<double>(visitor.x()); */
/*     //objSizeJsonObj["YPos"] = static_cast<double>(visitor.y()); */
/*     //tempJsonObject["ObjPos"] = objPosJsonObj; */
/* // */
/*     //QJsonArray objChildObjectsJsonArray; */
/*     //OJsonArray objLabelsJsonArray; */
/* // */
/*     //QList<QGraphicsItem *> children = visitor.childItems(); */
/* // */
/*     //for(QGraphicsItem *child : children) */
/*     //{ */
/*         //SysOvrvObject *sysOvrvObjChild = dynamic_cast<SysOvrvObject *>(child); */
/*         //if(sysOvrvObjChild != Q_NULLPTR) */
/*         //{ */
/*             //sysOvrvObjChild->accept(this); */
/*             //objChildObjectsJsonArray.append(*currentJsonValuePtr); */
/*             //continue; */
/*         //} */
/*         //SysOvrvTextLabel *sysOvrvTextLabel = dynamic_cast<SysOvrvTextLabel *>(child); */
/*         //if(sysOvrvTextLabel != Q_NULLPTR) */
/*         //{ */
/*             //sysOvrvTextLabel->accept(this); */
/*             //objLabelsJsonArray.append(*currentJsonValuePtr); */
/*             //continue; */
/*         //} */
/*     //} */
/* // */
/*     //tempJsonObject["ObjChildObjects"] = objChildObjectsJsonArray; */
/*     //tempJsonObject["ObjLabels"] = objLabelsJsonArray; */
/* // */
/*     //currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/* } */

/* void JsonOutParser::visit(SysOvrvTextLabel &visitor) */
/* { */
/* //    QJsonObject tempJsonObject; */
/* // */
/*     //tempJsonObject["SysOvrvTextLabel"] = QString("TestLabel"); */
/* // */
/*     //currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/* } */

/* void JsonOutParser::visit(SysOvrvTrigger &visitor) */
/* { */
/* } */

/* /1* void JsonOutParser::visit(ErrorLogView &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonOutParser::visit(ErrLogModel &visitor) */
/* { */
/* } */

/* void JsonOutParser::visit(ErrorLogEntry &visitor) */
/* { */
/* } */

