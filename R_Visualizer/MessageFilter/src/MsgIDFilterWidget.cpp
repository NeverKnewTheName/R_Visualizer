#include "MsgIDFilterWidget.h"
#include "ui_msgidfilterwidget.h"

MsgIDFilterWidget::MsgIDFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgIDFilterWidget)
{
    ui->setupUi(this);
}

MsgIDFilterWidget::~MsgIDFilterWidget()
{
    delete ui;
}
