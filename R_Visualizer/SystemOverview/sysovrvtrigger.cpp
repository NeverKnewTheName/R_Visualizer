#include "sysovrvtrigger.h"

#include "sysovrvobject.h"
#include "../R_Visualizer_Utilities/templatevalueevaluator.h"

#include <QColor>

#include <QDebug>


QString TriggerNames[SysOvrvTrigger::NrOfTriggers] =
{
    "StandardTrigger",
    "ColorChangeTrigger",
    "TextChangeTrigger",
    "DimensionChangeTrigger"
};

SysOvrvTrigger::SysOvrvTrigger(SysOvrvObject *objToTrigger, TriggerType type) :
    m_pObjToTrigger(objToTrigger),
    evaluator(NULL),
    type(type)
{

}

void SysOvrvTrigger::trigger(QByteArray &canData)
{
    qDebug() << "Triggered";
}

QString &SysOvrvTrigger::printToString()
{
    return TriggerNames[type];
}

SysOvrvObject *SysOvrvTrigger::getRelatedSysOvrvObj()
{
    return m_pObjToTrigger;
}

SysOvrvTrigger::TriggerType SysOvrvTrigger::getType() const
{
    return type;
}

void SysOvrvTrigger::setType(const TriggerType &value)
{
    type = value;
}

TemplateValueEvaluator *SysOvrvTrigger::getEvaluator() const
{
    return evaluator;
}

void SysOvrvTrigger::setEvaluator(TemplateValueEvaluator *value)
{
    evaluator = value;
}

SysOvrvColorChangeTrigger::SysOvrvColorChangeTrigger(SysOvrvObject *objToTrigger) :
    SysOvrvTrigger(objToTrigger,ColorChangeTrigger)
{
    initialColor = QColor(objToTrigger->getMyColor());
}

void SysOvrvColorChangeTrigger::trigger(QByteArray &canData)
{
    qDebug() << "ColorChangeTrigger";
}

QColor SysOvrvColorChangeTrigger::getColorToChangeTo() const
{
    return colorToChangeTo;
}

void SysOvrvColorChangeTrigger::setColorToChangeTo(const QColor &value)
{
    colorToChangeTo = value;
}

QColor SysOvrvColorChangeTrigger::getInitialColor() const
{
    return initialColor;
}

void SysOvrvColorChangeTrigger::setInitialColor(const QColor &value)
{
    initialColor = value;
}
SysOvrvTextChangeTrigger::SysOvrvTextChangeTrigger(SysOvrvObject *objToTrigger) :
    SysOvrvTrigger(objToTrigger,TextChangeTrigger)

{

}

void SysOvrvTextChangeTrigger::trigger(QByteArray &canData)
{
    qDebug() << "TextChangeTrigger";
}

SysOvrvTextLabel *SysOvrvTextChangeTrigger::getTextLabelToChange() const
{
    return textLabelToChange;
}

void SysOvrvTextChangeTrigger::setTextLabelToChange(SysOvrvTextLabel *value)
{
    textLabelToChange = value;
}

QString SysOvrvTextChangeTrigger::getTextToChangeTo() const
{
    return textToChangeTo;
}

void SysOvrvTextChangeTrigger::setTextToChangeTo(const QString &value)
{
    textToChangeTo = value;
}

SysOvrvDimensionChangeTrigger::SysOvrvDimensionChangeTrigger(SysOvrvObject *objToTrigger) :
    SysOvrvTrigger(objToTrigger, DimensionChangeTrigger),
    dimensionToExpandTo(Top),
    startChangePercentage(0),
    endChangePercentage(100)
{

}

void SysOvrvDimensionChangeTrigger::trigger(QByteArray &canData)
{
    qDebug() << "DimensionChangeTrigger";
}
