#include "SendMessagesWidget.h"
#include "ui_sendmessageswidget.h"

#include "ISendMessages.h"

SendMessagesWidget::SendMessagesWidget(
        ISendMessages *sendMessages,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SendMessagesWidget),
    sendMessages(sendMessages)
{
    ui->setupUi(this);
}

SendMessagesWidget::~SendMessagesWidget()
{
    delete ui;
}

void SendMessagesWidget::addSendMsgSingleWidget(
        QWidget *sendMsgWidget
    )
{
    ui->verticalLayout->addWidget(sendMsgWidget);
}

void SendMessagesWidget::connectSendMessages()
{
}
