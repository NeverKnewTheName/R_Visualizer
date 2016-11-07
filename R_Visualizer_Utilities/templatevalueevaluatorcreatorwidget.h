#ifndef TEMPLATEVALUEEVALUATORCREATORWIDGET_H
#define TEMPLATEVALUEEVALUATORCREATORWIDGET_H

#include <QWidget>

class TemplateValueEvaluator;
class SysOvrvTriggerLimitEvaluator;
class SysOvrvTriggerRangeEvaluator;

namespace Ui {
class TemplateValueEvaluatorCreatorWidget;
class LimitEvaluatorCreatorWidget;
class RangeEvaluatorCreatorWidget;
}

class LimitEvaluatorCreatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LimitEvaluatorCreatorWidget(QWidget *parent = 0);
    ~LimitEvaluatorCreatorWidget();

    void populateUi(SysOvrvTriggerLimitEvaluator *LimitEvaluator);
    SysOvrvTriggerLimitEvaluator *createLimitEvaluator() const;
    void updateLimitEvaluator(SysOvrvTriggerLimitEvaluator *evaluatorToUpdate) const;
private slots:

private:
    Ui::LimitEvaluatorCreatorWidget *ui;
};


class RangeEvaluatorCreatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RangeEvaluatorCreatorWidget(QWidget *parent = 0);
    ~RangeEvaluatorCreatorWidget();

    void populateUi(SysOvrvTriggerRangeEvaluator *RangeEvaluator);
    SysOvrvTriggerRangeEvaluator *createRangeEvaluator() const;
    void updateRangeEvaluator(SysOvrvTriggerRangeEvaluator *evaluatorToUpdate) const;
private:
    Ui::RangeEvaluatorCreatorWidget *ui;
};



class TemplateValueEvaluatorCreatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateValueEvaluatorCreatorWidget(QWidget *parent = 0);
    explicit TemplateValueEvaluatorCreatorWidget(TemplateValueEvaluator *EvaluatorToEdit, QWidget *parent = 0);
    ~TemplateValueEvaluatorCreatorWidget();

signals:
    void newTemplateValueEvaluatorCreated(TemplateValueEvaluator*);

private slots:
    void on_EvaluatorTypeComboBox_currentIndexChanged(int index);

    void on_AddEvaluatorPushButton_clicked();

private:
    Ui::TemplateValueEvaluatorCreatorWidget *ui;
    QWidget *SpecificEvaluatorCreatorWidget;
    TemplateValueEvaluator *EvaluatorToEdit;
};

#endif // TEMPLATEVALUEEVALUATORCREATORWIDGET_H
