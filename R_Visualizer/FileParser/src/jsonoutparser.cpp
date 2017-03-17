#include "jsonoutparser.h"

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

void JsonOutParser::visit(MessageStream &visitor)
{
}

void JsonOutParser::visit(MsgStreamModel &visitor)
{
}

void JsonOutParser::visit(MsgStorage &visitor)
{
    QJsonArray tempJsonArray;
    /* tempJsonObject["MsgStorageSaveLocation"] = QJsonValue(visitor.saveMsgStorage(QString(""))); */
    /* currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
    const int msgStorageSize = visitor.size();
    for(int i = 0; i < msgStorageSize; ++i)
    {
        Msg msg = visitor.at(i);
        msg.accept(this);
        tempJsonArray.append(*currentJsonValuePtr);
    }
    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray));
}

void JsonOutParser::visit(SendMessages &visitor)
{
}

void JsonOutParser::visit(SendMsgModel &visitor)
{
    QVector<PrettyMsg> prettyMsgs = visitor.getMsgPacket();
    QJsonArray tempJsonArray;
    for(PrettyMsg &prettyMsg : prettyMsgs)
    {
        dynamic_cast<Msg&>(prettyMsg).accept(this);
        tempJsonArray.append(*currentJsonValuePtr);
    }
    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray));
}

void JsonOutParser::visit(Msg &visitor)
{
    QJsonObject tempJsonObject;
    QJsonArray tempJsonDataArray;

    tempJsonObject["MsgTimestamp"] = visitor.getTimestamp().toString(QString("dd.MM.yyyy - hh:mm:ss.zzz"));
    tempJsonObject["MsgID"] = QJsonValue(static_cast<int>(visitor.getId()));
    tempJsonObject["MsgCode"] = QJsonValue(static_cast<int>(visitor.getCode()));

    const MsgData &tempMsgData = visitor.getData();
    for(unsigned int i = 0; i < tempMsgData.DataSizeInBytes; ++i)
    {
        tempJsonDataArray.append(QJsonValue(static_cast<int>(tempMsgData.DataBytes.at(i))));
    }
    tempJsonObject["MsgData"] = tempJsonDataArray;
    
    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject));
}

void JsonOutParser::visit(MessageConfig &visitor)
{
}

void JsonOutParser::visit(IDModel &visitor)
{
    QJsonArray tempJsonArray;
    const int idModelSize = visitor.size();
    for(int i = 0; i < idModelSize; ++i)
    {
        IDRep idRep = visitor.at(i);
        idRep.accept(this);
        tempJsonArray.append(*currentJsonValuePtr);
    }
    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray));
}

void JsonOutParser::visit(IDRep &visitor)
{
    QJsonObject tempJsonObject;
    tempJsonObject["IDRepID"] = static_cast<int>(visitor.getId());
    tempJsonObject["IDRepName"] = visitor.getName();
    tempJsonObject["IDRepColor"] = visitor.getColor().name();

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject));
}

void JsonOutParser::visit(MsgTypeModel &visitor)
{
    QJsonArray tempJsonArray;
    const int msgTypeModelSize = visitor.size();
    for(int i = 0; i < msgTypeModelSize; ++i)
    {
        MsgTypeRep msgTypeRep = visitor.at(i);
        msgTypeRep.accept(this);
        tempJsonArray.append(*currentJsonValuePtr);
    }
    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray));
}

void JsonOutParser::visit(MsgTypeRep &visitor)
{
    QJsonObject tempJsonObject;
    tempJsonObject["MsgTypeRepCode"] = static_cast<int>(visitor.getCode());
    tempJsonObject["MsgTypeRepName"] = visitor.getCodeName();
    tempJsonObject["MsgTypeRepMessageFormat"] = visitor.getMessageFormat();
    tempJsonObject["MsgTypeRepColor"] = visitor.getColor().name();

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject));
}

void JsonOutParser::visit(MessageFilter &visitor)
{
}

void JsonOutParser::visit(FilterIDStore &visitor)
{
    QJsonArray tempJsonArray;

    const int filterIDStoreSize = visitor.size();
    for(int i = 0; i < filterIDStoreSize; ++i)
    {
        QJsonObject tempJsonObject;
        tempJsonObject["FilterID"] = QJsonValue(static_cast<int>(visitor.at(i)));
        tempJsonArray.append(tempJsonObject);
    }
    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray));
}

void JsonOutParser::visit(FilterCodeStore &visitor)
{
    QJsonArray tempJsonArray;

    const int filterCodeStoreSize = visitor.size();
    for(int i = 0; i < filterCodeStoreSize; ++i)
    {
        QJsonObject tempJsonObject;
        tempJsonObject["FilterCode"] = QJsonValue(static_cast<int>(visitor.at(i)));
        tempJsonArray.append(tempJsonObject);
    }
    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray));
}

void JsonOutParser::visit(FilterTimestampStore &visitor)
{
    QJsonObject tempJsonObject;
    tempJsonObject["FilterTimestampFrom"] = QJsonValue(visitor.getTimestampFilterFrom().toString("dd.MM.yyyy - hh:mm:ss.zzz"));
    tempJsonObject["FilterTimestampTo"] = QJsonValue(visitor.getTimestampFilterTo().toString("dd.MM.yyyy - hh:mm:ss.zzz"));

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject));
}

void JsonOutParser::visit(SystemOverview &visitor)
{
}

void JsonOutParser::visit(SysOvrvObject &visitor)
{
    //QJsonObject tempJsonObject;
    //tempJsonObject["ObjName"] = visitor.getObjName();
    //tempJsonObject["ObjShape"] = static_cast<int>(visitor.getShape());
//
    //const QColor &objColor = visitor.getObjColor();
    //tempJsonObject["ObjColor"] = objColor.name(QColor::HexArgb);
//
    //QJsonObject objSizeJsonObj;
    //const QRectF &objBoundingRect = visitor.boundingRect();
    //objSizeJsonObj["ObjWidth"] = static_cast<double>(objBoundingRect.width());
    //objSizeJsonObj["ObjHeight"] = static_cast<double>(objBoundingRect.height());
    //tempJsonObject["ObjSize"] = objSizeJsonObj;
//
    //OJsonObject objPosJsonObj;
    //objSizeJsonObj["XPos"] = static_cast<double>(visitor.x());
    //objSizeJsonObj["YPos"] = static_cast<double>(visitor.y());
    //tempJsonObject["ObjPos"] = objPosJsonObj;
//
    //QJsonArray objChildObjectsJsonArray;
    //OJsonArray objLabelsJsonArray;
//
    //QList<QGraphicsItem *> children = visitor.childItems();
//
    //for(QGraphicsItem *child : children)
    //{
        //SysOvrvObject *sysOvrvObjChild = dynamic_cast<SysOvrvObject *>(child);
        //if(sysOvrvObjChild != Q_NULLPTR)
        //{
            //sysOvrvObjChild->accept(this);
            //objChildObjectsJsonArray.append(*currentJsonValuePtr);
            //continue;
        //}
        //SysOvrvTextLabel *sysOvrvTextLabel = dynamic_cast<SysOvrvTextLabel *>(child);
        //if(sysOvrvTextLabel != Q_NULLPTR)
        //{
            //sysOvrvTextLabel->accept(this);
            //objLabelsJsonArray.append(*currentJsonValuePtr);
            //continue;
        //}
    //}
//
    //tempJsonObject["ObjChildObjects"] = objChildObjectsJsonArray;
    //tempJsonObject["ObjLabels"] = objLabelsJsonArray;
//
    //currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject));
}

void JsonOutParser::visit(SysOvrvTextLabel &visitor)
{
//    QJsonObject tempJsonObject;
//
    //tempJsonObject["SysOvrvTextLabel"] = QString("TestLabel");
//
    //currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject));
}

void JsonOutParser::visit(SysOvrvTrigger &visitor)
{
}

void JsonOutParser::visit(ErrorLogView &visitor)
{
}

void JsonOutParser::visit(ErrLogModel &visitor)
{
}

void JsonOutParser::visit(ErrorLogEntry &visitor)
{
}

