#include "MsgWidget.h"
#include "ui_msgwidget.h"

MsgWidget::MsgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgWidget),
    msgIDMappingManager(Q_NULLPTR),
    msgCodeMappingManager(Q_NULLPTR)
{
    ui->setupUi(this);
}

MsgWidget::~MsgWidget()
{
    delete ui;
}

MsgIDType MsgWidget::getMsgID() const
{
    return ui->msgIDWidget->getMsgID();
}

MsgCodeType MsgWidget::getMsgCode() const
{
    return ui->msgCodeWidget->getMsgCode();
}

MsgDataType MsgWidget::getMsgData() const
{
    return ui->msgDataWidget->getMsgData();
}

Msg MsgWidget::getMsg() const
{
    Msg assembledMsg(getMsgID(),getMsgCode(),getMsgData());
    return assembledMsg;
}

void MsgWidget::setMsgIDMapping(IMsgIDMappingManager *msgIDMappingManager)
{
    ui->msgIDWidget->setMappingManager(msgIDMappingManager);
}

void MsgWidget::setMsgIDCompleter(QCompleter *msgIDCompleter)
{
    ui->msgIDWidget->setCompleter(msgIDCompleter);
}

void MsgWidget::setMsgCodeMapping(IMsgCodeMappingManager *msgCodeMappingManager)
{
    ui->msgCodeWidget->setMappingManager(msgCodeMappingManager);
}

void MsgWidget::setMsgCodeCompleter(QCompleter *msgCodeCompleter)
{
    ui->msgCodeWidget->setCompleter(msgCodeCompleter);
}
