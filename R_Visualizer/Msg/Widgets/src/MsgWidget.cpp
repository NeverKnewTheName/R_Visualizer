#include "MsgWidget.h"
#include "ui_msgwidget.h"

#include <QTimer>

MsgWidget::MsgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgWidget),
    msgIDMappingManager(Q_NULLPTR),
    msgCodeMappingManager(Q_NULLPTR)
{
    ui->setupUi(this);
    setTabOrder(ui->msgCodeWidget,ui->msgDataWidget);
    setTabOrder(ui->msgIDWidget,ui->msgCodeWidget);

    QTimer::singleShot(0,ui->msgIDWidget,SLOT(setFocus()));
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

void MsgWidget::setMsg(const IMsg &msgToSet)
{
    ui->msgIDWidget->setMsgID(msgToSet.getMsgID());
    ui->msgCodeWidget->setMsgCode(msgToSet.getMsgCode());
    ui->msgDataWidget->setMsgData(msgToSet.getMsgData());
}

void MsgWidget::setMsgIDMapping(IMsgIDMappingManager *msgIDMappingManager)
{
    ui->msgIDWidget->setMappingManager(msgIDMappingManager);
}

void MsgWidget::setMsgIDCompleter(QCompleter *msgIDCompleter)
{
    msgIDCompleter->setParent(ui->msgIDWidget);
    ui->msgIDWidget->setCompleter(msgIDCompleter);
}

void MsgWidget::setMsgCodeMapping(IMsgCodeMappingManager *msgCodeMappingManager)
{
    ui->msgCodeWidget->setMappingManager(msgCodeMappingManager);
}

void MsgWidget::setMsgCodeCompleter(QCompleter *msgCodeCompleter)
{
    msgCodeCompleter->setParent(ui->msgCodeWidget);
    ui->msgCodeWidget->setCompleter(msgCodeCompleter);
}
