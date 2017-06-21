#include "SysOverviewObjectImageManagerWidget.h"
#include "ui_sysoverviewobjectimagemanagerwidget.h"

#include "ISysOverviewObjectManager.h"
#include "SysOverviewObjectImageManager.h"

#include <QFileDialog>

SysOverviewObjectImageManagerWidget::SysOverviewObjectImageManagerWidget(
        ISysOvrvObjPtr sysOvrvObj,
        QWidget *parent
        ) :
    ISysOverviewObjectManagerSubWidget(parent),
    ui(new Ui::SysOverviewObjectImageManagerWidget),
    sysOvrvObj(sysOvrvObj)
{
    ui->setupUi(this);
}

SysOverviewObjectImageManagerWidget::~SysOverviewObjectImageManagerWidget()
{
    delete ui;
}

void SysOverviewObjectImageManagerWidget::on_imagePickerBtn_clicked()
{
    const QString &filePath = QFileDialog::getOpenFileName(
            this,
            QString("Open Image"),
            QString(),
            "Images (*.bmp *.jpg *.png)"
            );
    ui->imagePathLineEdit->setText(filePath);
    ui->imageLabel->setPixmap(QPixmap(filePath));
}

void SysOverviewObjectImageManagerWidget::updateSysOverviewObject(ISysOvrvObjPtr sysOvrvObj)
{
    this->sysOvrvObj = sysOvrvObj;
}

void SysOverviewObjectImageManagerWidget::on_applyBtn_clicked()
{
    const QPixmap objPixmap(ui->imagePathLineEdit->text());

    if(objPixmap.isNull())
    {
        return;
    }

    if(sysOvrvObj != Q_NULLPTR)
    {
        SysOvrvObjectManagerPtr objManager =
                sysOvrvObj->getShapeManager();
        const ISysOverviewObjectManager::ObjectType managerType =
                objManager->getType();
        SysOverviewObjectImageManager *imageManager;

        switch(managerType)
        {
        case ISysOverviewObjectManager::ImageType:
        {
            imageManager =
                    dynamic_cast<SysOverviewObjectImageManager*>(
                        objManager.release()
                        );
            imageManager->setImage(objPixmap);
        }
            break;
        case ISysOverviewObjectManager::ShapeType:
        default:
            imageManager =
                    new SysOverviewObjectImageManager(
                        sysOvrvObj.data(),
                        objPixmap
                        );
            break;
        }

        sysOvrvObj->setShapeManager(std::move(SysOvrvObjectManagerPtr(imageManager)));
    }
}

void SysOverviewObjectImageManagerWidget::on_imagePathLineEdit_editingFinished()
{
    QPixmap objPixmap(ui->imagePathLineEdit->text());
    ui->imageLabel->setPixmap(objPixmap);
}
