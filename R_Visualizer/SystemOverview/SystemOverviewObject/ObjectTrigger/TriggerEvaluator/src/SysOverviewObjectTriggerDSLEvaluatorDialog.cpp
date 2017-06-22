#include "SysOverviewObjectTriggerDSLEvaluatorDialog.h"
#include "ui_sysoverviewobjecttriggerdslevaluatordialog.h"

#include "SysOverviewObjectTriggerDSLEvaluator.h"

SysOverviewObjectTriggerDSLEvaluatorDialog::SysOverviewObjectTriggerDSLEvaluatorDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SysOverviewObjectTriggerDSLEvaluatorDialog)
{
    ui->setupUi(this);
}

SysOverviewObjectTriggerDSLEvaluatorDialog::~SysOverviewObjectTriggerDSLEvaluatorDialog()
{
    delete ui;
}

MessageTypeIdentifier SysOverviewObjectTriggerDSLEvaluatorDialog::getMsgType() const
{
    return MessageTypeIdentifier(
                ui->msgIDLE->getMsgID(),
                ui->msgCodeLE->getMsgCode()
                );
}

SysOvrvObjTriggerEvaluatorPtr SysOverviewObjectTriggerDSLEvaluatorDialog::getEvaluator() const
{
    return SysOvrvObjTriggerEvaluatorPtr(
                new SysOverviewObjectTriggerDSLEvaluator(
                    getMsgType(),
                    ui->formatStringPlainTextEdit->document()->toPlainText()
                    )
                );
}

void SysOverviewObjectTriggerDSLEvaluatorDialog::setMsgIDMappingManager(
        IMsgIDMappingManager *msgIDMappingManager
        )
{
    ui->msgIDLE->setMappingManager(msgIDMappingManager);
}

void SysOverviewObjectTriggerDSLEvaluatorDialog::setMsgCodeMappingManager(
        IMsgCodeMappingManager *msgCodeMappingManager
        )
{
    ui->msgCodeLE->setMappingManager(msgCodeMappingManager);
}
