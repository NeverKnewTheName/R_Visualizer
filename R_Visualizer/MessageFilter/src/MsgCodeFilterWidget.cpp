#include "MsgCodeFilterWidget.h"
#include "ui_msgcodefilterwidget.h"

MsgCodeFilterWidget::MsgCodeFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgCodeFilterWidget)
{
    ui->setupUi(this);
}

MsgCodeFilterWidget::~MsgCodeFilterWidget()
{
    delete ui;
}
