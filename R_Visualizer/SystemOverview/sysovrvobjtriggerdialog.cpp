#include "sysovrvobjtriggerdialog.h"
#include "ui_sysovrvobjtriggerdialog.h"

#include "sysovrvtriggermodel.h"

SysOvrvObjTriggerDialog::SysOvrvObjTriggerDialog(SysOvrvObject *sysOvrvObj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjTriggerDialog),
    ObjectToTrigger(sysOvrvObj)
{
    ui->setupUi(this);
    ui->TriggerTreeView->setModel(new SysOvrvTriggerModel(this));
}

SysOvrvObjTriggerDialog::~SysOvrvObjTriggerDialog()
{
    delete ui;
}

void SysOvrvObjTriggerDialog::on_buttonBox_accepted()
{

}

void SysOvrvObjTriggerDialog::on_AddTriggerBtn_clicked()
{

}

void SysOvrvObjTriggerDialog::on_RemoveTriggerBtn_clicked()
{

}

void SysOvrvObjTriggerDialog::on_EditTriggerBtn_clicked()
{

}
