#include "SystemOverviewWidget.h"
#include "ui_systemoverviewwidget.h"

#include "ISystemOverview.h"
#include "ISystemOverviewObject.h"

#include "SystemOverviewObject.h"
#include "SystemOverviewObjectStore.h"
#include "SysOverviewObjectDialog.h"

#include <QInputDialog>

SystemOverviewWidget::SystemOverviewWidget(
        ISystemOverview *systemOverview,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SystemOverviewWidget),
    systemOverview(systemOverview),
    sysOvrvScene(this)
{
    ui->setupUi(this);
    ui->sysOverviewGraphicsView->setScene(&sysOvrvScene);

    connect(
            ui->sysOverviewGraphicsView,
            &SystemOverviewGraphicsView::sgnl_RequestAddObject,
                [=](const QPointF &pos){
                        ISysOvrvObjPtr newObj(new SystemOverviewObject());
                        SysOverviewObjectDialog * objDiag =
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
                                obj->setPos(pos);
                                QString objectName = obj->getObjectName();
                                while(
                                      objectName.isEmpty() ||
                                      (objectName.compare("INVALID") == 0) ||
                                      !systemOverview->getObject(objectName).isNull()
                                      )
                                {
                                    //Object already exists!
                                    objectName = QInputDialog::getText(
                                                this,
                                                QString("Enter Name for Object"),
                                                QString("Object Name:"),
                                                QLineEdit::Normal,
                                                objectName
                                                );
                                    obj->setObjectName(objectName);
                                }
                                systemOverview
                                        ->addObject(
                                            obj
                                            );
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
                    systemOverview->removeObject(objName);
                }
            );

    connect(
            ui->sysOverviewGraphicsView,
            &SystemOverviewGraphicsView::sgnl_RequestEditObject,
                [=](const QString &objName){
                    ISysOvrvObjPtr obj = systemOverview->getObject(objName);
                    systemOverview->removeObject(obj);
                    SysOverviewObjectDialog * objDiag =
                            new SysOverviewObjectDialog(
                                obj,
                                this
                                );
                    connect(
                            objDiag,
                            &SysOverviewObjectDialog::sgnl_CommitObject,
                            [=](ISysOvrvObjPtr obj){
                                QString objectName = obj->getObjectName();
                                while(
                                      objectName.isEmpty() ||
                                      (objectName.compare("INVALID") == 0) ||
                                      !systemOverview->getObject(objectName).isNull()
                                      )
                                {
                                    //Object already exists!
                                    objectName = QInputDialog::getText(
                                                this,
                                                QString("Enter Name for Object"),
                                                QString("Object Name:"),
                                                QLineEdit::Normal,
                                                objectName
                                                );
                                    obj->setObjectName(objectName);
                                }
                                systemOverview
                                        ->addObject(
                                            obj
                                            );
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
                                ISysOvrvObjPtr originalObj =
                                        objDiag->getObject();
                                systemOverview
                                        ->addObject(
                                            originalObj
                                            );
                            }
                        );

                    objDiag->setAttribute(Qt::WA_DeleteOnClose);
                    objDiag->exec();
                }
            );

    connect(
            systemOverview,
            &ISystemOverview::sgnl_objectAdded,
            [=](ISysOvrvObjPtr obj){
                    sysOvrvScene.addItem(obj.data());
                }
            );
    connect(
            systemOverview,
            &ISystemOverview::sgnl_objectRemoved,
            [=](ISysOvrvObjPtr obj){
                    sysOvrvScene.removeItem(obj.data());
                }
            );
}

SystemOverviewWidget::~SystemOverviewWidget()
{
    systemOverview->clear();
    delete ui;
}
