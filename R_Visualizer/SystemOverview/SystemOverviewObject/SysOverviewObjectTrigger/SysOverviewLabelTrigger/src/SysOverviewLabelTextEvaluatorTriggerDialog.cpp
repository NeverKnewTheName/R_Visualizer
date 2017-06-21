#include "SysOverviewLabelTextEvaluatorTriggerDialog.h"
#include "ui_sysoverviewlabeltextevaluatortriggerdialog.h"

#include "SysOverviewLabelTextEvaluatorTrigger.h"

SysOverviewLabelTextEvaluatorTriggerDialog::SysOverviewLabelTextEvaluatorTriggerDialog(
        SysOverviewTextLabel *textLabel,
        QWidget *parent
        ) :
    QDialog(parent),
    ui(new Ui::SysOverviewLabelTextEvaluatorTriggerDialog),
    textLabel(textLabel)
{
    ui->setupUi(this);
}

SysOverviewLabelTextEvaluatorTriggerDialog::~SysOverviewLabelTextEvaluatorTriggerDialog()
{
    delete ui;
}

void SysOverviewLabelTextEvaluatorTriggerDialog::on_buttonBox_accepted()
{
    SysOvrvLabelTriggerPtr textChangeTrigger(
                new SysOverviewLabelTextEvaluatorTrigger(
                    textLabel,
                    ui->evaluator->getEvaluator()
                    )
                );
    emit sgnl_commitTrigger(textChangeTrigger);
}
