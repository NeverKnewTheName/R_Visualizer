#include "SysOverviewLabelTextChangeTriggerDialog.h"
#include "ui_sysoverviewlabeltextchangetriggerdialog.h"

#include "SysOverviewLabelTextChangeTrigger.h"

SysOverviewLabelTextChangeTriggerDialog::SysOverviewLabelTextChangeTriggerDialog(
        SysOverviewTextLabel *textLabel,
        QWidget *parent
        ) :
    QDialog(parent),
    ui(new Ui::SysOverviewLabelTextChangeTriggerDialog),
    textLabel(textLabel)
{
    ui->setupUi(this);
}

SysOverviewLabelTextChangeTriggerDialog::~SysOverviewLabelTextChangeTriggerDialog()
{
    delete ui;
}

void SysOverviewLabelTextChangeTriggerDialog::on_buttonBox_accepted()
{
    SysOvrvLabelTriggerPtr textChangeTrigger(
                new SysOverviewLabelTextChangeTrigger(
                    textLabel,
                    ui->evaluator->getEvaluator()
                    )
                );
    emit sgnl_commitTrigger(textChangeTrigger);
}
