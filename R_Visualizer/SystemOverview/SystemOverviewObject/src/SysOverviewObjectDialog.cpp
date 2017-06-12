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
    sysOvrvObjSave(sysOvrvObj->clone())
{
    ui->setupUi(this);
    ui->objectPreviewGrahicsView->setScene(&scene);

    if(!sysOvrvObj.isNull())
    {
        setupSysOvrvObj(sysOvrvObj);

        scene.addItem(sysOvrvObj.data());
        setupDialog();
    }
    setupButtons();

    ui->shapeComboBox->addItems(SysOverviewObjectShapeManager::listShapes());
    /* ui->shapeComboBox->setCurrentIndex(sysOvrvObj->getShapeManager()->getShape()); */

    connect(
                &scene,
                &QGraphicsScene::focusItemChanged,
                [=](){
                    qDebug() << "FOCus changed";
                }
                );
    connect(
                &scene,
                &QGraphicsScene::selectionChanged,
                [=](){
                    qDebug() << "Selection changed";
                    QList<QGraphicsItem *> selectedItems =
                            scene.selectedItems();
                    setupButtons();
                    selectedObj.clear();
                    selectedTextLabel.clear();

                    if(selectedItems.size() == 1)
                    {
                        //Valid only if one item is selected!
                        ISystemOverviewObject *sysOvrvObj =
                                dynamic_cast<ISystemOverviewObject*>(
                                    selectedItems.first()
                                    );
                        if(sysOvrvObj != Q_NULLPTR)
                        {
                            if(sysOvrvObj == this->sysOvrvObj.data())
                            {
                                //Object is current object
                                selectedObj = this->sysOvrvObj;
                                //if object is parent
                                ui->addLabelBtn->setEnabled(true);
                            }
                            else
                            {
                                //Object is a child of current object
                                selectedObj =
                                        this->sysOvrvObj->convertObjectPointer(
                                            sysOvrvObj
                                            );
                                if(selectedObj.isNull())
                                {
                                    return;
                                }
                                //if object is child
                                ui->removeObjectBtn->setEnabled(true);
                                ui->editObjectBtn->setEnabled(true);
                            }

                            ui->addTriggerBtn->setEnabled(true);
                            ui->removeTriggerBtn->setEnabled(true);
                            ui->editTriggerBtn->setEnabled(true);

                            qDebug() << selectedObj->getObjectName();
                        }
                        else
                        {
                            SysOverviewTextLabel *textLabel =
                                    dynamic_cast<SysOverviewTextLabel *>(
                                        selectedItems.first()
                                        );
                            if(textLabel != Q_NULLPTR)
                            {
                                selectedTextLabel =
                                        this->sysOvrvObj
                                            ->convertLabelPointer(textLabel);
                                if(!selectedTextLabel.isNull())
                                {
                                    ui->removeLabelBtn->setEnabled(true);
                                }
                            }
                        }
                    }
                }
            );
}

SysOverviewObjectDialog::~SysOverviewObjectDialog()
{
    if(!sysOvrvObj.isNull())
    {
        scene.removeItem(sysOvrvObj.data());
    }
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

void SysOverviewObjectDialog::setupButtons()
{
    ui->removeObjectBtn->setDisabled(true);
    ui->editObjectBtn->setDisabled(true);
    ui->addLabelBtn->setDisabled(true);
    ui->removeLabelBtn->setDisabled(true);
    ui->addTriggerBtn->setDisabled(true);
    ui->removeTriggerBtn->setDisabled(true);
    ui->editTriggerBtn->setDisabled(true);
}

void SysOverviewObjectDialog::on_colorPickerBtn_clicked()
{

}

void SysOverviewObjectDialog::on_addObjectBtn_clicked()
{
    scene.clearSelection();
    scene.clearFocus();
    ISysOvrvObjPtr newObj(new SystemOverviewObject());
    SysOverviewObjectDialog *addDialog =
            new SysOverviewObjectDialog(
                newObj,
                this
                );

    connect(
            addDialog,
            &SysOverviewObjectDialog::sgnl_CommitObject,
            [=](ISysOvrvObjPtr obj){
                setupChildSysOvrvObj(obj);
                sysOvrvObj->addChildObject(obj);
            }
        );
    addDialog->setAttribute(Qt::WA_DeleteOnClose);
    addDialog->exec();
}

void SysOverviewObjectDialog::on_removeObjectBtn_clicked()
{
    ISysOvrvObjPtr objToRemove = selectedObj;
    if(objToRemove.isNull() || (objToRemove == sysOvrvObj))
    {
        return;
    }
    scene.clearSelection();
    scene.clearFocus();
    sysOvrvObj->removeChildObject(objToRemove);
    selectedObj.clear();
}

void SysOverviewObjectDialog::on_editObjectBtn_clicked()
{
    ISysOvrvObjPtr objToEdit = selectedObj;
    scene.clearSelection();
    scene.clearFocus();
    selectedObj.clear();
    if(objToEdit.isNull() || (objToEdit == sysOvrvObj))
    {
        return;
    }
    sysOvrvObj->removeChildObject(objToEdit);

    SysOverviewObjectDialog *addDialog =
            new SysOverviewObjectDialog(
                objToEdit,
                this
                );
    connect(
            addDialog,
            &SysOverviewObjectDialog::sgnl_CommitObject,
            [=](ISysOvrvObjPtr obj){
                setupChildSysOvrvObj(obj);
                sysOvrvObj->addChildObject(obj);
            }
        );
    connect(
            addDialog,
            &SysOverviewObjectDialog::rejected,
            [=](){
                setupChildSysOvrvObj(objToEdit);
                sysOvrvObj->addChildObject(objToEdit);
            }
        );
    addDialog->setAttribute(Qt::WA_DeleteOnClose);
    addDialog->exec();
}

void SysOverviewObjectDialog::on_addLabelBtn_clicked()
{
    ISysOvrvObjPtr objToEdit = selectedObj;
    scene.clearSelection();
    scene.clearFocus();
    selectedObj.clear();
    if(objToEdit.isNull() || (objToEdit != sysOvrvObj))
    {
        return;
    }
    SysOvrvTextLabelPtr newLabel(
                new SysOverviewTextLabel(
                    QString("PlaceHolder"),
                    sysOvrvObj.data()
                    )
                );
    objToEdit->addLabel(newLabel);
    newLabel->setPos(-20,-20);
    newLabel->setEditable(true);
    newLabel->textEdit(this);
}

void SysOverviewObjectDialog::on_removeLabelBtn_clicked()
{
    if(selectedTextLabel.isNull())
    {
        return;
    }

    SysOvrvTextLabelPtr textLabel = selectedTextLabel;

    selectedTextLabel.clear();
    scene.clearSelection();
    scene.clearFocus();

    sysOvrvObj->removeLabel(textLabel);
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
    SysOvrvObjectShapeManagerPtr objShapeManager(
                dynamic_cast<SysOverviewObjectShapeManager *>(
                    sysOvrvObj->getShapeManager().release()
                    )
                );
    if(objShapeManager.get() != Q_NULLPTR)
    {
        SysOvrvObjColorManagerPtr colorManager =
                objShapeManager->getColorManager();

        objShapeManager.reset(
                    new SysOverviewObjectShapeManager(
                        sysOvrvObj.data(),
                        std::move(colorManager),
                        static_cast<SysOverviewObjectShapeManager::SysOverviewObjectShape>(index)
                        )
                    );
        sysOvrvObj->setShapeManager(std::move(objShapeManager));
    }
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

void SysOverviewObjectDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    scene.clearSelection();
    scene.clearFocus();
    switch(ui->buttonBox->buttonRole(button))
    {
    case QDialogButtonBox::AcceptRole:
        switch(ui->buttonBox->standardButton(button))
        {
        case QDialogButtonBox::Ok:
            if(!sysOvrvObj.isNull())
            {
                scene.removeItem(sysOvrvObj.data());
                prepareSysOvrvObjForCommit(sysOvrvObj);
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
            prepareSysOvrvObjForCommit(sysOvrvObj);
            scene.removeItem(sysOvrvObj.data());
            break;
        }
        break;
    case QDialogButtonBox::ResetRole:
        selectedObj.clear();
        selectedTextLabel.clear();
        scene.removeItem(sysOvrvObj.data());
        sysOvrvObj.reset(sysOvrvObjSave->clone());
        scene.addItem(sysOvrvObj.data());
        setupDialog();
        setupSysOvrvObj(sysOvrvObj);
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

void SysOverviewObjectDialog::setupSysOvrvObj(ISysOvrvObjPtr obj)
{
    QVector<SysOvrvTextLabelPtr> textLabels =
            obj->getLabels();
    for( SysOvrvTextLabelPtr label : textLabels)
    {
        label->setEditable(true);
    }

    obj->enableResizing(true);
    obj->enableEditing(true);
    obj->enableMoving(true);
    QVector<ISysOvrvObjPtr> directChildren =
            obj->getChildObjects();
    for(ISysOvrvObjPtr directChild : directChildren)
    {
        directChild->enableResizing(true);
        directChild->enableMoving(true);
        directChild->enableEditing(true);
    }
}

void SysOverviewObjectDialog::setupChildSysOvrvObj(ISysOvrvObjPtr obj)
{
    QVector<SysOvrvTextLabelPtr> textLabels =
            obj->getLabels();
    for(SysOvrvTextLabelPtr label : textLabels)
    {
        label->setEditable(false);
    }
    obj->enableResizing(true);
    obj->enableEditing(true);
    obj->enableMoving(true);
    obj->enableChildrenEditing(false);
    obj->enableChildrenMoving(false);
    obj->enableChildrenResizing(false);
}

void SysOverviewObjectDialog::prepareSysOvrvObjForCommit(ISysOvrvObjPtr obj)
{
    QVector<SysOvrvTextLabelPtr> textLabels =
            obj->getLabels();
    for(SysOvrvTextLabelPtr label : textLabels)
    {
        label->setEditable(false);
    }
    obj->enableResizing(false);
    obj->enableEditing(false);
    obj->enableMoving(true);
    obj->enableResizing(false);
    obj->enableChildrenEditing(false);
    obj->enableChildrenMoving(false);
    obj->enableChildrenResizing(false);
}
