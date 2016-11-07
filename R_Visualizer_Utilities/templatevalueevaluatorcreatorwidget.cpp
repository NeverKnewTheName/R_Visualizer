#include "templatevalueevaluatorcreatorwidget.h"
#include "ui_limitevaluatorcreatorwidget.h"
#include "ui_rangeevaluatorcreatorwidget.h"
#include "ui_templatevalueevaluatorcreatorwidget.h"

#include "templatevalueevaluator.h"






LimitEvaluatorCreatorWidget::LimitEvaluatorCreatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LimitEvaluatorCreatorWidget)
{
    ui->setupUi(this);

    QStringList DataTypeItems;
    DataTypeItems << "Integer" << "Float";
    ui->DataTypeComboBox->addItems(DataTypeItems);

    QStringList EvaluationOperationItems;
    EvaluationOperationItems << "Equal to" << "Equal to or Greater than" << "Equal to or lower than" << "Greater than" << "Lower than";
    ui->EvalOpComboBox->addItems(EvaluationOperationItems);

    ui->LimitValueLineEdit->setText(QString::number(0));
}

LimitEvaluatorCreatorWidget::~LimitEvaluatorCreatorWidget()
{
    delete ui;
}

void LimitEvaluatorCreatorWidget::populateUi(SysOvrvTriggerLimitEvaluator *LimitEvaluator)
{
    ui->EvalOpComboBox->setCurrentIndex(static_cast<int>(LimitEvaluator->getEvalOp()));
    ui->LimitValueLineEdit->setText(QString::number(LimitEvaluator->getLimit()));
    // // // DEBUG // // //
    ui->DataTypeComboBox->setCurrentIndex(0);
    ui->DataTypeComboBox->setEditable(false);
    // // // DEBUG // // //
}

SysOvrvTriggerLimitEvaluator *LimitEvaluatorCreatorWidget::createLimitEvaluator() const
{
    int limit = ui->LimitValueLineEdit->text().toInt();
    SysOvrvTriggerLimitEvaluator::LimitEvaluatorOperation evalOp = static_cast<SysOvrvTriggerLimitEvaluator::LimitEvaluatorOperation>(ui->EvalOpComboBox->currentIndex());
    SysOvrvTriggerLimitEvaluator * newlyCreatedLimitEvaluator = new SysOvrvTriggerLimitEvaluator(limit, evalOp);
    return newlyCreatedLimitEvaluator;
}

void LimitEvaluatorCreatorWidget::updateLimitEvaluator(SysOvrvTriggerLimitEvaluator *evaluatorToUpdate) const
{
    int limit = ui->LimitValueLineEdit->text().toInt();
    SysOvrvTriggerLimitEvaluator::LimitEvaluatorOperation evalOp = static_cast<SysOvrvTriggerLimitEvaluator::LimitEvaluatorOperation>(ui->EvalOpComboBox->currentIndex());
    evaluatorToUpdate->setLimit(limit);
    evaluatorToUpdate->setEvalOp(evalOp);
}






RangeEvaluatorCreatorWidget::RangeEvaluatorCreatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RangeEvaluatorCreatorWidget)
{
    ui->setupUi(this);

    QStringList DataTypeItems;
    DataTypeItems << "Integer" << "Float";
    ui->DataTypeComboBox->addItems(DataTypeItems);

    QStringList EvaluationOperationItems;
    EvaluationOperationItems << "Is in range" << "Is out of range";
    ui->EvalOpComboBox->addItems(EvaluationOperationItems);

    ui->LowerBoundaryValueLineEdit->setText(QString::number(0));
    ui->UpperBoundaryValueLineEdit->setText(QString::number(100));
}

RangeEvaluatorCreatorWidget::~RangeEvaluatorCreatorWidget()
{
    delete ui;
}

void RangeEvaluatorCreatorWidget::populateUi(SysOvrvTriggerRangeEvaluator *RangeEvaluator)
{
    ui->EvalOpComboBox->setCurrentIndex(static_cast<int>(RangeEvaluator->getEvalOp()));
    ui->LowerBoundaryValueLineEdit->setText(QString::number(RangeEvaluator->getLowerBoundary()));
    ui->UpperBoundaryValueLineEdit->setText(QString::number(RangeEvaluator->getUpperBoundary()));
    // // // DEBUG // // //
    ui->DataTypeComboBox->setCurrentIndex(0);
    ui->DataTypeComboBox->setEditable(false);
    // // // DEBUG // // //
}

SysOvrvTriggerRangeEvaluator *RangeEvaluatorCreatorWidget::createRangeEvaluator() const
{
    int lowerBoundaryValue = ui->LowerBoundaryValueLineEdit->text().toInt();
    int upperBoundaryValue = ui->UpperBoundaryValueLineEdit->text().toInt();
    bool includeMarginValues = false;
    SysOvrvTriggerRangeEvaluator::RangeEvaluatorOperation evalOp = static_cast<SysOvrvTriggerRangeEvaluator::RangeEvaluatorOperation>(ui->EvalOpComboBox->currentIndex());
    SysOvrvTriggerRangeEvaluator * newlyCreatedRangeEvaluator = new SysOvrvTriggerRangeEvaluator(lowerBoundaryValue, upperBoundaryValue, evalOp, includeMarginValues);
    return newlyCreatedRangeEvaluator;
}

void RangeEvaluatorCreatorWidget::updateRangeEvaluator(SysOvrvTriggerRangeEvaluator *evaluatorToUpdate) const
{
    int lowerBoundaryValue = ui->LowerBoundaryValueLineEdit->text().toInt();
    int upperBoundaryValue = ui->UpperBoundaryValueLineEdit->text().toInt();
    bool includeMarginValues = false;
    SysOvrvTriggerRangeEvaluator::RangeEvaluatorOperation evalOp = static_cast<SysOvrvTriggerRangeEvaluator::RangeEvaluatorOperation>(ui->EvalOpComboBox->currentIndex());
    evaluatorToUpdate->setLowerBoundary(lowerBoundaryValue);
    evaluatorToUpdate->setUpperBoundary(upperBoundaryValue);
    evaluatorToUpdate->setEvalOp(evalOp);
}






TemplateValueEvaluatorCreatorWidget::TemplateValueEvaluatorCreatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateValueEvaluatorCreatorWidget),
    EvaluatorToEdit(NULL)
{
    ui->setupUi(this);

    QStringList items;
    items << "LimitEvaluator" << "RangeEvaluator";
    ui->EvaluatorTypeComboBox->addItems(items);

    ui->SpecificValueEvaluatorCreatorWidget->layout()->setMargin(0);
    ui->SpecificValueEvaluatorCreatorWidget->layout()->setContentsMargins(0,0,0,0);
    //    ui->SpecificValueEvaluatorCreatorWidget->layout()->setSizeConstraint();

    ui->EvaluatorTypeComboBox->setCurrentIndex(0);
}

TemplateValueEvaluatorCreatorWidget::TemplateValueEvaluatorCreatorWidget(TemplateValueEvaluator *EvaluatorToEdit, QWidget *parent) :
    TemplateValueEvaluatorCreatorWidget(parent)
{
    this->EvaluatorToEdit = EvaluatorToEdit;
    ui->EvaluatorTypeComboBox->setCurrentIndex(EvaluatorToEdit->getEvalType());
    switch(EvaluatorToEdit->getEvalType())
    {
    case TemplateValueEvaluator::LimitEvaluator:
        static_cast<LimitEvaluatorCreatorWidget*>(SpecificEvaluatorCreatorWidget)->populateUi(static_cast<SysOvrvTriggerLimitEvaluator *>(EvaluatorToEdit));
        break;
    case TemplateValueEvaluator::RangeEvaluator:
        static_cast<RangeEvaluatorCreatorWidget*>(SpecificEvaluatorCreatorWidget)->populateUi(static_cast<SysOvrvTriggerRangeEvaluator *>(EvaluatorToEdit));
        break;
    }
}

TemplateValueEvaluatorCreatorWidget::~TemplateValueEvaluatorCreatorWidget()
{
    delete ui;
}

void TemplateValueEvaluatorCreatorWidget::on_EvaluatorTypeComboBox_currentIndexChanged(int index)
{
    QLayoutItem* item;
    while ( ( item = ui->SpecificValueEvaluatorCreatorWidget->layout()->takeAt( 0 ) ) != NULL )
    {
            delete item->widget();
            delete item;
    }

    SpecificEvaluatorCreatorWidget = NULL;

    switch(index)
    {
    case TemplateValueEvaluator::LimitEvaluator:
        SpecificEvaluatorCreatorWidget = new LimitEvaluatorCreatorWidget(this);
        break;
    case TemplateValueEvaluator::RangeEvaluator:
        SpecificEvaluatorCreatorWidget = new RangeEvaluatorCreatorWidget(this);
        break;
    }
    if(SpecificEvaluatorCreatorWidget != NULL)
        ui->SpecificValueEvaluatorCreatorWidget->layout()->addWidget(SpecificEvaluatorCreatorWidget);
    updateGeometry();
}


void TemplateValueEvaluatorCreatorWidget::on_AddEvaluatorPushButton_clicked()
{
    switch(ui->EvaluatorTypeComboBox->currentIndex())
    {
    case TemplateValueEvaluator::LimitEvaluator:
        if(EvaluatorToEdit == NULL)
            EvaluatorToEdit = static_cast<LimitEvaluatorCreatorWidget*>(SpecificEvaluatorCreatorWidget)->createLimitEvaluator();
        else
            static_cast<LimitEvaluatorCreatorWidget*>(SpecificEvaluatorCreatorWidget)->updateLimitEvaluator(static_cast<SysOvrvTriggerLimitEvaluator*>(EvaluatorToEdit));
        break;
    case TemplateValueEvaluator::RangeEvaluator:
        if(EvaluatorToEdit == NULL)
            EvaluatorToEdit = static_cast<RangeEvaluatorCreatorWidget*>(SpecificEvaluatorCreatorWidget)->createRangeEvaluator();
        else
            static_cast<RangeEvaluatorCreatorWidget*>(SpecificEvaluatorCreatorWidget)->updateRangeEvaluator(static_cast<SysOvrvTriggerRangeEvaluator*>(EvaluatorToEdit));
        break;
    }
    emit newTemplateValueEvaluatorCreated(EvaluatorToEdit);
    close();
}
