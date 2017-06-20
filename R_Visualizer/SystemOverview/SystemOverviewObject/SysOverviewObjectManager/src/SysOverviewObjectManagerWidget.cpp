#include "SysOverviewObjectManagerWidget.h"
#include "ui_sysoverviewobjectmanagerwidget.h"

#include "SysOverviewObjectShapeManagerWidget.h"

SysOverviewObjectManagerWidget::SysOverviewObjectManagerWidget(
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SysOverviewObjectManagerWidget)
{
    ui->setupUi(this);

    QStringList objectTypes;
    objectTypes << QString("Shape");
    objectTypes << QString("Image");

    ui->objectTypeComboBox->addItems(objectTypes);
}

SysOverviewObjectManagerWidget::SysOverviewObjectManagerWidget(
        ISysOvrvObjPtr sysOvrvObj,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SysOverviewObjectManagerWidget),
    sysOvrvObj(sysOvrvObj)
{
    ui->setupUi(this);
    QStringList objectTypes;
    objectTypes << QString("Shape");
    objectTypes << QString("Image");

    ui->objectTypeComboBox->addItems(objectTypes);

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
    QObjectList widgetList =
        ui->widgetHolder->layout()->children();

    if(!widgetList.isEmpty())
    {
        ISysOverviewObjectManagerSubWidget *childWidget =
                dynamic_cast<ISysOverviewObjectManagerSubWidget*>(
                    widgetList.first()
                    );
        childWidget->updateSysOverviewObject(sysOvrvObj);
    }
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
    static QWidget *oldWidget = Q_NULLPTR;
    QLayout *oldLayout = ui->widgetHolder->layout();
    if(oldLayout != Q_NULLPTR)
    {
        if(oldWidget != Q_NULLPTR)
        {
            oldLayout->removeWidget(oldWidget);
            delete oldWidget;
        }
        delete oldLayout;
    }
    QVBoxLayout *newLayout = new QVBoxLayout();
    QWidget *newWidget;
    switch(index)
    {
    default:
        newWidget = new SysOverviewObjectShapeManagerWidget(sysOvrvObj);
    }
    newLayout->addWidget(newWidget);
    oldWidget = newWidget;

    ui->widgetHolder->setLayout(newLayout);
}
