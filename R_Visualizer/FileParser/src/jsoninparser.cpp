#include "jsoninparser.h"

#include "IMsg.h"
#include "ITimestampedMsg.h"
#include "IMsgStreamStore.h"
#include "msgstorage.h"
#include "ISendMsgPackageStore.h"
#include "IMsgIDMappingStore.h"
#include "IMsgIDMapping.h"
#include "MsgIDMapping.h"
#include "IMsgCodeMappingStore.h"
#include "IMsgCodeMapping.h"
#include "MsgCodeMapping.h"
#include "IMsgDataMappingStore.h"
#include "IMsgDataMapping.h"
#include "MsgDataMapping.h"
#include "IMsgIDFilterStore.h"
#include "IMsgCodeFilterStore.h"
#include "IMsgTimespanFilter.h"

#include "ISystemOverviewObject.h"
#include "ISysOverviewObjectManager.h"
#include "ISysOverviewObjectColorManager.h"
#include "ISysOverviewObjectResizeManager.h"
#include "SysOverviewTextLabel.h"
#include "ISysOverviewObjectTrigger.h"
#include "ISysOverviewLabelTrigger.h"
#include "ISysOverviewObjectTriggerEvaluator.h"

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
        currentJsonValuePtr =
            std::unique_ptr<QJsonValue>(new QJsonValue(jsonDoc.object()));
    }
    else if(jsonDoc.isArray())
    {
        currentJsonValuePtr =
            std::unique_ptr<QJsonValue>(new QJsonValue(jsonDoc.array()));
    }
}

void JsonInParser::visit(IMsg *visitor)
{
    const QJsonObject &tempIMsgJsonObject = currentJsonValuePtr->toObject();

    MsgIDType msgID(static_cast<MsgIDType::type>(tempIMsgJsonObject["MsgID"].toInt()));
    MsgCodeType msgCode(static_cast<MsgCodeType::type>(tempIMsgJsonObject["MsgCode"].toInt()));
    MsgDataType msgData;

    const QJsonArray &tempMsgDataJsonArray = tempIMsgJsonObject["MsgData"].toArray();

    for(const QJsonValue &dataByte : tempMsgDataJsonArray)
    {
        msgData.append(MsgDataByteType(static_cast<MsgDataByteType::type>(dataByte.toInt())));
    }

    visitor->setMsgID(msgID);
    visitor->setMsgCode(msgCode);
    visitor->setMsgData(msgData);
}

void JsonInParser::visit(ITimestampedMsg *visitor)
{
    const QJsonObject &tempITimestampedMsgJsonObject = currentJsonValuePtr->toObject();

    visitor->setTimestamp(
                QDateTime::fromString(
                    tempITimestampedMsgJsonObject["MsgTimestamp"].toString(),
                    "dd.MM.yyyy - hh:mm:ss.zzz"
                )
            );

    visit(dynamic_cast<IMsg *>(visitor));
}

void JsonInParser::visit(IMsgStreamStore *visitor)
{
    const QJsonArray &tempIMsgStreamStoreJsonArray = currentJsonValuePtr->toArray();

    for(const QJsonValue &msgJsonObject : tempIMsgStreamStoreJsonArray)
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(msgJsonObject));
        TimestampedMsg tempTimestampedMsg;
        visit(&tempTimestampedMsg);

        visitor->appendMsg(tempTimestampedMsg);
    }
}

void JsonInParser::visit(MsgStorage *visitor)
{
    const QJsonArray &tempMsgStorageJsonArray = currentJsonValuePtr->toArray();

    for(const QJsonValue &tempMsgJsonObject : tempMsgStorageJsonArray)
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(
                    new QJsonValue(tempMsgJsonObject)
                    );
        Msg tempMsg;
        tempMsg.accept(this);
        visitor->appendMsg(tempMsg);
    }
}

void JsonInParser::visit(TimestampedMsgStorage *visitor)
{
    const QJsonArray &tempTimestampedMsgStorageJsonArray = currentJsonValuePtr->toArray();

    for(const QJsonValue &tempTimestampedMsgJsonObject : tempTimestampedMsgStorageJsonArray)
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(
                    new QJsonValue(tempTimestampedMsgJsonObject)
                    );
        TimestampedMsg tempTimestampedMsg;
        tempTimestampedMsg.accept(this);
        visitor->appendMsg(tempTimestampedMsg);
    }
}

void JsonInParser::visit(ISendMsgPackageStore *visitor)
{
    const QJsonArray &tempMsgPackageJsonArray =
            currentJsonValuePtr->toArray();

    for(
        const QJsonValue &tempMsgJsonObject
        : tempMsgPackageJsonArray
        )
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(
                    new QJsonValue(tempMsgJsonObject)
                    );
        Msg tempMsg;
        tempMsg.accept(this);
        visitor->appendMsg(tempMsg);
    }
}

void JsonInParser::visit(IMsgIDMappingStore *visitor)
{
    const QJsonArray &tempIMsgIDMappingStoreJsonArray =
        currentJsonValuePtr->toArray();

    for(
        const QJsonValue &tempIMsgIDMappingJsonObject
        : tempIMsgIDMappingStoreJsonArray
        )
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(
                    new QJsonValue(tempIMsgIDMappingJsonObject)
                    );
        MsgIDMapping tempMsgIDMapping;
        tempMsgIDMapping.accept(this);
        visitor->addMsgIDMapping(tempMsgIDMapping.getID(),tempMsgIDMapping);
    }
}

void JsonInParser::visit(IMsgIDMapping *visitor)
{
    const QJsonObject &tempMsgIDMappingJsonObject =
        currentJsonValuePtr->toObject();

    visitor->setID(
            MsgIDType(
                static_cast<MsgIDType::type>(
                    tempMsgIDMappingJsonObject["MsgID"].toInt()
                    )
                )
            );
    visitor->setPlainTextAlias(
            tempMsgIDMappingJsonObject["MsgIDAlias"].toString()
            );
    visitor->setColorRepresentation(
            QColor(
                tempMsgIDMappingJsonObject["MsgIDColorRep"].toString()
                )
            );
}

void JsonInParser::visit(IMsgCodeMappingStore *visitor)
{
    const QJsonArray &tempIMsgCodeMappingStoreJsonArray =
        currentJsonValuePtr->toArray();

    for(
        const QJsonValue &tempIMsgCodeMappingJsonObject
        : tempIMsgCodeMappingStoreJsonArray
        )
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(
                new QJsonValue(tempIMsgCodeMappingJsonObject)
                );
        MsgCodeMapping tempMsgCodeMapping;
        tempMsgCodeMapping.accept(this);
        visitor->addMsgCodeMapping(
                tempMsgCodeMapping.getCode(),
                tempMsgCodeMapping
                );
    }
}

void JsonInParser::visit(IMsgCodeMapping *visitor)
{
    const QJsonObject &tempMsgCodeMappingJsonObject =
        currentJsonValuePtr->toObject();

    visitor->setCode(
            MsgCodeType(
                static_cast<MsgCodeType::type>(
                    tempMsgCodeMappingJsonObject["MsgCode"].toInt()
                    )
                )
            );
    visitor->setPlainTextAlias(
            tempMsgCodeMappingJsonObject["MsgCodeAlias"].toString()
            );
    visitor->setColorRepresentation(
            QColor(
                tempMsgCodeMappingJsonObject["MsgCodeColorRep"].toString()
                )
            );
}

void JsonInParser::visit(IMsgDataMappingStore *visitor)
{
    const QJsonArray &tempIMsgDataMappingStoreJsonArray =
        currentJsonValuePtr->toArray();

    for(
        const QJsonValue &tempIMsgDataMappingJsonObject
        : tempIMsgDataMappingStoreJsonArray
        )
    {
        currentJsonValuePtr = std::unique_ptr<QJsonValue>(
                    new QJsonValue(tempIMsgDataMappingJsonObject)
                    );

        MsgDataMapping tempMsgDataMapping;
        tempMsgDataMapping.accept(this);

        visitor->addMsgDataMapping(
                tempMsgDataMapping.getMsgID(),
                tempMsgDataMapping.getMsgCode(),
                tempMsgDataMapping
                );
    }
}

void JsonInParser::visit(IMsgDataMapping *visitor)
{
    const QJsonObject &tempMsgDataMappingJsonObject =
        currentJsonValuePtr->toObject();

    visitor->setMsgID(
            MsgIDType(
                static_cast<MsgIDType::type>(
                    tempMsgDataMappingJsonObject["MsgID"].toInt()
                    )
                )
            );

    visitor->setMsgCode(
            MsgCodeType(
                static_cast<MsgCodeType::type>(
                    tempMsgDataMappingJsonObject["MsgCode"].toInt()
                    )
                )
            );

    visitor->setMsgDataFormatString(
            tempMsgDataMappingJsonObject["MsgDataFormatString"].toString()
            );

    visitor->setMsgDataDefaultColor(
            QColor(
                tempMsgDataMappingJsonObject["MsgDataDefaultColor"].toString()
                )
            );
}

void JsonInParser::visit(IMsgIDFilterStore *visitor)
{
    const QJsonArray &tempIMsgIDFilterStoreJsonArray =
            currentJsonValuePtr->toArray();

    for(const QJsonValue &msgIDJsonVal : tempIMsgIDFilterStoreJsonArray)
    {
        MsgIDType msgID(
                    static_cast<MsgIDType::type>(
                        msgIDJsonVal.toObject()["FilterMsgID"].toInt()
                    )
                );
        visitor->addMsgID(msgID);
    }
}

void JsonInParser::visit(IMsgCodeFilterStore *visitor)
{
    const QJsonArray &tempIMsgCodeFilterStoreJsonArray =
            currentJsonValuePtr->toArray();

    for(const QJsonValue &msgCodeJsonVal : tempIMsgCodeFilterStoreJsonArray)
    {
        MsgCodeType msgCode(
                    static_cast<MsgCodeType::type>(
                        msgCodeJsonVal.toObject()["FilterMsgCode"].toInt()
                    )
                );
        visitor->addMsgCode(msgCode);
    }
}

void JsonInParser::visit(IMsgTimespanFilter *visitor)
{
    const QJsonObject &tempIMsgTimespanFilterJsonObject =
            currentJsonValuePtr->toObject();

    visitor->setTimestampFrom(
                QDateTime::fromString(
                    tempIMsgTimespanFilterJsonObject["FilterTimespanFrom"].toString(),
                    "dd.MM.yyyy - hh:mm:ss.zzz"
                    )
                );
    visitor->setTimestampTo(
                QDateTime::fromString(
                    tempIMsgTimespanFilterJsonObject["FilterTimespanTo"].toString(),
                    "dd.MM.yyyy - hh:mm:ss.zzz"
                    )
            );
}

#include "SystemOverviewObject.h"
#include "SysOverviewObjectShapeManager.h"
#include "SysOverviewObjectImageManager.h"
#include "SysOverviewObjectResizeManager.h"
#include "SysOverviewObjectColorTrigger.h"
#include "SysOverviewObjectTriggerMsgTypeEvaluator.h"
#include "SysOverviewObjectTriggerDSLEvaluator.h"
void JsonInParser::visit(ISystemOverviewObject *visitor)
{
    const QJsonObject &tempISysOverviewObjJsonObject =
            currentJsonValuePtr->toObject();

    visitor->setObjectName(
                tempISysOverviewObjJsonObject["ObjectName"].toString()
            );
    visitor->setX(
                static_cast<const qreal>(
                    tempISysOverviewObjJsonObject["ObjectPosition_X"].toDouble()
                    )
                );
    visitor->setY(
                static_cast<const qreal>(
                    tempISysOverviewObjJsonObject["ObjectPosition_Y"].toDouble()
                    )
                );
    SysOvrvObjectManagerPtr objManager;
    const QJsonObject tempObjManagerJsonObject =
           tempISysOverviewObjJsonObject["ObjectManager"].toObject();
    const ISysOverviewObjectManager::ObjectType objManagerType =
            static_cast<ISysOverviewObjectManager::ObjectType>(
                tempObjManagerJsonObject["ObjectManagerType"].toInt()
            );

    switch(objManagerType)
    {
    case ISysOverviewObjectManager::ImageType:
        objManager.reset(new SysOverviewObjectImageManager(visitor));
        break;
    case ISysOverviewObjectManager::ShapeType:
    default:
        objManager.reset(new SysOverviewObjectShapeManager(visitor));
        break;
    }

    currentJsonValuePtr.reset(new QJsonValue(tempObjManagerJsonObject));
    this->visit(objManager.get());
    visitor->setShapeManager(std::move(objManager));

    SysOvrvObjectResizeManagerPtr resizeManager;
    const QJsonObject tempResizeManagerJsonObject =
           tempISysOverviewObjJsonObject["ObjectResizeManager"].toObject();
    const ISysOverviewObjectResizeManager::ResizeManagerType resizeManagerType =
            static_cast<ISysOverviewObjectResizeManager::ResizeManagerType>(
                tempResizeManagerJsonObject["ObjectResizeManagerType"].toInt()
            );

    switch(resizeManagerType)
    {
    case ISysOverviewObjectResizeManager::ResizeManagerType_RectCornerResizeManager:
    default:
        resizeManager.reset(new SysOverviewObjectResizeManager(visitor));
        break;
    }

    currentJsonValuePtr.reset(new QJsonValue(tempResizeManagerJsonObject));
    this->visit(resizeManager.get());
    visitor->setResizeManager(std::move(resizeManager));

    const QJsonArray &tempTextLabelsJsonArray =
            tempISysOverviewObjJsonObject["ObjectLabels"].toArray();

    for(const QJsonValue &tempTextLabelJsonValue : tempTextLabelsJsonArray)
    {
        const QJsonObject &tempTextLabelJsonObject =
                tempTextLabelJsonValue.toObject();
        currentJsonValuePtr.reset(
                    new QJsonValue(
                        tempTextLabelJsonObject
                        )
                    );
        SysOvrvTextLabelPtr textLabelPtr(new SysOverviewTextLabel());
        SysOverviewTextLabel *tempTextLabelPtr = textLabelPtr.data();
        textLabelPtr->setParentItem(visitor);
        this->visit(textLabelPtr.data());
        const QPointF &labelPos = textLabelPtr->pos();
        visitor->addLabel(std::move(textLabelPtr));
        tempTextLabelPtr->setPos(labelPos);
    }

    const QJsonArray &tempObjTriggerJsonArray =
            tempISysOverviewObjJsonObject["ObjectTriggers"].toArray();

    for(const QJsonValue &tempObjTriggerJsonValue : tempObjTriggerJsonArray)
    {
        const QJsonObject &tempObjTriggerJsonObject =
                tempObjTriggerJsonValue.toObject();
        currentJsonValuePtr.reset(new QJsonValue(tempObjTriggerJsonObject));
        SysOvrvObjTriggerPtr objTriggerPtr;

        ISysOverviewObjectTrigger::TriggerType triggerType =
                static_cast<ISysOverviewObjectTrigger::TriggerType>(
                    tempObjTriggerJsonObject[""].toInt()
                );
        switch(triggerType)
        {
        case ISysOverviewObjectTrigger::TriggerType_ColorChangeTrigger:
        default:
            objTriggerPtr.reset(
                        new SysOverviewObjectColorTrigger(
                            visitor
                            )
                        );
            break;
        }

        currentJsonValuePtr.reset(new QJsonValue(tempObjTriggerJsonObject));
        this->visit(objTriggerPtr.data());
        objTriggerPtr->setSysOverviewObject(visitor);
        visitor->addObjectTrigger(objTriggerPtr);
    }

    const QJsonArray &tempChildObjJsonArray =
            tempISysOverviewObjJsonObject["ObjectChildObjects"].toArray();

    for(const QJsonValue &tempChildObjJsonValue : tempChildObjJsonArray)
    {
        const QJsonObject &tempChildObjJsonObject =
                tempChildObjJsonValue.toObject();
        currentJsonValuePtr.reset(
                    new QJsonValue(
                        tempChildObjJsonObject
                        )
                    );

        ISysOvrvObjPtr childObjPtr(new SystemOverviewObject(visitor));
        this->visit(childObjPtr.data());
        const QPointF &childPos = childObjPtr->pos();
        visitor->addChildObject(childObjPtr);
        childObjPtr->setPos(childPos);
    }
}

#include "ISysOverviewObjectColorManager.h"
void JsonInParser::visit(ISysOverviewObjectManager *visitor)
{
    const QJsonObject &tempSysOverviewObjManagerJsonObject =
            currentJsonValuePtr->toObject();

    const ISysOverviewObjectManager::ObjectType objectManagerType =
            visitor->getType();

    switch(objectManagerType)
    {
    case ISysOverviewObjectManager::ImageType:
    {
        SysOverviewObjectImageManager *imageManager =
                dynamic_cast<SysOverviewObjectImageManager *>(visitor);
        const QJsonObject &tempImageManagerJsonObject =
                tempSysOverviewObjManagerJsonObject["ImageManager"].toObject();
        QPixmap imageToSet;
        QByteArray imageRawData =
                tempImageManagerJsonObject["SerializedImagePNG"].toString().toLatin1();
        imageToSet.loadFromData(imageRawData, "PNG");
        imageManager->setImage(imageToSet);
    }
        break;
    case ISysOverviewObjectManager::ShapeType:
    default:
    {
        SysOverviewObjectShapeManager *shapeManager =
                dynamic_cast<SysOverviewObjectShapeManager*>(visitor);
        const QJsonObject &tempShapeManagerJsonObject =
                tempSysOverviewObjManagerJsonObject["ShapeManager"].toObject();

        shapeManager->setShape(
                    static_cast<SysOverviewObjectShapeManager::SysOverviewObjectShape>(
                        tempShapeManagerJsonObject["ObjectShapeManager_Shape"].toInt()
                        )
                    );

        SysOvrvObjColorManagerPtr colorManager =
                shapeManager->getColorManager();

        currentJsonValuePtr.reset(
                    new QJsonValue(
                        tempShapeManagerJsonObject["ObjectShapeManager_ColorManager"].toObject()
                    )
                );
        this->visit(colorManager.get());
        shapeManager->setColorManager(std::move(colorManager));
    }
        break;
    }
}

void JsonInParser::visit(ISysOverviewObjectColorManager *visitor)
{
    const QJsonObject &tempSysOvrvObjColorManagerJsonObject =
            currentJsonValuePtr->toObject();

    visitor->setBorderColor(
                QColor(
                    tempSysOvrvObjColorManagerJsonObject["BorderColor"].toString()
                )
            );
    visitor->setFillColor(
                QColor(
                    tempSysOvrvObjColorManagerJsonObject["FillColor"].toString()
                )
            );
    visitor->setTransparency(
                static_cast<const qreal>(
                    tempSysOvrvObjColorManagerJsonObject["Transparency"].toDouble()
                )
            );
}

void JsonInParser::visit(ISysOverviewObjectResizeManager *visitor)
{
    const QJsonObject &tempSysOvrvObjResizeManager =
            currentJsonValuePtr->toObject();

    const ISysOverviewObjectResizeManager::ResizeManagerType resizeManagerType =
            visitor->getType();

    switch (resizeManagerType) {
    case ISysOverviewObjectResizeManager::ResizeManagerType_RectCornerResizeManager:
    default:
    {
        SysOverviewObjectResizeManager *rectCornerResizeManager =
                dynamic_cast<SysOverviewObjectResizeManager*>(visitor);

        const qreal width =
                static_cast<const qreal>(
                    tempSysOvrvObjResizeManager["Width"].toDouble(
                    ));
        const qreal height =
                static_cast<const qreal>(
                    tempSysOvrvObjResizeManager["Height"].toDouble(
                    ));
        rectCornerResizeManager->setSize(QSizeF(width,height));
    }
        break;
    }
}

#include "ISysOverviewLabelTrigger.h"
#include "SysOverviewLabelTextChangeTrigger.h"
void JsonInParser::visit(SysOverviewTextLabel *visitor)
{
    const QJsonObject &tempSysOverviewTextLabelJsonObject =
            currentJsonValuePtr->toObject();

    visitor->setLabelText(
                tempSysOverviewTextLabelJsonObject["LabelText"].toString()
                );
    visitor->setX(
                static_cast<const qreal>(
                    tempSysOverviewTextLabelJsonObject["LabelPosition_X"].toInt()
                    )
                );
    visitor->setY(
                static_cast<const qreal>(
                    tempSysOverviewTextLabelJsonObject["LabelPosition_Y"].toInt()
                    )
                );

    const QJsonArray &tempTextLabelTriggersJsonArray =
            tempSysOverviewTextLabelJsonObject["LabelTriggers"].toArray();

    for(const QJsonValue &tempTextLabelTriggerJsonValue : tempTextLabelTriggersJsonArray)
    {
        const QJsonObject &tempTextLabelTriggerJsonObject =
                tempTextLabelTriggerJsonValue.toObject();
        SysOvrvLabelTriggerPtr textLabelTriggerPtr;

        const ISysOverviewLabelTrigger::TriggerType triggerType =
                static_cast<ISysOverviewLabelTrigger::TriggerType>(
                    tempTextLabelTriggerJsonObject["TextLabelTriggerType"].toInt()
                    );

        switch(triggerType)
        {
        case ISysOverviewLabelTrigger::TriggerType_TextChangeTrigger:
        default:
        {
            textLabelTriggerPtr.reset(new SysOverviewLabelTextChangeTrigger(visitor));
        }
            break;
        }

        currentJsonValuePtr.reset(
                    new QJsonValue(tempTextLabelTriggerJsonObject)
                    );
        this->visit(textLabelTriggerPtr.data());
        textLabelTriggerPtr->setSysOverviewLabel(visitor);
        visitor->addTrigger(textLabelTriggerPtr);
    }

}

#include "ISysOverviewObjectTriggerEvaluator.h"
#include "SysOverviewObjectTriggerMsgTypeEvaluator.h"
#include "SysOverviewObjectTriggerDSLEvaluator.h"
void JsonInParser::visit(ISysOverviewObjectTrigger *visitor)
{
    const QJsonObject &tempSysOvrvObjTriggerJsonObject =
            currentJsonValuePtr->toObject();

    const ISysOverviewObjectTrigger::TriggerType triggerType =
            visitor->getTriggerType();

    switch (triggerType) {
    case ISysOverviewObjectTrigger::TriggerType_ColorChangeTrigger:
    default:
    {
        SysOverviewObjectColorTrigger *colorChangeTrigger =
                dynamic_cast<SysOverviewObjectColorTrigger*>(visitor);
        const QJsonObject &tempColorChangeTriggerJsonObject =
                tempSysOvrvObjTriggerJsonObject["ColorChangeTrigger"].toObject();

        colorChangeTrigger->setTriggerColor(
                    QColor(
                        tempColorChangeTriggerJsonObject["TriggerColor"].toString()
                        )
                    );
    }
        break;
    }

    const QJsonObject &tempTriggerEvaluatorJsonObject =
            tempSysOvrvObjTriggerJsonObject["TriggerEvaluator"].toObject();

    const ISysOverviewObjectTriggerEvaluator::EvaluatorType triggerEvaluatorType =
        static_cast<ISysOverviewObjectTriggerEvaluator::EvaluatorType>(
                tempTriggerEvaluatorJsonObject["TriggerEvaluatorType"].toInt()
            );


    SysOvrvObjTriggerEvaluatorPtr triggerEvaluatorPtr;

    switch (triggerEvaluatorType)
    {
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_ParserEvaluator:
    {
        //ToDO
    }
        break;
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_DSLEvaluator:
    {
        triggerEvaluatorPtr.reset(
                    new SysOverviewObjectTriggerDSLEvaluator()
                    );
    }
        break;
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_MsgTypeEvaluator:
    default:
    {
        triggerEvaluatorPtr.reset(
                    new SysOverviewObjectTriggerMsgTypeEvaluator()
                    );
    }
        break;
    }

    currentJsonValuePtr.reset(
                new QJsonValue(tempTriggerEvaluatorJsonObject)
                );
    this->visit(triggerEvaluatorPtr.get());
    visitor->setTriggerEvaluator(std::move(triggerEvaluatorPtr));
}

void JsonInParser::visit(ISysOverviewLabelTrigger *visitor)
{
    const QJsonObject &tempLabelTriggerJsonObject =
            currentJsonValuePtr->toObject();

    const ISysOverviewLabelTrigger::TriggerType triggerType =
            visitor->getTriggerType();

    switch(triggerType)
    {
    case ISysOverviewLabelTrigger::TriggerType_TextChangeTrigger:
    default:
    {
        SysOverviewLabelTextChangeTrigger *textChangeTrigger =
                dynamic_cast<SysOverviewLabelTextChangeTrigger*>(
                    visitor
                    );
        const QJsonObject &tempTextChangeTriggerJsonObject =
                tempLabelTriggerJsonObject["TextChangeTrigger"].toObject();
    }
        break;
    }

    const QJsonObject &tempTriggerEvaluatorJsonObject =
            tempLabelTriggerJsonObject["TriggerEvaluator"].toObject();

    const ISysOverviewObjectTriggerEvaluator::EvaluatorType triggerEvaluatorType =
        static_cast<ISysOverviewObjectTriggerEvaluator::EvaluatorType>(
                tempTriggerEvaluatorJsonObject["TriggerEvaluatorType"].toInt()
            );


    SysOvrvObjTriggerEvaluatorPtr triggerEvaluatorPtr;

    switch (triggerEvaluatorType)
    {
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_ParserEvaluator:
    {
        //ToDO
    }
        break;
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_DSLEvaluator:
    {
        triggerEvaluatorPtr.reset(
                    new SysOverviewObjectTriggerDSLEvaluator()
                    );
    }
        break;
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_MsgTypeEvaluator:
    default:
    {
        triggerEvaluatorPtr.reset(
                    new SysOverviewObjectTriggerMsgTypeEvaluator()
                    );
    }
        break;
    }

    currentJsonValuePtr.reset(
                new QJsonValue(tempTriggerEvaluatorJsonObject)
                );
    this->visit(triggerEvaluatorPtr.get());
    visitor->setTriggerEvaluator(std::move(triggerEvaluatorPtr));
}

void JsonInParser::visit(ISysOverviewObjectTriggerEvaluator *visitor)
{
    const QJsonObject &tempTriggerEvaluatorJsonObject =
            currentJsonValuePtr->toObject();

    const QJsonObject &tempMsgTypeJsonObject =
            tempTriggerEvaluatorJsonObject["MsgType"].toObject();

    const MessageTypeIdentifier &msgType = MessageTypeIdentifier(
                MsgIDType(static_cast<MsgIDType::type>(tempMsgTypeJsonObject["MessageID"].toInt())),
                MsgCodeType(static_cast<MsgCodeType::type>(tempMsgTypeJsonObject["MessageCode"].toInt()))
                );

    visitor->setMsgType(msgType);

    const ISysOverviewObjectTriggerEvaluator::EvaluatorType triggerEvaluatorType =
            visitor->getType();

    switch(triggerEvaluatorType)
    {
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_ParserEvaluator:
    {
        //ToDO
    }
        break;
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_DSLEvaluator:
    {
        SysOverviewObjectTriggerDSLEvaluator *dslEvaluator =
                dynamic_cast<SysOverviewObjectTriggerDSLEvaluator*>(
                    visitor
                    );
        const QJsonObject &tempDSLEvaluatorJsonObject =
                tempTriggerEvaluatorJsonObject["DSLEvaluator"].toObject();
        dslEvaluator->setFormatString(
                    tempDSLEvaluatorJsonObject["FormatString"].toString()
                    );
    }
        break;
    case ISysOverviewObjectTriggerEvaluator::EvaluatorType_MsgTypeEvaluator:
    default:
    {
        SysOverviewObjectTriggerMsgTypeEvaluator *msgTypeEvaluator =
                dynamic_cast<SysOverviewObjectTriggerMsgTypeEvaluator*>(
                    visitor
                    );
        const QJsonObject &tempMsgTypeEvaluatorJsonObject =
                tempTriggerEvaluatorJsonObject["MsgTypeEvaluator"].toObject();
    }
        break;
    }
}


/* void JsonInParser::visit(SysOvrvObject *visitor) */
/* { */
/* } */

/* void JsonInParser::visit(SysOvrvTextLabel *visitor) */
/* { */
/* } */

/* void JsonInParser::visit(SysOvrvTrigger *visitor) */
/* { */
/* } */

/* void JsonInParser::visit(ErrLogModel *visitor) */
/* { */
/* } */

/* void JsonInParser::visit(ErrorLogEntry *visitor) */
/* { */
/* } */







/////////////////////////////////////////////////////END//////////////////////
/* void JsonInParser::visit(MsgStreamModel *visitor) */
/* { */
/* } */

/* void JsonInParser::visit(MsgStorage *visitor) */
/* { */
/*     QJsonArray tempJsonArray = currentJsonValuePtr->toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray.at(i).toObject())); */
/*         Msg newMsg; */
/*         newMsg.accept(this); */
/*         visitor->appendMsg(newMsg); */
/*     } */
/* } */

/* void JsonInParser::visit(TimestampedMsgStorage *visitor) */
/* { */
/*     QJsonArray tempJsonArray = currentJsonValuePtr->toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonArray.at(i).toObject())); */
/*         TimestampedMsg newMsg; */
/*         newMsg.accept(this); */
/*         visitor->appendMsg(newMsg); */
/*     } */
/* } */

/* /1* void JsonInParser::visit(SendMessages *visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(SendMsgPackageStore *visitor) */
/* { */
/*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */

/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); */
/*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); */
/*         Msg newMsg; */
/*         newMsg.accept(this); */
/*         visitor->appendMsg(PrettyMsg<Msg>(newMsg)); */
/*     } */
/* } */

/* void JsonInParser::visit(Msg *visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */
/*     visitor->setMsgID(MsgIDType(tempJsonObject["MsgID"].toInt())); */
/*     visitor->setMsgCode(MsgCodeType(tempJsonObject["MsgCode"].toInt())); */
/*     const QJsonArray &tempJsonArray = tempJsonObject["MsgData"].toArray(); */
/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     MsgDataType tempMsgData; */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         tempMsgData.append(MsgDataByteType(tempJsonArray.at(i).toInt())); */
/*     } */
/*     visitor->setMsgData(tempMsgData); */
/* } */

/* void JsonInParser::visit(TimestampedMsg *visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */
/*     visitor->setTimestamp( */
/*             QDateTime::fromString( */
/*                 tempJsonObject["MsgTimestamp"].toString(), */
/*                 QString("dd.MM.yyyy - hh:mm:ss.zzz") */
/*                 ) */
/*             ); */
/*     Msg originalMsg; */
/*     originalMsg.accept(this); */
/*     visitor->setOriginalMsg(originalMsg); */
/* } */

/* /1* void JsonInParser::visit(MessageConfig *visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* /1* void JsonInParser::visit(IDModel *visitor) *1/ */
/* /1* { *1/ */
/* /1*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); *1/ */
/* /1*     const int tempJsonArraySize = tempJsonArray.size(); *1/ */

/* /1*     for(int i = 0; i < tempJsonArraySize; ++i) *1/ */
/* /1*     { *1/ */
/* /1*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); *1/ */
/* /1*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); *1/ */
/* /1*         IDMapping newIDMapping; *1/ */
/* /1*         newIDMapping.accept(this); *1/ */
/* /1*         visitor->add(newIDMapping); *1/ */
/* /1*     } *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(MsgIDMapping *visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */

/*     visitor->setID(MsgIDType(tempJsonObject["IDMappingID"].toInt())); */
/*     visitor->setPlainTextAlias(tempJsonObject["IDMappingName"].toString()); */
/*     visitor->setColorMappingresentation(QColor(tempJsonObject["IDMappingColor"].toString())); */
/* } */

/* /1* void JsonInParser::visit(MsgTypeModel *visitor) *1/ */
/* /1* { *1/ */
/* /1*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); *1/ */
/* /1*     const int tempJsonArraySize = tempJsonArray.size(); *1/ */

/* /1*     for(int i = 0; i < tempJsonArraySize; ++i) *1/ */
/* /1*     { *1/ */
/* /1*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); *1/ */
/* /1*         currentJsonValuePtr = std::unique_ptr<QJsonValue>(new QJsonValue(tempJsonObject)); *1/ */
/* /1*         MsgTypeMapping newMsgTypeMapping; *1/ */
/* /1*         newMsgTypeMapping.accept(this); *1/ */
/* /1*         visitor->add(newMsgTypeMapping); *1/ */
/* /1*     } *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(MsgCodeMapping *visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */

/*     visitor->setCode(MsgCodeType(tempJsonObject["MsgTypeMappingCode"].toInt())); */
/*     visitor->setPlainTextAlias(tempJsonObject["MsgTypeMappingName"].toString()); */
/*     /1* visitor->setMessageFormat(tempJsonObject["MsgTypeMappingMessageFormat"].toString()); *1/ */
/*     visitor->setColorMappingresentation(QColor(tempJsonObject["MsgTypeMappingColor"].toString())); */
/* } */

/* void JsonInParser::visit(MsgDataMapping *visitor) */
/* { */
/* } */

/* /1* void JsonInParser::visit(MessageFilter *visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(FilterIDStore *visitor) */
/* { */
/*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); */

/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); */
/*         visitor->addID(static_cast<MsgIDType>(tempJsonObject["FilterID"].toInt())); */
/*     } */
/* } */

/* void JsonInParser::visit(FilterCodeStore *visitor) */
/* { */
/*     const QJsonArray &tempJsonArray = currentJsonValuePtr->toArray(); */

/*     const int tempJsonArraySize = tempJsonArray.size(); */
/*     for(int i = 0; i < tempJsonArraySize; ++i) */
/*     { */
/*         const QJsonObject &tempJsonObject = tempJsonArray.at(i).toObject(); */
/*         visitor->addCode(static_cast<MsgCodeType>(tempJsonObject["FilterCode"].toInt())); */
/*     } */
/* } */

/* void JsonInParser::visit(FilterTimestampStore *visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */
/*     visitor->setTimestampFilterFrom( */
/*             QDateTime::fromString( */
/*                 tempJsonObject["FilterTimestampFrom"].toString(), */
/*                 QString("dd.MM.yyyy - hh:mm:ss.zzz") */
/*                 ) */
/*             ); */
/*     visitor->setTimestampFilterTo( */
/*             QDateTime::fromString( */
/*                 tempJsonObject["FilterTimestampTo"].toString(), */
/*                 QString("dd.MM.yyyy - hh:mm:ss.zzz") */
/*                 ) */
/*             ); */
/* } */

/* /1* void JsonInParser::visit(SystemOverview *visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(SysOvrvObject *visitor) */
/* { */
/*     const QJsonObject &tempJsonObject = currentJsonValuePtr->toObject(); */
/*     //SysOvrvObject::ObjShapeType shape = static_cast<SysOvrvObject::ObjShapeType>( */
/*     //        tempJsonObject["ObjShape"] */
/*     //        ); */
/*     /1* SysOvrvObject *newSysOvrvObject *1/ */
/*     //DANG IT! Inheritance model does not work here... */
/* } */

/* void JsonInParser::visit(SysOvrvTextLabel *visitor) */
/* { */
/* } */

/* void JsonInParser::visit(SysOvrvTrigger *visitor) */
/* { */
/* } */

/* /1* void JsonInParser::visit(ErrorLogView *visitor) *1/ */
/* /1* { *1/ */
/* /1* } *1/ */

/* void JsonInParser::visit(ErrLogModel *visitor) */
/* { */
/* } */

/* void JsonInParser::visit(ErrorLogEntry *visitor) */
/* { */
/* } */
