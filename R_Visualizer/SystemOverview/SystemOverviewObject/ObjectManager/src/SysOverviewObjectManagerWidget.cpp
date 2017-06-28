#include "SysOverviewObjectManagerWidget.h"
#include "ui_sysoverviewobjectmanagerwidget.h"

#include "ISysOverviewObjectManagerSubWidget.h"
#include "SysOverviewObjectShapeManagerWidget.h"
#include "SysOverviewObjectImageManagerWidget.h"

SysOverviewObjectManagerWidget::SysOverviewObjectManagerWidget(
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SysOverviewObjectManagerWidget),
    currentWidget(Q_NULLPTR)
{
    initWidget();
}

SysOverviewObjectManagerWidget::SysOverviewObjectManagerWidget(
        ISysOvrvObjPtr sysOvrvObj,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SysOverviewObjectManagerWidget),
    sysOvrvObj(sysOvrvObj),
    currentWidget(Q_NULLPTR)
{
    initWidget();
    setupWidget();
}

SysOverviewObjectManagerWidget::~SysOverviewObjectManagerWidget()
{
    delete ui;
}

void SysOverviewObjectManagerWidget::updateSysOverviewObject(
        ISysOvrvObjPtr sysOvrvObj
        )
{
    this->sysOvrvObj = sysOvrvObj;

    setupWidget();
    currentWidget->updateSysOverviewObject(sysOvrvObj);
}

void SysOverviewObjectManagerWidget::initWidget()
{
    ui->setupUi(this);

    QStringList objectTypes;
    objectTypes << QString("Shape");
    objectTypes << QString("Image");

    ui->objectTypeComboBox->addItems(objectTypes);
}

void SysOverviewObjectManagerWidget::setupWidget()
{
    const ISysOverviewObjectManager::ObjectType objType =
            sysOvrvObj->getShapeManager()->getType();
    ui->objectTypeComboBox->setCurrentIndex(
                static_cast<const int>(objType)
                );
}

void SysOverviewObjectManagerWidget::on_objectTypeComboBox_currentIndexChanged(int index)
{
    QLayout *oldLayout = ui->widgetHolder->layout();
    if(oldLayout != Q_NULLPTR)
    {
        if(currentWidget != Q_NULLPTR)
        {
            oldLayout->removeWidget(currentWidget);
            delete currentWidget;
        }
        delete oldLayout;
    }
    QVBoxLayout *newLayout = new QVBoxLayout();
    ISysOverviewObjectManagerSubWidget *newWidget;
    switch(static_cast<ISysOverviewObjectManager::ObjectType>(index))
    {
    case ISysOverviewObjectManager::ImageType:
        newWidget = new SysOverviewObjectImageManagerWidget(sysOvrvObj);
        break;
    case ISysOverviewObjectManager::ShapeType:
    default:
        newWidget = new SysOverviewObjectShapeManagerWidget(sysOvrvObj);
    }
    newLayout->addWidget(newWidget);
    currentWidget = newWidget;

    ui->widgetHolder->setLayout(newLayout);
}
