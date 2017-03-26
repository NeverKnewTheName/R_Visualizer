#include "MessageConfigWidget.h"
#include "ui_messageconfigwidget.h"

MessageConfigWidget::MessageConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageConfigWidget)
{
    ui->setupUi(this);
}

MessageConfigWidget::~MessageConfigWidget()
{
    delete ui;
}

void MessageConfigWidget::appendMappingWidget(QWidget *mappingWidgetToAppend)
{
    ui->verticalLayout->addWidget(mappingWidgetToAppend);
}
