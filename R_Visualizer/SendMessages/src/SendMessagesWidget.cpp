#include "SendMessagesWidget.h"
#include "ui_sendmessageswidget.h"

SendMessagesWidget::SendMessagesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMessagesWidget)
{
    ui->setupUi(this);
}

SendMessagesWidget::~SendMessagesWidget()
{
    delete ui;
}
