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
    ui->msgIDWidget->setMappingManager(msgIDMappingManager);
}

void SendMsgSingleWidget::setMsgIDCompleter(
        QCompleter *msgIDCompleter
        )
{
    ui->msgIDWidget->setCompleter(msgIDCompleter);
}

void SendMsgSingleWidget::setMsgCodeMapping(
        IMsgCodeMappingManager *msgCodeMappingManager
        )
{
    ui->msgCodeWidget->setMappingManager(msgCodeMappingManager);
}

void SendMsgSingleWidget::setMsgCodeCompleter(
        QCompleter *msgCodeCompleter
        )
{
    ui->msgCodeWidget->setCompleter(msgCodeCompleter);
}

void SendMsgSingleWidget::setMsgDataMapping(
        IMsgDataMappingManager *msgDataMappingManager
        )
{
    ui->msgDataWidget->setMappingManager(msgDataMappingManager);
}

void SendMsgSingleWidget::on_sndMsgSendBtn_clicked()
{
    const MsgIDType msgID = ui->msgIDWidget->getMsgID();
    const MsgCodeType msgCode = ui->msgCodeWidget->getMsgCode();
    const MsgDataType msgData = ui->msgDataWidget->getMsgData();

    Msg msgToSend(msgID,msgCode,msgData);

    sendMsgSingle->sendMessage(msgToSend);
}
