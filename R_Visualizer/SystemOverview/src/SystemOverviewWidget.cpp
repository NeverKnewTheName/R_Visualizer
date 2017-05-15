#include "SystemOverviewWidget.h"
#include "ui_systemoverviewwidget.h"

SystemOverviewWidget::SystemOverviewWidget(
        ISystemOverview *systemOverview,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SystemOverviewWidget),
    systemOverview(systemOverview)
{
    ui->setupUi(this);
}

SystemOverviewWidget::~SystemOverviewWidget()
{
    delete ui;
}
