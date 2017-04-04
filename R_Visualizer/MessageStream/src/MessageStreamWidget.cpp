#include "MessageStreamWidget.h"
#include "ui_messagestreamwidget.h"

MessageStreamWidget::MessageStreamWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageStreamWidget)
{
    ui->setupUi(this);
}

MessageStreamWidget::~MessageStreamWidget()
{
    delete ui;
}
