#include "SendMsgSingleWidget.h"
#include "ui_sendmsgsinglewidget.h"

#include "ISendMsgSingle.h"

#include "IMsgIDMappingManager.h"
#include "IMsgCodeMappingManager.h"
#include "IMsgDataMappingManager.h"

#include "Msg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

#include "MsgWidget.h"

SendMsgSingleWidget::SendMsgSingleWidget(
        ISendMsgSingle *sendMsgSingle,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SendMsgSingleWidget),
    sendMsgSingle(sendMsgSingle)
{
    ui->setupUi(this);
}

SendMsgSingleWidget::~SendMsgSingleWidget()
{
    delete ui;
}

void SendMsgSingleWidget::setMsgIDMapping(
        IMsgIDMappingManager *msgIDMappingManager
        )
{
    ui->msgWidget->setMsgIDMapping(msgIDMappingManager);
}

void SendMsgSingleWidget::setMsgIDCompleter(
        QCompleter *msgIDCompleter
        )
{
    ui->msgWidget->setMsgIDCompleter(msgIDCompleter);
}

void SendMsgSingleWidget::setMsgCodeMapping(
        IMsgCodeMappingManager *msgCodeMappingManager
        )
{
    ui->msgWidget->setMsgCodeMapping(msgCodeMappingManager);
}

void SendMsgSingleWidget::setMsgCodeCompleter(
        QCompleter *msgCodeCompleter
        )
{
    ui->msgWidget->setMsgCodeCompleter(msgCodeCompleter);
}

void SendMsgSingleWidget::setMsgDataMapping(
        IMsgDataMappingManager *msgDataMappingManager
        )
{
    //ui->msgDataWidget->setMappingManager(msgDataMappingManager);
}

void SendMsgSingleWidget::on_sndMsgSendBtn_clicked()
{
    Msg msgToSend(ui->msgWidget->getMsg());

    sendMsgSingle->sendMessage(msgToSend);
}

void SendMsgSingleWidget::on_sndMsgAddToPackageBtn_clicked()
{
    Msg msgToAdd(ui->msgWidget->getMsg());

    emit sgnl_AddToPackage(msgToAdd);
}
