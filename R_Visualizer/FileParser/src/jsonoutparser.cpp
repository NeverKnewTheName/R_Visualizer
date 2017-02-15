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
}

void JsonOutParser::visit(IDRep &visitor)
{
}

void JsonOutParser::visit(MsgTypeModel &visitor)
{
}

void JsonOutParser::visit(MsgTypeRep &visitor)
{
}

void JsonOutParser::visit(MessageFilter &visitor)
{
}

void JsonOutParser::visit(FilterIDStore &visitor)
{
}

void JsonOutParser::visit(FilterCodeStore &visitor)
{
}

void JsonOutParser::visit(FilterTimestampStore &visitor)
{
}

void JsonOutParser::visit(SystemOverview &visitor)
{
}

void JsonOutParser::visit(SysOvrvObject &visitor)
{
}

void JsonOutParser::visit(SysOvrvTextLabel &visitor)
{
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

