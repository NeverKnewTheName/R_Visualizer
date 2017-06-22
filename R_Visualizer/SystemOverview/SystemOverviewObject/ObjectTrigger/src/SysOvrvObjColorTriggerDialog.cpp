#include "SysOvrvObjColorTriggerDialog.h"
#include "ui_sysovrvobjcolortriggerdialog.h"

#include "IMsgIDMappingManager.h"
#include "IMsgCodeMappingManager.h"

#include "ISystemOverviewObject.h"
#include "SysOverviewObjectShapeManager.h"
#include "SysOverviewObjectColorManager.h"
#include "SysOverviewObjectColorTrigger.h"

#include <QColor>

SysOvrvObjColorTriggerDialog::SysOvrvObjColorTriggerDialog(
        ISystemOverviewObject *sysOvrvObject,
        QWidget *parent
        ) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjColorTriggerDialog),
    sysOvrvObject(sysOvrvObject)
{
ui->setupUi(this);

SysOvrvObjectShapeManagerPtr objManager =
        SysOvrvObjectShapeManagerPtr(
            dynamic_cast<SysOverviewObjectShapeManager*>(
                sysOvrvObject->getShapeManager().release()
                )
            );

if(objManager.get() != Q_NULLPTR)
{
    SysOvrvObjColorManagerPtr colorManager(
            objManager->getColorManager()
                );
    const QString &colorName =
            colorManager->getFillColor().name();
    ui->currentColorLE->setText(
                colorName
                );
    ui->currentColorLE->setStyleSheet(
                QString("QLineEdit { background: %1; }")
                    .arg(colorName)
                );

    ui->triggerColorLE->setText(
                colorName
                );
    ui->triggerColorLE->setStyleSheet(
                QString("QLineEdit { background: %1; }")
                    .arg(colorName)
                );
}
}

SysOvrvObjColorTriggerDialog::~SysOvrvObjColorTriggerDialog()
{
delete ui;
}

void SysOvrvObjColorTriggerDialog::setMsgIDMappingManager(
    IMsgIDMappingManager *msgIDMappingManager
    )
{
    ui->evaluator->setMsgIDMappingManager(msgIDMappingManager);
}

void SysOvrvObjColorTriggerDialog::setMsgCodeMappingManager(
    IMsgCodeMappingManager *msgCodeMappingManager
    )
{
    ui->evaluator->setMsgCodeMappingManager(msgCodeMappingManager);
}

void SysOvrvObjColorTriggerDialog::on_triggerColorLE_editingFinished()
{
    const QString &colorName = ui->triggerColorLE->text();

    ui->triggerColorLE->setStyleSheet(
                QString("QLineEdit { background: %1; }")
                    .arg(colorName)
                );
}

void SysOvrvObjColorTriggerDialog::on_buttonBox_accepted()
{
    SysOvrvObjTriggerPtr colorTrigger(
                new SysOverviewObjectColorTrigger(
                    sysOvrvObject,
                    QColor(ui->triggerColorLE->text()),
                    ui->evaluator->getEvaluator()
                    )
                );
    emit sgnl_commitTrigger(colorTrigger);
}
