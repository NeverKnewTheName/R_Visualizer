#include "SendMsgSingleWidget.h"
#include "ui_sendmsgsinglewidget.h"

SendMsgSingleWidget::SendMsgSingleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMsgSingleWidget)
{
    ui->setupUi(this);
}

SendMsgSingleWidget::~SendMsgSingleWidget()
{
    delete ui;
}
