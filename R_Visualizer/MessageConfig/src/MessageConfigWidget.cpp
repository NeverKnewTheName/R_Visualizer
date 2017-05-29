#include "MessageConfigWidget.h"
#include "ui_messageconfigwidget.h"

#include <QVBoxLayout>

MessageConfigWidget::MessageConfigWidget(
        IMessageConfig *msgConfig,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MessageConfigWidget),
    msgConfig(msgConfig)
{
    ui->setupUi(this);
}

MessageConfigWidget::~MessageConfigWidget()
{
    delete ui;
}

void MessageConfigWidget::appendMappingManagerWidget(QWidget *mappingWidgetToAppend)
{
    ui->verticalLayout->addWidget(mappingWidgetToAppend);
}
