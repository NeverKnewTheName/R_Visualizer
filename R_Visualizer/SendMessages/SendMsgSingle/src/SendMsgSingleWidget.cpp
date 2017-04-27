#include "SendMsgSingleWidget.h"
#include "ui_sendmsgsinglewidget.h"

#include "ISendMsgSingle.h"

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
