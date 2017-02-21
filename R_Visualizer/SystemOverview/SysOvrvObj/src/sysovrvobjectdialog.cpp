#include "sysovrvobjectdialog.h"
#include "ui_sysovrvobjectdialog.h"

#include "sysovrvobjtriggerdialog.h"
#include "triggerablesysovrvobj.h"

#include "squaresysovrvobject.h"
#include "rectsysovrvobject.h"
#include "circlesysovrvobject.h"
#include "ellipsesysovrvobject.h"
#include "trianglesysovrvobject.h"
#include "imagesysovrvobject.h"

#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QDebug>

SysOvrvObjectDialog::SysOvrvObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjectDialog),
    m_curSysOvrvObject(new RectSysOvrvObject()),
    m_focusedItem(Q_NULLPTR),
    updateExisting(false)
{
    m_jsonObjSave = m_curSysOvrvObject->parseToJson();
    ui->setupUi(this);
    this->setupDialog();
    m_curSysOvrvObject->enableEdit(true);
}

SysOvrvObjectDialog::SysOvrvObjectDialog(SysOvrvObject *object, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjectDialog),
    m_curSysOvrvObject(object),
    m_focusedItem(Q_NULLPTR),
    updateExisting(true)
{
    m_jsonObjSave = m_curSysOvrvObject->parseToJson();
    ui->setupUi(this);
    this->setupDialog();
    m_curSysOvrvObject->enableEdit(true);
    QVector<SysOvrvObject *> children = m_curSysOvrvObject->getChildSysOvrvObjects();
    for(auto childObj : children)
    {
        childObj->setAsChild(false);
        childObj->enableEdit(true);
    }
}

SysOvrvObjectDialog::~SysOvrvObjectDialog()
{
    qDebug() << __PRETTY_FUNCTION__;
    delete ui;
}

void SysOvrvObjectDialog::on_addPropertyBtn_clicked()
{
    SysOvrvObjectDialog addSysOvrvObjectDialog(this);
    connect(&addSysOvrvObjectDialog, &SysOvrvObjectDialog::sgnl_commit, this, &SysOvrvObjectDialog::slt_addObjectToObject);
    addSysOvrvObjectDialog.exec();
}

void SysOvrvObjectDialog::on_rmvPropertyBtn_clicked()
{
    if((m_focusedItem == Q_NULLPTR) || (m_focusedItem == m_curSysOvrvObject))
    {
        return;
    }

    qDebug() << "Focused item: " << m_focusedItem->getObjName();

    delete m_focusedItem;
    m_focusedItem = Q_NULLPTR;
}

void SysOvrvObjectDialog::on_edtPropertyBtn_clicked()
{
    if((m_focusedItem == Q_NULLPTR) || (m_focusedItem == m_curSysOvrvObject))
    {
        return;
    }

    qDebug() << "Focused item: " << m_focusedItem->getObjName();

    SysOvrvObjectDialog addSysOvrvObjectDialog(m_focusedItem);
    connect(&addSysOvrvObjectDialog, &SysOvrvObjectDialog::sgnl_commit, this, &SysOvrvObjectDialog::slt_addObjectToObject);
    addSysOvrvObjectDialog.exec();
}

void SysOvrvObjectDialog::on_edtTriggerBtn_clicked()
{
    if(m_focusedItem == Q_NULLPTR)
    {
        return;
    }

    //DO SOMETHING HERE! TRIGGER ALL THE SysOvrvObjs!
    SysOvrvObjTriggerDialog triggerDiag(m_focusedItem, this);

    triggerDiag.exec();
}

void SysOvrvObjectDialog::slt_objectShapeChanged(int index)
{
    SysOvrvObject *curObjSave = m_curSysOvrvObject;

    SysOvrvScene.removeItem(m_curSysOvrvObject);

    switch(static_cast<SysOvrvObject::ObjShapeType>(index))
    {
    case SysOvrvObject::ObjShape_Rectangle:
        m_curSysOvrvObject = new RectSysOvrvObject(std::move(*m_curSysOvrvObject));
        break;
    case SysOvrvObject::ObjShape_Square:
        m_curSysOvrvObject = new SquareSysOvrvObject(std::move(*m_curSysOvrvObject));
        break;
    case SysOvrvObject::ObjShape_Ellipse:
        m_curSysOvrvObject = new EllipseSysOvrvObject(std::move(*m_curSysOvrvObject));
        break;
    case SysOvrvObject::ObjShape_Circle:
        m_curSysOvrvObject = new CircleSysOvrvObject(std::move(*m_curSysOvrvObject));
        break;
    case SysOvrvObject::ObjShape_Triangle:
        m_curSysOvrvObject = new TriangleSysOvrvObject(std::move(*m_curSysOvrvObject));
        break;
    case SysOvrvObject::ObjShape_Image:
        m_curSysOvrvObject = new ImageSysOvrvObject(std::move(*m_curSysOvrvObject));
        //ToDO open file dialog.. pick file .. call method
        /* m_curSysOvrvObject->loadImageFromFile(); */
        break;
    default:
        curObjSave = Q_NULLPTR;
        break;
    }

    SysOvrvScene.addItem(m_curSysOvrvObject);

    if(curObjSave != Q_NULLPTR)
    {
        delete curObjSave;
    }
}

void SysOvrvObjectDialog::slt_addObjectToObject(SysOvrvObject *obj)
{
//    m_curSysOvrvObject->addChildSysOvrvItem(obj);
    /* obj->setPos(m_curSysOvrvObject->pos()); */
    obj->moveBy(10,10);
    obj->setParentItem(m_curSysOvrvObject);
    update();
}

void SysOvrvObjectDialog::slt_focusChanged(QGraphicsItem *newItem, QGraphicsItem *oldItem)
{
    Q_UNUSED(oldItem)

    if(newItem != Q_NULLPTR)
    {
        m_focusedItem = dynamic_cast<SysOvrvObject *>(newItem);
    }
}

void SysOvrvObjectDialog::slt_selectionChanged()
{
    if(!SysOvrvScene.isActive())
    {
        return;
    }
    QList<QGraphicsItem *> selectedItems = SysOvrvScene.selectedItems();
    if(selectedItems.isEmpty())
    {
        m_focusedItem = Q_NULLPTR;
    }
    else
    {
        m_focusedItem = dynamic_cast<SysOvrvObject*>(selectedItems.at(0));
    }
}

SysOvrvObject *SysOvrvObjectDialog::curSysOvrvObject() const
{
    return m_curSysOvrvObject;
}

void SysOvrvObjectDialog::setCurSysOvrvObject(SysOvrvObject *curSysOvrvObject)
{
    m_curSysOvrvObject = curSysOvrvObject;
}

void SysOvrvObjectDialog::setupDialog()
{
    QStringList items(std::move(SysOvrvObject::getShapesAsStringList()));

    ui->objectShapeComboBox->addItems(items);
    ui->objectShapeComboBox->setCurrentIndex(m_curSysOvrvObject->getShape());
    ui->ObjectColorLE->setStyleSheet(QString("QLineEdit { background: %1; }").arg(m_curSysOvrvObject->getObjColor().name()));
    ui->ObjectColorLE->setText(m_curSysOvrvObject->getObjColor().name());
    ui->objectNameLE->setText(m_curSysOvrvObject->getObjName());

    connect(ui->objectShapeComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SysOvrvObjectDialog::slt_objectShapeChanged);

    SysOvrvScene.addItem(this->m_curSysOvrvObject);
//    connect(&SysOvrvScene, &QGraphicsScene::selectionChanged, this, &SysOvrvObjectDialog::slt_selectionChanged);
    connect(&SysOvrvScene, &QGraphicsScene::focusItemChanged, this, &SysOvrvObjectDialog::slt_focusChanged);

    ui->objectVisualizerGraphicsView->setScene(&SysOvrvScene);
}

void SysOvrvObjectDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch(ui->buttonBox->buttonRole(button))
    {
    case QDialogButtonBox::AcceptRole:
        switch(ui->buttonBox->standardButton(button))
        {
        case QDialogButtonBox::Ok:
            if(ui->objectNameLE->text().isEmpty())
            {
                ui->objectNameLE->setFocus();
                break;
            }
            SysOvrvScene.removeItem(m_curSysOvrvObject);
            this->m_curSysOvrvObject->setObjName(ui->objectNameLE->text());
            for(auto childObj : m_curSysOvrvObject->getChildSysOvrvObjects())
            {
                childObj->setAsChild(true);
                childObj->enableEdit(false);
            }
            m_curSysOvrvObject->enableEdit(false);
            emit sgnl_commit(m_curSysOvrvObject);
            accept();
            break;
        case QDialogButtonBox::Save:
            if(ui->objectNameLE->text().isEmpty())
            {
                ui->objectNameLE->setFocus();
                break;
            }
            qDebug() << "Accept: Save SysOvrvObj";
        {
            QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
            qDebug() << saveLoc;
            QFile jsonSaveFile(saveLoc);
            if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
                qDebug() << "error open file to save: " << jsonSaveFile.fileName();
            } else
            {
                //ToDO
                // extract ui content
                // parse content to file format
                // write to file
                jsonSaveFile.write(m_curSysOvrvObject->parseToJson()); //ToDO check for error (-1)
            }
            // close file
            jsonSaveFile.flush(); //always flush after write!
            jsonSaveFile.close();
        }
            break;
        case QDialogButtonBox::Open:
            qDebug() << "Accept: Open SysOvrvObj";
        {
            QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
            qDebug() << openLoc;
            QFile jsonOpenFile(openLoc);
            if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "error opening: " << jsonOpenFile.fileName();
            }
            else
            {
                //ToDO
                SysOvrvScene.removeItem(m_curSysOvrvObject);
                delete m_curSysOvrvObject;
                m_curSysOvrvObject = new SquareSysOvrvObject();
                // read file content
                QByteArray jsonSysOvrvObj = jsonOpenFile.readAll();
                m_curSysOvrvObject->parseFromJson(jsonSysOvrvObj); //ToDO check for error (-1)
                m_curSysOvrvObject->enableEdit(true);
                for(auto childObj : m_curSysOvrvObject->getChildSysOvrvObjects())
                {
                    childObj->setAsChild(false);
                    childObj->enableEdit(true);
                }
                ui->ObjectColorLE->setStyleSheet(QString("QLineEdit { background: %1; }").arg(m_curSysOvrvObject->getObjColor().name()));
                ui->ObjectColorLE->setText(m_curSysOvrvObject->getObjColor().name());
                ui->objectNameLE->setText(m_curSysOvrvObject->getObjName());
                ui->objectShapeComboBox->setCurrentIndex(m_curSysOvrvObject->getShape());
                SysOvrvScene.addItem(m_curSysOvrvObject);
            }
            // close file
            jsonOpenFile.close();
        }
            break;
        default:
            qDebug() << "Invalid button: " << ui->buttonBox->standardButton(button);
        }

        break;
    case QDialogButtonBox::RejectRole:
        SysOvrvScene.removeItem(m_curSysOvrvObject);
        if(updateExisting)
        {
            delete m_curSysOvrvObject;
            //restore from json save
            m_curSysOvrvObject = new SquareSysOvrvObject();
            m_curSysOvrvObject->parseFromJson(m_jsonObjSave);
            emit sgnl_commit(m_curSysOvrvObject);
        }
        else
        {
            delete m_curSysOvrvObject;
        }
        reject();
        break;
    case QDialogButtonBox::ResetRole:
        SysOvrvScene.removeItem(m_curSysOvrvObject);
        delete m_curSysOvrvObject;
        m_curSysOvrvObject = new SquareSysOvrvObject();
        m_curSysOvrvObject->parseFromJson(m_jsonObjSave);
        m_curSysOvrvObject->enableResizing(true);
        ui->ObjectColorLE->setStyleSheet(QString("QLineEdit { background: %1; }").arg(m_curSysOvrvObject->getObjColor().name()));
        ui->ObjectColorLE->setText(m_curSysOvrvObject->getObjColor().name());
        ui->objectNameLE->setText(m_curSysOvrvObject->getObjName());
        ui->objectShapeComboBox->setCurrentIndex(m_curSysOvrvObject->getShape());

        SysOvrvScene.addItem(m_curSysOvrvObject);
        break;
    default:
        break;
    }
}

void SysOvrvObjectDialog::on_OpenColorPicker_clicked()
{
    QColorDialog *colorPicker = new QColorDialog(m_curSysOvrvObject->getObjColor(), this);
    connect(colorPicker, &QColorDialog::colorSelected, this, &SysOvrvObjectDialog::slt_colorChanged);
    colorPicker->exec();
}

void SysOvrvObjectDialog::slt_colorChanged(const QColor &newColor)
{
    qDebug() << "Color picked: " << newColor.name();
    ui->ObjectColorLE->setStyleSheet(QString("QLineEdit { background: %1; }").arg(newColor.name()));
    ui->ObjectColorLE->setText(newColor.name());
    m_curSysOvrvObject->setObjColor(QColor(newColor));
}

void SysOvrvObjectDialog::on_pushButton_clicked() //duplicate
{
    if(m_focusedItem == Q_NULLPTR)
    {
        return;
    }
    //IF the main object is to be duplicated, the main object shall be the parent of the duplicated object
    SysOvrvObject* duplicateObjParent = (m_focusedItem == m_curSysOvrvObject) ? m_focusedItem : Q_NULLPTR;
    SysOvrvObject* duplicatedObject = m_focusedItem->duplicate(duplicateObjParent);

    duplicateObjParent = dynamic_cast<SysOvrvObject*>(duplicatedObject->parentItem());
    if(duplicateObjParent == Q_NULLPTR)
    {
        return;
    }
    duplicatedObject->setPos(duplicateObjParent->pos());
    duplicatedObject->moveBy(10,10);
    duplicatedObject->enableEdit(true);
//    //The parent of the duplicated object shall always be the current object that is being edited by the current dialog!
//    if(duplicateObjParent != Q_NULLPTR)
//    {
//        duplicateObjParent->removeChildSysOvrvItem(duplicatedObject);
//    }
//    m_curSysOvrvObject->addChildSysOvrvItem(duplicatedObject);
}

void SysOvrvObjectDialog::on_objectNameLE_textEdited(const QString &arg1)
{
    m_curSysOvrvObject->setObjName(arg1);
}

void SysOvrvObjectDialog::on_addLblBtn_clicked()
{
    m_curSysOvrvObject->addLabel();
}
