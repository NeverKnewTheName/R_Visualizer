#include "sysovrvobjectdialog.h"
#include "ui_sysovrvobjectdialog.h"

SysOvrvObjectDialog::SysOvrvObjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjectDialog)
{
    ui->setupUi(this);
    this->m_curSysOvrvObject = new SysOvrvObject();
    this->setupDialog();
}

SysOvrvObjectDialog::SysOvrvObjectDialog(SysOvrvObject *object, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjectDialog)
{
    ui->setupUi(this);
    this->m_curSysOvrvObject = object;
    this->setupDialog();
}



SysOvrvObjectDialog::~SysOvrvObjectDialog()
{
    delete ui;
}

void SysOvrvObjectDialog::on_addPropertyBtn_clicked()
{

}

void SysOvrvObjectDialog::on_rmvPropertyBtn_clicked()
{

}

void SysOvrvObjectDialog::on_edtPropertyBtn_clicked()
{

}

void SysOvrvObjectDialog::on_edtTriggerBtn_clicked()
{

}

void SysOvrvObjectDialog::objectShapeChanged(int index)
{
    switch(index)
    {
    case ObjShape_Rectangle:
        m_curSysOvrvObject->setShape(ObjShape_Rectangle);
        break;
    case ObjShape_Square:
        m_curSysOvrvObject->setShape(ObjShape_Square);
        break;
    case ObjShape_Circle:
        m_curSysOvrvObject->setShape(ObjShape_Circle);
        break;
    case ObjShape_Triangle:
        m_curSysOvrvObject->setShape(ObjShape_Triangle);
        break;
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
    QStringList items;
    items << "Rectangle"
          << "Square"
          << "Circle"
          << "Triangle";

    ui->objectShapeComboBox->addItems(items);
    connect(ui->objectShapeComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SysOvrvObjectDialog::objectShapeChanged);

    scene = new QGraphicsScene();
    scene->addItem(this->m_curSysOvrvObject);

    ui->objectVisualizerGraphicsView->setScene(scene);
}

void SysOvrvObjectDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch(ui->buttonBox->buttonRole(button))
    {
    case QDialogButtonBox::AcceptRole:
        emit commit(this->m_curSysOvrvObject);
        break;
    case QDialogButtonBox::RejectRole:
        break;
    case QDialogButtonBox::ResetRole:
        break;
    }
}
