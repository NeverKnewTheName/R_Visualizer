#include "SystemOverviewWidget.h"
#include "ui_systemoverviewwidget.h"

#include "ISystemOverview.h"
#include "ISystemOverviewObject.h"

SystemOverviewWidget::SystemOverviewWidget(
        ISystemOverview *systemOverview,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SystemOverviewWidget),
    systemOverview(systemOverview)
{
    ui->setupUi(this);
    connect(
            ui->sysOverviewGraphicsView,
            &SystemOverviewGraphicsView::sgnl_RequestAddObject,
            systemOverview,
            &ISystemOverview::slt_RequestAddObject
            );
    connect(
            ui->sysOverviewGraphicsView,
            &SystemOverviewGraphicsView::sgnl_RequestRemoveObject,
            systemOverview,
            &ISystemOverview::slt_RequestRemoveObject
            );
    connect(
            ui->sysOverviewGraphicsView,
            &SystemOverviewGraphicsView::sgnl_RequestEditObject,
            systemOverview,
            &ISystemOverview::slt_RequestEditObject
            );
}

SystemOverviewWidget::~SystemOverviewWidget()
{
    delete ui;
}
