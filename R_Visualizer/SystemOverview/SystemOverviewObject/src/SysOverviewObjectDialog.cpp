#include "SysOverviewObjectDialog.h"
#include "ui_sysoverviewobjectdialog.h"

#include "SysOverviewObjectShapeManager.h"
#include "SysOverviewObjectResizeManager.h"

#include <QDebug>

SysOverviewObjectDialog::SysOverviewObjectDialog(
        ISysOvrvObjPtr sysOvrvObj,
        QWidget *parent
        ) :
    QDialog(parent),
    ui(new Ui::SysOverviewObjectDialog),
    scene(this),
    sysOvrvObj(sysOvrvObj),
    sysOvrvObjSave(new SystemOverviewObject())
{
    ui->setupUi(this);
    ui->objectPreviewGrahicsView->setScene(&scene);

    if(!sysOvrvObj.isNull())
    {
        sysOvrvObjSave->setObjectName(sysOvrvObj->getObjectName());
        sysOvrvObjSave->setColor(sysOvrvObj->getColor());
        sysOvrvObjSave->setShapeManager(std::move(sysOvrvObj->getShapeManager()));
        sysOvrvObjSave->setResizeManager(std::move(sysOvrvObj->getResizeManager()));

        scene.addItem(sysOvrvObj.data());
        setupDialog();
    }

    ui->shapeComboBox->addItems(SysOverviewObjectShapeManager::listShapes());
    /* ui->shapeComboBox->setCurrentIndex(sysOvrvObj->getShapeManager()->getShape()); */
}

SysOverviewObjectDialog::~SysOverviewObjectDialog()
{
    scene.removeItem(sysOvrvObj.data());
    delete ui;
    qDebug() << "SysOvrvObjDiag Destroyed!";
}

void SysOverviewObjectDialog::setupDialog()
{
    ui->nameLE->setText(sysOvrvObj->getObjectName());
    SysOvrvObjectShapeManagerPtr objShapeManager(
                dynamic_cast<SysOverviewObjectShapeManager *>(
                    sysOvrvObj->getShapeManager().release()
                    )
                );
    if(objShapeManager.get() != Q_NULLPTR)
    {
        const QColor &objColor = objShapeManager->getColor();
        ui->colorLE->setText(objColor.name());
        ui->transparencySpinBox->setValue(static_cast<int>(objColor.alphaF()*100));
    }
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
        QColor objColor = objShapeManager->getColor();
        objColor.setAlphaF(arg1/100.0);
        objShapeManager->setColor(objColor);
        sysOvrvObj->setShapeManager(std::move(objShapeManager));
    }
}

void SysOverviewObjectDialog::on_colorLE_editingFinished()
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
                objShapeManager->setColor(colorToSet);
                sysOvrvObj->setShapeManager(std::move(objShapeManager));
            }
        }
    }
}

void SysOverviewObjectDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch(ui->buttonBox->buttonRole(button))
    {
    case QDialogButtonBox::AcceptRole:
        switch(ui->buttonBox->standardButton(button))
        {
        case QDialogButtonBox::Ok:
            if(!sysOvrvObj.isNull())
            {
                scene.removeItem(sysOvrvObj.data());
                emit sgnl_CommitObject(std::move(this->sysOvrvObj));
            }
            break;
        case QDialogButtonBox::Save:
            break;
        case QDialogButtonBox::Open:
            break;
        }
        break;
    case QDialogButtonBox::RejectRole:
        switch(ui->buttonBox->standardButton(button))
        {
        case QDialogButtonBox::Abort:
            scene.removeItem(sysOvrvObj.data());
            break;
        }
        break;
    case QDialogButtonBox::ResetRole:
        sysOvrvObj->setObjectName(sysOvrvObjSave->getObjectName());
        sysOvrvObj->setShapeManager(std::move(sysOvrvObjSave->getShapeManager()));
        sysOvrvObj->setResizeManager(std::move(sysOvrvObjSave->getResizeManager()));
        setupDialog();
        break;
    }
}

void SysOverviewObjectDialog::on_nameLE_editingFinished()
{
    if(!sysOvrvObj.isNull())
    {
        this->sysOvrvObj->setObjectName(ui->nameLE->text());
    }
}

void SysOverviewObjectDialog::on_buttonBox_rejected()
{

}
