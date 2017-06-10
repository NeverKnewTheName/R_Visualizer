#include "SystemOverviewWidget.h"
#include "ui_systemoverviewwidget.h"

#include "ISystemOverview.h"
#include "ISystemOverviewObject.h"

#include "SystemOverviewObject.h"
#include "SystemOverviewObjectStore.h"
#include "SysOverviewObjectDialog.h"

SystemOverviewWidget::SystemOverviewWidget(
        ISystemOverview *systemOverview,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SystemOverviewWidget),
    systemOverview(systemOverview),
    objStore(new SystemOverviewObjectStore(this)),
    sysOvrvScene(this)
{
    ui->setupUi(this);
    ui->sysOverviewGraphicsView->setScene(&sysOvrvScene);

    connect(
            ui->sysOverviewGraphicsView,
            &SystemOverviewGraphicsView::sgnl_RequestAddObject,
                [=](const QPointF &pos){
                    ISysOvrvObjPtr newObj(new SystemOverviewObject());
                    SysOverviewObjectDialog *objDiag =
                            new SysOverviewObjectDialog(
                                newObj,
                                this
                                );

                    connect(
                            objDiag,
                            &SysOverviewObjectDialog::accepted,
                            [=](){
                                qDebug() << "Add -- accepted";
                            }
                        );
                    connect(
                            objDiag,
                            &SysOverviewObjectDialog::sgnl_CommitObject,
                            [=](ISysOvrvObjPtr obj){
                                addObject(std::move(obj));
                            }
                        );
                    connect(
                            objDiag,
                            &SysOverviewObjectDialog::rejected,
                            [=](){
                                qDebug() << "Add -- rejected";
                            }
                        );

                    objDiag->setAttribute(Qt::WA_DeleteOnClose);
                    objDiag->exec();
                }
            );
    connect(
            ui->sysOverviewGraphicsView,
            &SystemOverviewGraphicsView::sgnl_RequestRemoveObject,
                [=](const QString &objName){
                    ISysOvrvObjPtr obj = objStore->getObj(objName);
                    if(obj == Q_NULLPTR)
                    {
                        return;
                    }
                    objStore->removeObj(objName);
                }
            );
    connect(
            ui->sysOverviewGraphicsView,
            &SystemOverviewGraphicsView::sgnl_RequestEditObject,
                [=](const QString &objName){
                    ISysOvrvObjPtr obj = objStore->getObj(objName);
                    objStore->removeObj(objName);
                    SysOverviewObjectDialog *objDiag =
                            new SysOverviewObjectDialog(
                                obj,
                                this
                                );
                    connect(
                            objDiag,
                            &SysOverviewObjectDialog::sgnl_CommitObject,
                            [=](ISysOvrvObjPtr obj){
                                addObject(std::move(obj));
                            }
                        );
                    connect(
                            objDiag,
                            &SysOverviewObjectDialog::accepted,
                            [=](){
                                qDebug() << "Edit -- accepted";
                            }
                        );
                    connect(
                            objDiag,
                            &SysOverviewObjectDialog::rejected,
                            [=](){
                                qDebug() << "Edit -- rejected";
                                addObject(obj);
                            }
                        );

                    objDiag->setAttribute(Qt::WA_DeleteOnClose);
                    objDiag->exec();
                }
            );

    connect(
            objStore,
            &ISystemOverviewObjectStore::sgnl_objectAdded,
            [=](ISysOvrvObjPtr obj){
                    sysOvrvScene.addItem(obj.data());
                }
            );
    connect(
            objStore,
            &ISystemOverviewObjectStore::sgnl_objectRemoved,
            [=](ISysOvrvObjPtr obj){
                    sysOvrvScene.removeItem(obj.data());
                }
            );
}

SystemOverviewWidget::~SystemOverviewWidget()
{
    objStore->clear();
    delete ui;
}

void SystemOverviewWidget::addObject(ISysOvrvObjPtr objectToAdd)
{
    objStore->addSystemOverviewObject(std::move(objectToAdd));
}
