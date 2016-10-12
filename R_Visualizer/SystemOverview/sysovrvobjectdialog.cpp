#include "sysovrvobjectdialog.h"
#include "ui_sysovrvobjectdialog.h"
#include <QColorDialog>

#include <qDebug>

SysOvrvObjectDialog::SysOvrvObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjectDialog),
  m_curSysOvrvObject(new SysOvrvObject()),
  m_svdSysOvrvObject(new SysOvrvObject()),
  m_focusedItem(NULL),
  updateExisting(false)
{
    ui->setupUi(this);
    m_curSysOvrvObject->setResizeMode(true);
    m_svdSysOvrvObject->setResizeMode(true);
    this->setupDialog();
}

SysOvrvObjectDialog::SysOvrvObjectDialog(SysOvrvObject *object, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjectDialog),
    m_curSysOvrvObject(object),
    m_svdSysOvrvObject(new SysOvrvObject(object)),
    m_focusedItem(NULL),
    updateExisting(true)
{
    ui->setupUi(this);
    this->setupDialog();
    for(auto childObj : m_curSysOvrvObject->getChidSysOvrvObjects())
    {
        childObj->setAsChild(false);
    }
    qDebug() << "Object to update name: " << object->getObjName();
}

SysOvrvObjectDialog::~SysOvrvObjectDialog()
{
    delete m_svdSysOvrvObject;
    delete ui;
}

void SysOvrvObjectDialog::on_addPropertyBtn_clicked()
{
    SysOvrvObjectDialog *addSysOvrvObjectDialog = new SysOvrvObjectDialog();
    connect(addSysOvrvObjectDialog, &SysOvrvObjectDialog::commit, this, &SysOvrvObjectDialog::addObjectToObject);
    addSysOvrvObjectDialog->exec();
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

}

void SysOvrvObjectDialog::objectShapeChanged(int index)
{
    switch(index)
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
    }
}

void SysOvrvObjectDialog::addObjectToObject(SysOvrvObject *obj)
{
    m_curSysOvrvObject->addChildSysOvrvItem(obj);
    this->update();
}

void SysOvrvObjectDialog::focusChanged(QGraphicsItem *newItem, QGraphicsItem *oldItem)
{
    if(newItem != NULL)
        m_focusedItem = qgraphicsitem_cast<SysOvrvObject *>(newItem);
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
    QStringList items;
    items << "Rectangle"
          << "Square"
          << "Ellipse"
          << "Circle"
          << "Triangle";

    ui->objectShapeComboBox->addItems(items);
    connect(ui->objectShapeComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SysOvrvObjectDialog::objectShapeChanged);

    ui->ObjectColorLE->setStyleSheet(QString("QLineEdit { background: %1; }").arg(m_curSysOvrvObject->getMyColor().name()));
    ui->ObjectColorLE->setText(m_curSysOvrvObject->getMyColor().name());
    ui->objectNameLE->setText(m_curSysOvrvObject->getObjName());
    ui->objectShapeComboBox->setCurrentIndex(m_curSysOvrvObject->getShape());

    scene = new QGraphicsScene();
    scene->addItem(this->m_curSysOvrvObject);
    connect(scene, &QGraphicsScene::focusItemChanged, this, &SysOvrvObjectDialog::focusChanged);

    ui->objectVisualizerGraphicsView->setScene(scene);
}

void SysOvrvObjectDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch(ui->buttonBox->buttonRole(button))
    {
    case QDialogButtonBox::AcceptRole:
        if(ui->objectNameLE->text().isEmpty())
        {
            break;
        }
        scene->removeItem(m_curSysOvrvObject);
        this->m_curSysOvrvObject->setObjName(ui->objectNameLE->text());
        for(auto childObj : m_curSysOvrvObject->getChidSysOvrvObjects())
        {
            childObj->setAsChild(true);
        }
        emit commit(this->m_curSysOvrvObject);
        delete m_svdSysOvrvObject;
        accept();
        break;
    case QDialogButtonBox::RejectRole:
        scene->removeItem(m_curSysOvrvObject);
        if(updateExisting)
        {
            *m_curSysOvrvObject = *m_svdSysOvrvObject;
            for(auto childObj : m_curSysOvrvObject->getChidSysOvrvObjects())
            {
                childObj->setAsChild(true);
            }
            emit commit(m_curSysOvrvObject);
        }
        else
        {
            delete m_curSysOvrvObject;
        }
        delete m_svdSysOvrvObject;
        reject();
        break;
    case QDialogButtonBox::ResetRole:
        *m_curSysOvrvObject = *m_svdSysOvrvObject;
        m_curSysOvrvObject->update();
        ui->objectNameLE->setText(m_curSysOvrvObject->getObjName());
        ui->objectShapeComboBox->setCurrentIndex(m_curSysOvrvObject->getShape());
        scene->update();
        break;
    }
}

void SysOvrvObjectDialog::on_OpenColorPicker_clicked()
{
    QColorDialog *colorPicker = new QColorDialog(this);
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
