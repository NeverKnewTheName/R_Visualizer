#include "SysOverviewObjectDialog.h"
#include "ui_sysoverviewobjectdialog.h"

#include "SysOverviewObjectShapeManager.h"

#include <QDebug>

SysOverviewObjectDialog::SysOverviewObjectDialog(
        ISysOvrvObjPtr sysOvrvObj,
        QWidget *parent
        ) :
    QDialog(parent),
    ui(new Ui::SysOverviewObjectDialog),
    scene(this),
    sysOvrvObj(sysOvrvObj)
{
    ui->setupUi(this);
    ui->objectPreviewGrahicsView->setScene(&scene);

    if(sysOvrvObj != Q_NULLPTR)
    {
        scene.addItem(sysOvrvObj.data());
    }

    ui->shapeComboBox->addItems(SysOverviewObjectShapeManager::listShapes());
    ui->shapeComboBox->setCurrentIndex(sysOvrvObj->getShapeManager()->getShape());
}

SysOverviewObjectDialog::~SysOverviewObjectDialog()
{
    delete ui;
    qDebug() << "SysOvrvObjDiag Destroyed!";
}

void SysOverviewObjectDialog::on_colorPickerBtn_clicked()
{

}

void SysOverviewObjectDialog::on_addObjectBtn_clicked()
{

}

void SysOverviewObjectDialog::on_removeObjectBtn_clicked()
{

}

void SysOverviewObjectDialog::on_editObjectBtn_clicked()
{

}

void SysOverviewObjectDialog::on_addLabelBtn_clicked()
{

}

void SysOverviewObjectDialog::on_removeLabelBtn_clicked()
{

}

void SysOverviewObjectDialog::on_addTriggerBtn_clicked()
{

}

void SysOverviewObjectDialog::on_removeTriggerBtn_clicked()
{

}

void SysOverviewObjectDialog::on_editTriggerBtn_clicked()
{

}

void SysOverviewObjectDialog::on_shapeComboBox_currentIndexChanged(int index)
{

}

void SysOverviewObjectDialog::on_transparencySpinBox_valueChanged(int arg1)
{

}

void SysOverviewObjectDialog::on_colorLE_editingFinished()
{

}

void SysOverviewObjectDialog::on_buttonBox_clicked(QAbstractButton *button)
{

}

void SysOverviewObjectDialog::on_nameLE_editingFinished()
{

}
