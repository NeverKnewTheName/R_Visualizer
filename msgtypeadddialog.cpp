#include "msgtypeadddialog.h"
#include "ui_msgtypeadddialog.h"

#include <QDebug>
#include <QColorDialog>

MsgTypeAddDialog::MsgTypeAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgTypeAddDialog)
{
    ui->setupUi(this);
    connect(this, &MsgTypeAddDialog::accepted, this, &MsgTypeAddDialog::readyToCommit);
}

MsgTypeAddDialog::~MsgTypeAddDialog()
{
    delete ui;
}

void MsgTypeAddDialog::colorSelected(const QColor &color)
{
    qDebug() << "Color picked: " << color.name();
    ui->colorLineEdit->setStyleSheet(QString("QLineEdit { background: %1; }").arg(color.name()));
    ui->colorLineEdit->setText(color.name());
}

void MsgTypeAddDialog::readyToCommit()
{
    emit commit(ui->codeLineEdit->text().toInt(0,16), ui->messageLineEdit->text(), QColor(ui->colorLineEdit->text()));
}

void MsgTypeAddDialog::on_colorPickerPushButton_clicked()
{
    QColorDialog *colorPicker = new QColorDialog(this);
    connect(colorPicker, &QColorDialog::colorSelected, this, &MsgTypeAddDialog::colorSelected);
    colorPicker->exec();
}
