#include "SysOverviewObjectTriggerMsgTypeEvaluatorDialog.h"
#include "ui_sysoverviewobjecttriggermsgtypeevaluatordialog.h"

#include "MessageTypeIdentifier.h"
#include "SysOverviewObjectTriggerMsgTypeEvaluator.h"

#include "IMsgIDMappingManager.h"
#include "IMsgCodeMappingManager.h"

SysOverviewObjectTriggerMsgTypeEvaluatorDialog::SysOverviewObjectTriggerMsgTypeEvaluatorDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SysOverviewObjectTriggerMsgTypeEvaluatorDialog)
{
    ui->setupUi(this);
}

SysOverviewObjectTriggerMsgTypeEvaluatorDialog::~SysOverviewObjectTriggerMsgTypeEvaluatorDialog()
{
    delete ui;
}

MessageTypeIdentifier SysOverviewObjectTriggerMsgTypeEvaluatorDialog::getMsgType() const
{
    return MessageTypeIdentifier(
                ui->msgIDLE->getMsgID(),
                ui->msgCodeLE->getMsgCode()
                );
}

SysOvrvObjTriggerEvaluatorPtr SysOverviewObjectTriggerMsgTypeEvaluatorDialog::getEvaluator() const
{
    return SysOvrvObjTriggerEvaluatorPtr(
                new SysOverviewObjectTriggerMsgTypeEvaluator(
                    getMsgType()
                    )
                );
}

void SysOverviewObjectTriggerMsgTypeEvaluatorDialog::setMsgIDMappingManager(
        IMsgIDMappingManager *msgIDMappingManager
        )
{
    ui->msgIDLE->setMappingManager(msgIDMappingManager);
}

void SysOverviewObjectTriggerMsgTypeEvaluatorDialog::setMsgCodeMappingManager(
        IMsgCodeMappingManager *msgCodeMappingManager
        )
{
    ui->msgCodeLE->setMappingManager(msgCodeMappingManager);
}
