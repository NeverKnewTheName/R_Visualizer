#include "MessageFilterWidget.h"
#include "ui_messagefilterwidget.h"

MessageFilterWidget::MessageFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageFilterWidget)
{
    ui->setupUi(this);
}

MessageFilterWidget::~MessageFilterWidget()
{
    delete ui;
}
