#include "sysovrvobjectdialog.h"
#include "ui_sysovrvobjectdialog.h"

#include "sysovrvobjtriggerdialog.h"
#include "triggerablesysovrvobj.h"

#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QDebug>

SysOvrvObjectDialog::SysOvrvObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjectDialog),
    m_curSysOvrvObject(new SysOvrvObject()),
    m_focusedItem(NULL),
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
    m_focusedItem(NULL),
    updateExisting(true)
{
    m_jsonObjSave = m_curSysOvrvObject->parseToJson();
    ui->setupUi(this);
    this->setupDialog();
    m_curSysOvrvObject->enableEdit(true);
    for(auto childObj : m_curSysOvrvObject->getChidSysOvrvObjects())
    {
        childObj->setAsChild(false);
    }
}

SysOvrvObjectDialog::~SysOvrvObjectDialog()
{
    qDebug() << __PRETTY_FUNCTION__;
    delete ui;
}

void SysOvrvObjectDialog::on_addPropertyBtn_clicked()
{
    SysOvrvObjectDialog addSysOvrvObjectDialog;// = new SysOvrvObjectDialog();
    connect(&addSysOvrvObjectDialog, &SysOvrvObjectDialog::commit, this, &SysOvrvObjectDialog::addObjectToObject);
    addSysOvrvObjectDialog.exec();
}

void SysOvrvObjectDialog::on_rmvPropertyBtn_clicked()
{
    if((m_focusedItem == NULL) || (m_focusedItem == this->m_curSysOvrvObject))
        return;

    qDebug() << "Focused item: " << m_focusedItem->getObjName();

    delete m_focusedItem;
    m_focusedItem = NULL;
}

void SysOvrvObjectDialog::on_edtPropertyBtn_clicked()
{
    if((m_focusedItem == NULL) || (m_focusedItem == this->m_curSysOvrvObject))
        return;

    qDebug() << "Focused item: " << m_focusedItem->getObjName();

    SysOvrvObjectDialog *addSysOvrvObjectDialog = new SysOvrvObjectDialog(m_focusedItem);
    connect(addSysOvrvObjectDialog, &SysOvrvObjectDialog::commit, this, &SysOvrvObjectDialog::addObjectToObject);
    addSysOvrvObjectDialog->exec();
}

void SysOvrvObjectDialog::on_edtTriggerBtn_clicked()
{
    if(m_focusedItem == NULL)
        return;

    //DO SOMETHING HERE! TRIGGER ALL THE SysOvrvObjs!
    SysOvrvObjTriggerDialog *triggerDiag = new SysOvrvObjTriggerDialog(m_focusedItem, this);

    triggerDiag->exec();
}

void SysOvrvObjectDialog::objectShapeChanged(int index)
{
    switch(static_cast<SysOvrvObject::ObjShapeType>(index))
    {
    case SysOvrvObject::ObjShape_Rectangle:
        m_curSysOvrvObject->setShape(SysOvrvObject::ObjShape_Rectangle);
        break;
    case SysOvrvObject::ObjShape_Square:
        m_curSysOvrvObject->setShape(SysOvrvObject::ObjShape_Square);
        break;
    case SysOvrvObject::ObjShape_Ellipse:
        m_curSysOvrvObject->setShape(SysOvrvObject::ObjShape_Ellipse);
        break;
    case SysOvrvObject::ObjShape_Circle:
        m_curSysOvrvObject->setShape(SysOvrvObject::ObjShape_Circle);
        break;
    case SysOvrvObject::ObjShape_Triangle:
        m_curSysOvrvObject->setShape(SysOvrvObject::ObjShape_Triangle);
        break;
    case SysOvrvObject::ObjShape_Image:
        m_curSysOvrvObject->loadImageFromFile();
        m_curSysOvrvObject->setShape(SysOvrvObject::ObjShape_Image);
        break;
    default:
        break;
    }
}

void SysOvrvObjectDialog::addObjectToObject(SysOvrvObject *obj)
{
//    m_curSysOvrvObject->addChildSysOvrvItem(obj);
    obj->setPos(m_curSysOvrvObject->pos());
    obj->moveBy(10,10);
    obj->setParentItem(m_curSysOvrvObject);
    this->update();
}

void SysOvrvObjectDialog::focusChanged(QGraphicsItem *newItem, QGraphicsItem *oldItem)
{
    Q_UNUSED(oldItem)

    if(newItem != Q_NULLPTR)
        m_focusedItem = dynamic_cast<SysOvrvObject *>(newItem);
}

void SysOvrvObjectDialog::selectionChanged()
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
    ui->ObjectColorLE->setStyleSheet(QString("QLineEdit { background: %1; }").arg(m_curSysOvrvObject->getMyColor().name()));
    ui->ObjectColorLE->setText(m_curSysOvrvObject->getMyColor().name());
    ui->objectNameLE->setText(m_curSysOvrvObject->getObjName());

    connect(ui->objectShapeComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SysOvrvObjectDialog::objectShapeChanged);

    SysOvrvScene.addItem(this->m_curSysOvrvObject);
//    connect(&SysOvrvScene, &QGraphicsScene::selectionChanged, this, &SysOvrvObjectDialog::selectionChanged);
    connect(&SysOvrvScene, &QGraphicsScene::focusItemChanged, this, &SysOvrvObjectDialog::focusChanged);

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
            for(auto childObj : m_curSysOvrvObject->getChidSysOvrvObjects())
            {
                childObj->setAsChild(true);
            }
            emit commit(this->m_curSysOvrvObject);
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
                m_curSysOvrvObject = new SysOvrvObject();
                // read file content
                QByteArray jsonSysOvrvObj = jsonOpenFile.readAll();
                m_curSysOvrvObject->parseFromJson(jsonSysOvrvObj); //ToDO check for error (-1)
                m_curSysOvrvObject->enableResizing(true);
                for(auto childObj : m_curSysOvrvObject->getChidSysOvrvObjects())
                {
                    childObj->setAsChild(false);
                }
                ui->ObjectColorLE->setStyleSheet(QString("QLineEdit { background: %1; }").arg(m_curSysOvrvObject->getMyColor().name()));
                ui->ObjectColorLE->setText(m_curSysOvrvObject->getMyColor().name());
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
            m_curSysOvrvObject = new SysOvrvObject();
            m_curSysOvrvObject->parseFromJson(m_jsonObjSave);
            emit commit(m_curSysOvrvObject);
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
        m_curSysOvrvObject = new SysOvrvObject();
        m_curSysOvrvObject->parseFromJson(m_jsonObjSave);
        m_curSysOvrvObject->enableResizing(true);
        ui->ObjectColorLE->setStyleSheet(QString("QLineEdit { background: %1; }").arg(m_curSysOvrvObject->getMyColor().name()));
        ui->ObjectColorLE->setText(m_curSysOvrvObject->getMyColor().name());
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
    QColorDialog *colorPicker = new QColorDialog(m_curSysOvrvObject->getMyColor(), this);
    connect(colorPicker, &QColorDialog::colorSelected, this, &SysOvrvObjectDialog::colorChanged);
    colorPicker->exec();
}

void SysOvrvObjectDialog::colorChanged(const QColor &newColor)
{
    qDebug() << "Color picked: " << newColor.name();
    ui->ObjectColorLE->setStyleSheet(QString("QLineEdit { background: %1; }").arg(newColor.name()));
    ui->ObjectColorLE->setText(newColor.name());
    m_curSysOvrvObject->setMyColor(QColor(newColor));
}

void SysOvrvObjectDialog::on_pushButton_clicked() //duplicate
{
    if(m_focusedItem == Q_NULLPTR)
        return;
    //IF the main object is to be duplicated, the main object shall be the parent of the duplicated object
    SysOvrvObject* duplicateObjParent = (m_focusedItem == m_curSysOvrvObject) ? m_focusedItem : NULL;
    SysOvrvObject* duplicatedObject = m_focusedItem->duplicate(duplicateObjParent);

    duplicateObjParent = dynamic_cast<SysOvrvObject*>(duplicatedObject->parentItem());
    if(duplicateObjParent == Q_NULLPTR)
    {
        return;
    }
    duplicatedObject->setPos(duplicateObjParent->pos());
    duplicatedObject->moveBy(10,10);
//    //The parent of the duplicated object shall always be the current object that is being edited by the current dialog!
//    if(duplicateObjParent != NULL)
//    {
//        duplicateObjParent->removeChildSysOvrvItem(duplicatedObject);
//    }
//    m_curSysOvrvObject->addChildSysOvrvItem(duplicatedObject);
    duplicatedObject->setAsChild(false);
}

void SysOvrvObjectDialog::on_objectNameLE_textEdited(const QString &arg1)
{
    m_curSysOvrvObject->setObjName(arg1);
}

void SysOvrvObjectDialog::on_addLblBtn_clicked()
{
    m_curSysOvrvObject->addLabel();
}
