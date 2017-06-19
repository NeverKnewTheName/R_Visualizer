#include "jsonoutparser.h"

#include "IMsg.h"
#include "ITimestampedMsg.h"
#include "IMsgStreamStore.h"
#include "msgstorage.h"
#include "ISendMsgPackageStore.h"
#include "IMsgIDMappingStore.h"
#include "IMsgIDMapping.h"
#include "IMsgCodeMappingStore.h"
#include "IMsgCodeMapping.h"
#include "IMsgDataMappingStore.h"
#include "IMsgDataMapping.h"
#include "IMsgIDFilterStore.h"
#include "IMsgCodeFilterStore.h"
#include "IMsgTimespanFilter.h"

#include "ISystemOverviewObject.h"
#include "ISysOverviewObjectManager.h"
#include "SysOverviewObjectShapeManager.h"
#include "SysOverviewObjectImageManager.h"
#include "ISysOverviewObjectColorManager.h"
#include "ISysOverviewObjectResizeManager.h"
#include "SysOverviewTextLabel.h"
#include "ISysOverviewObjectTrigger.h"
#include "ISysOverviewLabelTrigger.h"
#include "ISysOverviewObjectTriggerEvaluator.h"

#include <QBuffer>
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
            return QJsonDocument(
                    {"BooleanValue", currentJsonValuePtr->toBool()}
                    );
            break;
        case QJsonValue::Double:
            return QJsonDocument(
                    {"DoubleValue", currentJsonValuePtr->toDouble()}
                    );
            break;
        case QJsonValue::String:
            return QJsonDocument(
                    {"StringValue", currentJsonValuePtr->toString()}
                    );
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

void JsonOutParser::visit(IMsg &visitor)
{
    QJsonObject tempIMsgJsonObject;
    QJsonArray tempIMsgDataJsonArray;

    const MsgIDType &msgID = visitor.getMsgID();
    const MsgCodeType &msgCode = visitor.getMsgCode();
    const MsgDataType &msgData = visitor.getMsgData();

    tempIMsgJsonObject["MsgID"] =
        QJsonValue(static_cast<int>(msgID.getPrimitiveData()));
    tempIMsgJsonObject["MsgCode"] =
        QJsonValue(static_cast<int>(msgCode.getPrimitiveData()));

    for(const MsgDataByteType byte : msgData)
    {
        tempIMsgDataJsonArray.append(
                QJsonValue(static_cast<int>(byte.getPrimitiveData()))
                );
    }
    tempIMsgJsonObject["MsgData"] = tempIMsgDataJsonArray;

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgJsonObject)
            );
}

void JsonOutParser::visit(ITimestampedMsg &visitor)
{
    visit(dynamic_cast<IMsg &>(visitor));

    const QDateTime &msgTimestamp = visitor.getTimestamp();

    QJsonObject tempITimestampedMsgJsonObject =
        currentJsonValuePtr->toObject();

    tempITimestampedMsgJsonObject["MsgTimestamp"] =
        msgTimestamp.toString("dd.MM.yyyy - hh:mm:ss.zzz");

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempITimestampedMsgJsonObject)
            );
}

#include "PrettyTimestampedMsg.h"
void JsonOutParser::visit(IMsgStreamStore &visitor)
{
    QJsonArray tempIMsgStreamJsonArray;

    const int msgStreamStoreSize = visitor.size();

    for(int i = 0; i < msgStreamStoreSize; ++i)
    {
        //PrettyTimestampedMsg prettyTimestampedMsg(visitor.at(i));
        //visit(dynamic_cast<IMsg>(prettyTimestampedMsg));
    }
}

void JsonOutParser::visit(MsgStorage &visitor)
{
    QJsonArray tempMsgStorageJsonArray;
    const int msgStorageSize = visitor.size();

    for(int i = 0; i < msgStorageSize; ++i)
    {
        Msg msgToParse(visitor.at(i));
        visit(msgToParse);
        tempMsgStorageJsonArray.append(currentJsonValuePtr->toObject());
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempMsgStorageJsonArray)
            );
}

void JsonOutParser::visit(TimestampedMsgStorage &visitor)
{
    QJsonArray tempMsgStorageJsonArray;
    const int msgStorageSize = visitor.size();

    for(int i = 0; i < msgStorageSize; ++i)
    {
        TimestampedMsg msgToParse(visitor.at(i));
        visit(msgToParse);
        tempMsgStorageJsonArray.append(currentJsonValuePtr->toObject());
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempMsgStorageJsonArray)
            );
}

void JsonOutParser::visit(ISendMsgPackageStore &visitor)
{
    QJsonArray tempISendMsgPackageJsonArray;

    const int msgPackageSize = visitor.size();

    for(int i = 0; i < msgPackageSize; ++i)
    {
        visit(visitor.at(i));
        tempISendMsgPackageJsonArray.append(
                    currentJsonValuePtr->toObject()
                    );
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
                new QJsonValue(tempISendMsgPackageJsonArray)
                );
}

void JsonOutParser::visit(IMsgIDMappingStore &visitor)
{
    QJsonArray tempIMsgIDMappingJsonArray;

    const QVector<MsgIDType> &msgIDs = visitor.getContainedMsgIDs();

    for(const MsgIDType &msgID : msgIDs)
    {
        visit(visitor.getMsgIDMappingToMsgID(msgID));
        tempIMsgIDMappingJsonArray.append(currentJsonValuePtr->toObject());
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgIDMappingJsonArray)
            );
}

void JsonOutParser::visit(IMsgIDMapping &visitor)
{
    QJsonObject tempIMsgIDMappingJsonObject;

    tempIMsgIDMappingJsonObject["MsgID"] =
        visitor.getID().getPrimitiveData();
    tempIMsgIDMappingJsonObject["MsgIDAlias"] =
        visitor.getPlainTextAlias();
    tempIMsgIDMappingJsonObject["MsgIDColorRep"] =
        visitor.getColorRepresentation().name();

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgIDMappingJsonObject)
            );
}

void JsonOutParser::visit(IMsgCodeMappingStore &visitor)
{
    QJsonArray tempIMsgCodeMappingJsonArray;

    const QVector<MsgCodeType> &msgCodes =
        visitor.getContainedMsgCodes();

    for(const MsgCodeType &msgCode : msgCodes)
    {
        visit(visitor.getMsgCodeMappingToMsgCode(msgCode));
        tempIMsgCodeMappingJsonArray.append(
                currentJsonValuePtr->toObject()
                );
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgCodeMappingJsonArray)
            );
}

void JsonOutParser::visit(IMsgCodeMapping &visitor)
{
    QJsonObject tempIMsgCodeMappingJsonObject;

    tempIMsgCodeMappingJsonObject["MsgCode"] =
        visitor.getCode().getPrimitiveData();
    tempIMsgCodeMappingJsonObject["MsgCodeAlias"] =
        visitor.getPlainTextAlias();
    tempIMsgCodeMappingJsonObject["MsgCodeColorRep"] =
        visitor.getColorRepresentation().name();

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgCodeMappingJsonObject)
            );
}

void JsonOutParser::visit(IMsgDataMappingStore &visitor)
{
    QJsonArray tempIMsgDataMappingJsonArray;

    const QVector<MessageTypeIdentifier> msgTypeIdentifierList =
        visitor.getContainedTypeIdentifiers();

    for(const MessageTypeIdentifier &msgTypeID : msgTypeIdentifierList)
    {
        visit(visitor.getMsgDataMapping(msgTypeID));
        tempIMsgDataMappingJsonArray.append(
                currentJsonValuePtr->toObject()
                );
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgDataMappingJsonArray)
            );
}

void JsonOutParser::visit(IMsgDataMapping &visitor)
{
    QJsonObject tempIMsgDataMappingJsonObject;

    tempIMsgDataMappingJsonObject["MsgID"] =
        visitor.getMsgID().getPrimitiveData();
    tempIMsgDataMappingJsonObject["MsgCode"] =
        visitor.getMsgCode().getPrimitiveData();
    tempIMsgDataMappingJsonObject["MsgDataFormatString"] =
        visitor.getMsgDataFormatString();
    tempIMsgDataMappingJsonObject["MsgDataDefaultColor"] =
        visitor.getMsgDataDefaultColor().name();

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgDataMappingJsonObject)
            );
}

void JsonOutParser::visit(IMsgIDFilterStore &visitor)
{
    QJsonArray tempIMsgIDFilterStoreJsonArray;

    const int filterStoreSize = visitor.size();

    for(int i = 0; i < filterStoreSize; ++i)
    {
        QJsonObject tempIMsgIDFilterJsonObject;
        tempIMsgIDFilterJsonObject["FilterMsgID"] =
                static_cast<int>(visitor.at(i).getPrimitiveData());
        tempIMsgIDFilterStoreJsonArray.append(
                    tempIMsgIDFilterJsonObject
                    );
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgIDFilterStoreJsonArray)
            );
}

void JsonOutParser::visit(IMsgCodeFilterStore &visitor)
{
    QJsonArray tempIMsgCodeFilterStoreJsonArray;

    const int filterStoreSize = visitor.size();

    for(int i = 0; i < filterStoreSize; ++i)
    {
        QJsonObject tempIMsgCodeFilterJsonObject;
        tempIMsgCodeFilterJsonObject["FilterMsgCode"] =
                static_cast<int>(visitor.at(i).getPrimitiveData());

        tempIMsgCodeFilterStoreJsonArray.append(
                    tempIMsgCodeFilterJsonObject
                    );
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgCodeFilterStoreJsonArray)
            );
}

void JsonOutParser::visit(IMsgTimespanFilter &visitor)
{
    QJsonObject tempIMsgTimespanFilterJsonObject;

    tempIMsgTimespanFilterJsonObject["FilterTimespanFrom"] =
            visitor.getTimestampFrom().toString("dd.MM.yyyy - hh:mm:ss.zzz");

    tempIMsgTimespanFilterJsonObject["FilterTimespanTo"] =
            visitor.getTimestampTo().toString("dd.MM.yyyy - hh:mm:ss.zzz");

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempIMsgTimespanFilterJsonObject)
                );
}

void JsonOutParser::visit(ISystemOverviewObject &visitor)
{
    QJsonObject tempISysOverviewObjJsonObject;

    const QString objectName = visitor.getObjectName();

    tempISysOverviewObjJsonObject["ObjectName"] = objectName;
    tempISysOverviewObjJsonObject["ObjectPosition_X"] =
            static_cast<const double>(visitor.x());
    tempISysOverviewObjJsonObject["ObjectPosition_Y"] =
            static_cast<const double>(visitor.y());

    SysOvrvObjectManagerPtr objManager =
            visitor.getShapeManager();
    this->visit(*objManager);
    tempISysOverviewObjJsonObject["ObjectManager"] =
            currentJsonValuePtr->toObject();

    SysOvrvObjectResizeManagerPtr objResizeManager =
            visitor.getResizeManager();
    this->visit(*objResizeManager);
    tempISysOverviewObjJsonObject["ObjectResizeManager"] = objectName;
            currentJsonValuePtr->toObject();

    const QVector<SysOvrvTextLabelPtr> objLocalLabels =
            visitor.getLabels();

    QJsonArray tempObjLabelsJsonArray;
    for(SysOvrvTextLabelPtr labelPtr : objLocalLabels)
    {
        this->visit(*labelPtr);
        tempObjLabelsJsonArray.append(currentJsonValuePtr->toObject());
    }

    tempISysOverviewObjJsonObject["ObjectLabels"] =
            tempObjLabelsJsonArray;

    const QVector<SysOvrvObjTriggerPtr> objLocalTriggers =
            visitor.getLocalObjectTriggers();

    QJsonArray tempObjTriggerJsonArray;
    for(SysOvrvObjTriggerPtr triggerPtr : objLocalTriggers)
    {
        this->visit(*triggerPtr);
        tempObjTriggerJsonArray.append(currentJsonValuePtr->toObject());
    }

    tempISysOverviewObjJsonObject["ObjectTriggers"] =
            tempObjTriggerJsonArray;

    const QVector<ISysOvrvObjPtr> childObjects =
            visitor.getChildObjects();
    QJsonArray tempObjChildObjJsonArray;

    for(ISysOvrvObjPtr childObjPtr : childObjects)
    {
        this->visit(*childObjPtr);
        tempObjChildObjJsonArray.append(currentJsonValuePtr->toObject());
    }

    tempISysOverviewObjJsonObject["ObjectChildObjects"] =
            tempObjChildObjJsonArray;

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempISysOverviewObjJsonObject)
                );
}

void JsonOutParser::visit(ISysOverviewObjectManager &visitor)
{
    QJsonObject tempISysOverviewObjManagerJsonObject;
    const ISysOverviewObjectManager::ObjectType objManagerType =
            visitor.getType();

    tempISysOverviewObjManagerJsonObject["ObjectManagerType"] =
            static_cast<const int>(objManagerType);

    switch(objManagerType)
    {
    case ISysOverviewObjectManager::ShapeType:
    {
        QJsonObject tempSysOverviewObjectShapeManager;
        try
        {
            SysOverviewObjectShapeManager &shapeManager =
                    dynamic_cast<SysOverviewObjectShapeManager &>(visitor);

            tempSysOverviewObjectShapeManager["ObjectShapeManager_Shape"] =
                    static_cast<const int>(shapeManager.getShape());

            SysOvrvObjColorManagerPtr colorManager =
                    shapeManager.getColorManager();

            this->visit(*colorManager);

            tempSysOverviewObjectShapeManager["ObjectShapeManager_ColorManager"] =
                    currentJsonValuePtr->toObject();

            tempISysOverviewObjManagerJsonObject["ShapeManager"] =
                    tempSysOverviewObjectShapeManager;
        }
        catch(const std::exception e)
        {
            qDebug() << "Exception caught in " << __PRETTY_FUNCTION__ <<
                        " -- " << e.what();
        }
    }
        break;
    case ISysOverviewObjectManager::ImageType:
    {
        QJsonObject tempSysOverviewObjectImageManager;
        try
        {
            SysOverviewObjectImageManager &imageManager =
                    dynamic_cast<SysOverviewObjectImageManager &>(visitor);
            QByteArray bytes;
            QBuffer buffer(&bytes);
            buffer.open(QIODevice::WriteOnly);
            imageManager.getImage().save(&buffer, "PNG");

            tempSysOverviewObjectImageManager["SerializedImagePNG"] =
                    QString(bytes);

            tempISysOverviewObjManagerJsonObject["ImageManager"] =
                    tempSysOverviewObjectImageManager;
        }
        catch(const std::exception e)
        {
            qDebug() << "Exception caught in " << __PRETTY_FUNCTION__ <<
                        " -- " << e.what();
        }
    }
        break;
    default:
        break;
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempISysOverviewObjManagerJsonObject)
                );
}

void JsonOutParser::visit(ISysOverviewObjectColorManager &visitor)
{
    QJsonObject tempISysOverviewObjectColorManagerJsonObject;

    tempISysOverviewObjectColorManagerJsonObject["BorderColor"] =
            visitor.getBorderColor().name();
    tempISysOverviewObjectColorManagerJsonObject["FillColor"] =
            visitor.getFillColor().name();
    tempISysOverviewObjectColorManagerJsonObject["Transparency"] =
            static_cast<const double>(visitor.getTransparency());

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempISysOverviewObjectColorManagerJsonObject)
                );
}

void JsonOutParser::visit(ISysOverviewObjectResizeManager &visitor)
{
    QJsonObject tempISysOverviewObjectResizeManagerJsonObject;

    tempISysOverviewObjectResizeManagerJsonObject["Width"] =
            visitor.getSize().width();
    tempISysOverviewObjectResizeManagerJsonObject["Height"] =
            visitor.getSize().height();

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempISysOverviewObjectResizeManagerJsonObject)
                );
}

void JsonOutParser::visit(SysOverviewTextLabel &visitor)
{
    QJsonObject tempISysOverviewTextLabelJsonObject;

    tempISysOverviewTextLabelJsonObject["LabelText"] =
            visitor.text();
    tempISysOverviewTextLabelJsonObject["LabelPosition_X"] =
            static_cast<const double>(visitor.x());
    tempISysOverviewTextLabelJsonObject["LabelPosition_Y"] =
            static_cast<const double>(visitor.y());

    const QVector<SysOvrvLabelTriggerPtr> labelTriggers =
            visitor.getTriggers();

    QJsonArray labelTriggersJsonArray;
    for(SysOvrvLabelTriggerPtr labelTriggerPtr : labelTriggers)
    {
        this->visit(*labelTriggerPtr);
        labelTriggersJsonArray.append(currentJsonValuePtr->toObject());
    }

    tempISysOverviewTextLabelJsonObject["LabelTriggers"] =
            labelTriggersJsonArray;

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempISysOverviewTextLabelJsonObject)
                );
}

#include "SysOverviewObjectColorTrigger.h"
void JsonOutParser::visit(ISysOverviewObjectTrigger &visitor)
{
    QJsonObject tempISysOverviewObjectTriggerJsonObject;

    const ISysOverviewObjectTrigger::TriggerType triggerType =
            visitor.getTriggerType();

    switch(triggerType)
    {
    case ISysOverviewObjectTrigger::TriggerType_ColorChangeTrigger:
    {
        try
        {
            SysOverviewObjectColorTrigger &colorChangeTrigger =
                    dynamic_cast<SysOverviewObjectColorTrigger &>(visitor);

            QJsonObject tempColorChangeTriggerJsonObject;

            tempColorChangeTriggerJsonObject["TriggerColor"] =
                    colorChangeTrigger.getTriggerColor().name();

            tempColorChangeTriggerJsonObject["OriginalColor"] =
                    colorChangeTrigger.getOriginalColor().name();

            tempISysOverviewObjectTriggerJsonObject["ColorChangeTrigger"] =
                    tempColorChangeTriggerJsonObject;
        }
        catch(const std::exception e)
        {
            qDebug() << "Exception caught in " << __PRETTY_FUNCTION__ <<
                        " -- " << e.what();
        }
    }
        break;
    default:
        break;
    }

    SysOvrvObjTriggerEvaluatorPtr triggerEvaluator =
            visitor.getTriggerEvaluator();

    this->visit(*triggerEvaluator);

    tempISysOverviewObjectTriggerJsonObject["TriggerEvaluator"] =
            currentJsonValuePtr->toObject();

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempISysOverviewObjectTriggerJsonObject)
                );
}

#include "SysOverviewLabelTextChangeTrigger.h"
void JsonOutParser::visit(ISysOverviewLabelTrigger &visitor)
{
    QJsonObject tempISysOverviewObjectLableTriggerJsonObject;

    const ISysOverviewLabelTrigger::TriggerType triggerType =
            visitor.getTriggerType();

    switch(triggerType)
    {
    case ISysOverviewLabelTrigger::TriggerType_TextChangeTrigger:
    {
        try
        {
            SysOverviewLabelTextChangeTrigger &textChangeTrigger =
                    dynamic_cast<SysOverviewLabelTextChangeTrigger &>(visitor);

            QJsonObject tempTextChangeTriggerJsonObject;

            tempISysOverviewObjectLableTriggerJsonObject["TextChangeTrigger"] =
                    tempTextChangeTriggerJsonObject;
        }
        catch(const std::exception e)
        {
            qDebug() << "Exception caught in " << __PRETTY_FUNCTION__ <<
                        " -- " << e.what();
        }
    }
        break;
    default:
        break;
    }

    SysOvrvObjTriggerEvaluatorPtr triggerEvaluator =
            visitor.getTriggerEvaluator();

    this->visit(*triggerEvaluator);

    tempISysOverviewObjectLableTriggerJsonObject["TriggerEvaluator"] =
            currentJsonValuePtr->toObject();

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempISysOverviewObjectLableTriggerJsonObject)
                );
}

#include "SysOverviewObjectTriggerMsgTypeEvaluator.h"
#include "SysOverviewObjectTriggerDSLEvaluator.h"
void JsonOutParser::visit(ISysOverviewObjectTriggerEvaluator &visitor)
{
    QJsonObject tempISysOverviewObjectTriggerEvaluatorJsonObject;

    const MessageTypeIdentifier msgType = visitor.getMsgType();

    QJsonObject tempMsgTypeJsonObject;

    tempMsgTypeJsonObject["MessageID"] =
            static_cast<const int>(msgType.getID().getPrimitiveData());
    tempMsgTypeJsonObject["MessageCode"] =
            static_cast<const int>(msgType.getCode().getPrimitiveData());

    tempISysOverviewObjectTriggerEvaluatorJsonObject["MsgType"] =
            tempMsgTypeJsonObject;

    const ISysOverviewObjectTriggerEvaluator::EvaluatorType type =
            visitor.getType();

    switch(type)
    {
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_MsgTypeEvaluator:
    {
        try
        {
            SysOverviewObjectTriggerMsgTypeEvaluator &msgTypeEvaluator =
                    dynamic_cast<SysOverviewObjectTriggerMsgTypeEvaluator &>(visitor);
            QJsonObject msgTypeEvaluatorJsonObject;

            tempISysOverviewObjectTriggerEvaluatorJsonObject["MsgTypeEvaluator"] =
                    msgTypeEvaluatorJsonObject;
        }
        catch(const std::exception e)
        {
            qDebug() << "Exception caught in " << __PRETTY_FUNCTION__ <<
                        " -- " << e.what();
        }
    }
        break;
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_DSLEvaluator:
    {
        try
        {
            SysOverviewObjectTriggerDSLEvaluator &dslEvaluator =
                    dynamic_cast<SysOverviewObjectTriggerDSLEvaluator &>(visitor);

            QJsonObject dslEvalutorJsonObject;
            dslEvalutorJsonObject["FormatString"] =
                dslEvaluator.getFormatString();

            tempISysOverviewObjectTriggerEvaluatorJsonObject["DSLEvaluator"] =
                    dslEvalutorJsonObject;
        }
        catch(const std::exception e)
        {
            qDebug() << "Exception caught in " << __PRETTY_FUNCTION__ <<
                        " -- " << e.what();
        }
    }
        break;
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_ParserEvaluator:
    {
//        ToDO
          QJsonObject parserEvalutorJsonObject;

          tempISysOverviewObjectTriggerEvaluatorJsonObject["ParserEvaluator"] =
                   parserEvalutorJsonObject;
    }
        break;
    }

    currentJsonValuePtr = std::unique_ptr<QJsonValue>(
            new QJsonValue(tempISysOverviewObjectTriggerEvaluatorJsonObject)
                );
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
/* void JsonOutParser::visit(IMsgStreamModel &visitor) */
/* { */
/* } */

/* void JsonOutParser::visit(IMsgStorage &visitor) */
/* { */
/*     QJsonArray tempJsonArray; */
/*     /1* tempJsonObject["IMsgStorageSaveLocation"] = QJsonValue(visitor.saveIMsgStorage(QString(""))); *1/ */
/*     /1* currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); *1/ */
/*     const int msgStorageSize = visitor.size(); */
/*     for(int i = 0; i < msgStorageSize; ++i) */
/*     { */
/*         IMsg msg = visitor.at(i); */
/*         msg.accept(this); */
/*         tempJsonArray.append(*currentJsonValuePtr); */
/*     } */
/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); */
/* } */

/* void JsonOutParser::visit(TimestampedIMsgStorage &visitor) */
/* { */
/*     QJsonArray tempJsonArray; */
/*     /1* tempJsonObject["IMsgStorageSaveLocation"] = QJsonValue(visitor.saveIMsgStorage(QString(""))); *1/ */
/*     /1* currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); *1/ */
/*     const int msgStorageSize = visitor.size(); */
/*     for(int i = 0; i < msgStorageSize; ++i) */
/*     { */
/*         TimestampedIMsg msg = visitor.at(i); */
/*         msg.accept(this); */
/*         tempJsonArray.append(*currentJsonValuePtr); */
/*     } */
/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); */
/* } */

/* /1* void JsonOutParser::visit(SendMessages &visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonOutParser::visit(SendIMsgPackageStore &visitor) */
/* { */
/*     QVector<PrettyIMsg> prettyIMsgs = visitor.getIMsgPacket(); */
/*     QJsonArray tempJsonArray; */
/*     for(PrettyIMsg &prettyIMsg : prettyIMsgs) */
/*     { */
/*         dynamic_cast<IMsg&>(prettyIMsg).accept(this); */
/*         tempJsonArray.append(*currentJsonValuePtr); */
/*     } */
/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); */
/* } */

/* void JsonOutParser::visit(IMsg &visitor) */
/* { */
/*     QJsonObject tempJsonObject; */
/*     QJsonArray tempJsonDataArray; */

/*     tempJsonObject["IMsgID"] = QJsonValue(static_cast<IMsgIDType::type>(visitor.getIMsgID())); */
/*     tempJsonObject["IMsgCode"] = QJsonValue(static_cast<IMsgCodeType::type>(visitor.getIMsgCode())); */

/*     const IMsgDataType &tempIMsgData = visitor.getIMsgData(); */
/*     const int tempIMsgDataSize = tempIMsgData.size(); */
/*     for(unsigned int i = 0; i < tempIMsgDataSize; ++i) */
/*     { */
/*         tempJsonDataArray.append(QJsonValue(static_cast<IMsgDataByteType::type>(tempIMsgData.at(i)))); */
/*     } */
/*     tempJsonObject["IMsgData"] = tempJsonDataArray; */

/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/* } */

/* void JsonOutParser::visit(TimestampedIMsg &visitor) */
/* { */
/*     IMsg originalIMsg = visitor.getOriginalIMsg(); */
/*     originalIMsg.accept(this); */

/*     QJsonObject tempJsonObject = currentJsonValuePtr->toObject(); */
/*     tempJsonObject["IMsgTimestamp"] = visitor.getTimestamp().toString( */
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

/* void JsonOutParser::visit(IMsgIDMapping &visitor) */
/* { */
/*     QJsonObject tempJsonObject; */
/*     tempJsonObject["IMsgIDMappingID"] = static_cast<int>( */
/*             static_cast<IMsgIDType::type>( */
/*                 visitor.getID() */
/*                 ) */
/*             ); */
/*     tempJsonObject["IMsgIDMappingName"] = visitor.getPlainTextAlias(); */
/*     tempJsonObject["IMsgIDMappingColor"] = visitor.getColorMappingresentation().name(); */

/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/* } */

/* /1* void JsonOutParser::visit(IMsgTypeModel &visitor) *1/ */
/* /1* { *1/ */
/* /1*     QJsonArray tempJsonArray; *1/ */
/* /1*     const int msgTypeModelSize = visitor.size(); *1/ */
/* /1*     for(int i = 0; i < msgTypeModelSize; ++i) *1/ */
/* /1*     { *1/ */
/* /1*         IMsgTypeMapping msgTypeMapping = visitor.at(i); *1/ */
/* /1*         msgTypeMapping.accept(this); *1/ */
/* /1*         tempJsonArray.append(*currentJsonValuePtr); *1/ */
/* /1*     } *1/ */
/* /1*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray)); *1/ */
/* /1* } *1/ */

/* void JsonOutParser::visit(IMsgCodeMapping &visitor) */
/* { */
/*     QJsonObject tempJsonObject; */
/*     tempJsonObject["IMsgCodeMappingCode"] = static_cast<int>( */
/*             static_cast<IMsgCodeType::type>( */
/*                 visitor.getCode() */
/*                 ) */
/*             ); */
/*     tempJsonObject["IMsgCodeMappingName"] = visitor.getPlainTextAlias(); */
/*     /1* tempJsonObject["IMsgCodeMappingMessageFormat"] = visitor.getMessageFormat(); *1/ */
/*     tempJsonObject["IMsgCodeMappingColor"] = visitor.getColorMappingresentation().name(); */

/*     currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/* } */

/* void JsonOutParser::visit(IMsgDataMapping &visitor) */
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
/*         tempJsonObject["FilterID"] = QJsonValue(static_cast<IMsgIDType::type>(visitor.at(i))); */
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
/*         tempJsonObject["FilterCode"] = QJsonValue(static_cast<IMsgCodeType::type>(visitor.at(i))); */
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

