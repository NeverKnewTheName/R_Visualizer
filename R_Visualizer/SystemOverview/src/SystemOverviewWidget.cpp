#include "SystemOverviewWidget.h"
#include "ui_systemoverviewwidget.h"

#include "ISystemOverview.h"
#include "ISystemOverviewObject.h"

#include "SysOverviewObjectDialog.h"

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
                [=](const QPointF &pos){
                    SysOverviewObjectDialog *objDiag =
                            new SysOverviewObjectDialog(this);

                    objDiag->setAttribute(Qt::WA_DeleteOnClose);
                    objDiag->exec();
                }
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
                [=](){
                    SysOverviewObjectDialog *objDiag =
                            new SysOverviewObjectDialog(this);

                    objDiag->setAttribute(Qt::WA_DeleteOnClose);
                    objDiag->exec();
                }
            );
}

SystemOverviewWidget::~SystemOverviewWidget()
{
    delete ui;
}
