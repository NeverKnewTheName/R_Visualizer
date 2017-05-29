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
    type(type)
{

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

QVector<TemplateValueEvaluator *> SysOvrvTrigger::getEvaluators() const
{
    return evaluators;
}

void SysOvrvTrigger::addEvaluator(TemplateValueEvaluator *value)
{
    evaluators.append(value);
}

void SysOvrvTrigger::removeEvaluator(TemplateValueEvaluator *value)
{
    evaluators.removeAll(value);
}

SysOvrvColorChangeTrigger::SysOvrvColorChangeTrigger(SysOvrvObject *objToTrigger) :
    SysOvrvTrigger(objToTrigger,ColorChangeTrigger)
{
    initialColor = QColor(objToTrigger->getObjColor());
    colorToChangeTo = QColor(Qt::white);
}

void SysOvrvColorChangeTrigger::trigger(QByteArray &canData)
{
    bool Evaluation = true;
    for(TemplateValueEvaluator *evaluator : evaluators)
    {
        Evaluation &= evaluator->evaluate(canData.at(0)); //ToDO
    }

    if(Evaluation != true)
    {
        m_pObjToTrigger->setObjColor(initialColor);
        return;
    }

    m_pObjToTrigger->setObjColor(colorToChangeTo);

    qDebug() << "ColorChangeTrigger";
}

QString SysOvrvColorChangeTrigger::printToString() const
{
    return QString("ColorChanageTrigger");
}

QString SysOvrvColorChangeTrigger::printFunctionToString() const
{
    //ToDO iterate Evaluators and add to string;
//    QString("if %1");
    return QString("Change Color from %1 to %2 %3").arg(this->initialColor.name(QColor::HexRgb)).arg(this->colorToChangeTo.name(QColor::HexRgb)).arg("");
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

QString SysOvrvTextChangeTrigger::printToString() const
{
    return QString("TextChangeTrigger");
}

QString SysOvrvTextChangeTrigger::printFunctionToString() const
{
    //ToDO iterate Evaluators and add to string;
//    QString("if %1");
    return QString("Change label text to %1 %2").arg(this->textToChangeTo).arg("");
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

QString SysOvrvDimensionChangeTrigger::printToString() const
{
    return QString("DimensionChangeTrigger");
}

QString SysOvrvDimensionChangeTrigger::printFunctionToString() const
{
    //ToDO iterate Evaluators and add to string;
//    QString("if %1");
    QString dimensionString;
    if(this->dimensionToExpandTo & Top)
    {
        dimensionString.append("top");
    }
    if(this->dimensionToExpandTo & Bottom)
    {
        if(!dimensionString.isEmpty())
        {
            dimensionString.append(" and ");
        }
        dimensionString.append("bottom");
    }
    if(this->dimensionToExpandTo & Left)
    {
        if(!dimensionString.isEmpty())
        {
            dimensionString.append(" and ");
        }
        dimensionString.append("left");
    }
    if(this->dimensionToExpandTo & Right)
    {
        if(!dimensionString.isEmpty())
        {
            dimensionString.append(" and ");
        }
        dimensionString.append("right");
    }


    return QString("Change Dimension %1 from %2 % to %3 % %4").arg(dimensionString).arg(this->startChangePercentage).arg(this->endChangePercentage).arg("");
}

void SysOvrvDimensionChangeTrigger::trigger(QByteArray &canData)
{
    qDebug() << "DimensionChangeTrigger";
}
