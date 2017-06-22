#include "SysOverviewObjectShapeManagerWidget.h"
#include "ui_sysoverviewobjectshapemanagerwidget.h"

#include "SysOverviewObjectShapeManager.h"

SysOverviewObjectShapeManagerWidget::SysOverviewObjectShapeManagerWidget(
        ISysOvrvObjPtr sysOvrvObj,
        QWidget *parent
        ) :
    ISysOverviewObjectManagerSubWidget(parent),
    ui(new Ui::SysOverviewObjectShapeManagerWidget),
    sysOvrvObj(sysOvrvObj)
{
    ui->setupUi(this);
    ui->shapeComboBox->addItems(SysOverviewObjectShapeManager::listShapes());

    connect(
            ui->shapeComboBox,
            static_cast<void (QComboBox::*)(const int)>(&QComboBox::currentIndexChanged),
            [=](const int index){
                if(!this->sysOvrvObj.isNull())
                {
                    SysOvrvObjectShapeManagerPtr objShapeManager(
                                dynamic_cast<SysOverviewObjectShapeManager *>(
                                    this->sysOvrvObj->getShapeManager().release()
                                    )
                                );
                    if(objShapeManager.get() != Q_NULLPTR)
                    {
                        SysOvrvObjColorManagerPtr colorManager =
                                objShapeManager->getColorManager();

                        objShapeManager.reset(
                                    new SysOverviewObjectShapeManager(
                                        this->sysOvrvObj.data(),
                                        std::move(colorManager),
                                        static_cast<SysOverviewObjectShapeManager::SysOverviewObjectShape>(index)
                                        )
                                    );
                        this->sysOvrvObj->setShapeManager(std::move(objShapeManager));
                    }
                }
            }
    );
    setupWidget();
}

SysOverviewObjectShapeManagerWidget::~SysOverviewObjectShapeManagerWidget()
{
    delete ui;
}

void SysOverviewObjectShapeManagerWidget::setupWidget()
{
    if(!sysOvrvObj.isNull())
    {
        SysOvrvObjectShapeManagerPtr objShapeManager(
                    dynamic_cast<SysOverviewObjectShapeManager *>(
                        sysOvrvObj->getShapeManager().release()
                        )
                    );
        if(objShapeManager.get() != Q_NULLPTR)
        {
            const SysOverviewObjectShapeManager::SysOverviewObjectShape shape =
                    objShapeManager->getShape();
            ui->shapeComboBox->setCurrentIndex(
                        static_cast<const int>(shape)
                        );
            SysOvrvObjColorManagerPtr objColorManager(
                        objShapeManager->getColorManager()
                        );
            const QColor &objColor = objColorManager->getFillColor();
            ui->colorLE->setText(objColor.name());
            ui->colorLE->setStyleSheet(
                        QString("QLineEdit { background: %1; }")
                            .arg(objColor.name())
                        );
            ui->transparencySpinBox->setValue(static_cast<int>(objColor.alphaF()*100));
        }
    }
}

void SysOverviewObjectShapeManagerWidget::on_shapeComboBox_currentIndexChanged(int index)
{
//    SysOvrvObjectShapeManagerPtr objShapeManager(
//                dynamic_cast<SysOverviewObjectShapeManager *>(
//                    sysOvrvObj->getShapeManager().release()
//                    )
//                );
//    if(objShapeManager.get() != Q_NULLPTR)
//    {
//        SysOvrvObjColorManagerPtr colorManager =
//                objShapeManager->getColorManager();

//        objShapeManager.reset(
//                    new SysOverviewObjectShapeManager(
//                        sysOvrvObj.data(),
//                        std::move(colorManager),
//                        static_cast<SysOverviewObjectShapeManager::SysOverviewObjectShape>(index)
//                        )
//                    );
//        sysOvrvObj->setShapeManager(std::move(objShapeManager));
//    }
}

void SysOverviewObjectShapeManagerWidget::on_transparencySpinBox_valueChanged(int arg1)
{
    if(sysOvrvObj.isNull())
    {
        return;
    }

    SysOvrvObjectShapeManagerPtr objShapeManager(
                dynamic_cast<SysOverviewObjectShapeManager *>(
                    sysOvrvObj->getShapeManager().release()
                    )
                );
    if(objShapeManager.get() != Q_NULLPTR)
    {
        SysOvrvObjColorManagerPtr objColorManager(
                    objShapeManager->getColorManager()
                    );
        QColor objColor = objColorManager->getFillColor();
        objColor.setAlphaF(arg1/100.0);
        objColorManager->setFillColor(objColor);
        objShapeManager->setColorManager(std::move(objColorManager));
        sysOvrvObj->setShapeManager(std::move(objShapeManager));
    }
}

void SysOverviewObjectShapeManagerWidget::on_colorLE_editingFinished()
{
    QColor colorToSet(ui->colorLE->text());
    if(colorToSet.isValid())
    {
        colorToSet.setAlphaF(ui->transparencySpinBox->value()/100.0);
        ui->colorLE->setStyleSheet(
                    QString("QLineEdit { background: %1; }")
                        .arg(colorToSet.name())
                    );
        if(!sysOvrvObj.isNull())
        {
            SysOvrvObjectShapeManagerPtr objShapeManager(
                        dynamic_cast<SysOverviewObjectShapeManager *>(
                            sysOvrvObj->getShapeManager().release()
                            )
                        );
            if(objShapeManager.get() != Q_NULLPTR)
            {
                SysOvrvObjColorManagerPtr objColorManager(
                            objShapeManager->getColorManager().release()
                            );
                objColorManager->setFillColor(colorToSet);
                objShapeManager->setColorManager(std::move(objColorManager));
                sysOvrvObj->setShapeManager(std::move(objShapeManager));
            }
        }
    }
}


void SysOverviewObjectShapeManagerWidget::updateSysOverviewObject(ISysOvrvObjPtr sysOvrvObj)
{
    this->sysOvrvObj = sysOvrvObj;
    setupWidget();
}
