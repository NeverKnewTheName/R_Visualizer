#ifndef SYSOVRVTRIGGER_H
#define SYSOVRVTRIGGER_H

#include <QColor>

class SysOvrvObject;
class SysOvrvTextLabel;

class QString;
class QByteArray;
class TemplateValueEvaluator;

class SysOvrvTrigger
{
public:
    typedef enum  {
        StandardTrigger,
        ColorChangeTrigger,
        TextChangeTrigger,
        DimensionChangeTrigger,
        NrOfTriggers
    }TriggerType;

    SysOvrvTrigger(SysOvrvObject *objToTrigger, TriggerType type);

    virtual void trigger(QByteArray &canData) = 0;
    virtual QString &printToString();

    SysOvrvObject *getRelatedSysOvrvObj();


    TriggerType getType() const;
    void setType(const TriggerType &value);

    TemplateValueEvaluator *getEvaluator() const;
    void setEvaluator(TemplateValueEvaluator *value);

private:
    bool evaluateData(QByteArray &canData);
    SysOvrvObject *m_pObjToTrigger;
    TemplateValueEvaluator *evaluator;
    TriggerType type;
};

class SysOvrvColorChangeTrigger : public SysOvrvTrigger
{
public:
    SysOvrvColorChangeTrigger(SysOvrvObject *objToTrigger);

    virtual void trigger(QByteArray &canData) override;

    QColor getColorToChangeTo() const;
    void setColorToChangeTo(const QColor &value);

    QColor getInitialColor() const;
    void setInitialColor(const QColor &value);

private:
    QColor initialColor;
    QColor colorToChangeTo;
};

class SysOvrvTextChangeTrigger : public SysOvrvTrigger
{
public:
    SysOvrvTextChangeTrigger(SysOvrvObject *objToTrigger);

    virtual void trigger(QByteArray &canData) override;

    SysOvrvTextLabel *getTextLabelToChange() const;
    void setTextLabelToChange(SysOvrvTextLabel *value);

    QString getTextToChangeTo() const;
    void setTextToChangeTo(const QString &value);

private:
    SysOvrvTextLabel *textLabelToChange;
    QString textToChangeTo;
};

class SysOvrvDimensionChangeTrigger : public SysOvrvTrigger
{
public:
    SysOvrvDimensionChangeTrigger(SysOvrvObject *objToTrigger);

    typedef enum {
        Top = 0x1,
        Left = 0x2,
        Right = 0x4,
        Bottom = 0x8
    } Dimension;

    virtual void trigger(QByteArray &canData) override;

    void setupTrigger(Dimension dimensionToExpandTo, qreal startPercentage, qreal endPercentage);


private:
    Dimension dimensionToExpandTo;
    qreal startChangePercentage;
    qreal endChangePercentage;
};

//PositionChangeTrigger

#endif // SYSOVRVTRIGGER_H
