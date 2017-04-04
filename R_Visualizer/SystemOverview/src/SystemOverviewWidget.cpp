#include "SystemOverviewWidget.h"
#include "ui_systemoverviewwidget.h"

SystemOverviewWidget::SystemOverviewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemOverviewWidget)
{
    ui->setupUi(this);
}

SystemOverviewWidget::~SystemOverviewWidget()
{
    delete ui;
}
