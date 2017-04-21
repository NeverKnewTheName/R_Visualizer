#include "MsgTimestampFilterWidget.h"
#include "ui_msgtimestampfilterwidget.h"

MsgTimestampFilterWidget::MsgTimestampFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgTimestampFilterWidget)
{
    ui->setupUi(this);
}

MsgTimestampFilterWidget::~MsgTimestampFilterWidget()
{
    delete ui;
}
