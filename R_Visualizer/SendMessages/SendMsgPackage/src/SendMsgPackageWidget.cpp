#include "SendMsgPackageWidget.h"
#include "ui_sendmsgpackagewidget.h"

SendMsgPackageWidget::SendMsgPackageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMsgPackageWidget)
{
    ui->setupUi(this);
}

SendMsgPackageWidget::~SendMsgPackageWidget()
{
    delete ui;
}
