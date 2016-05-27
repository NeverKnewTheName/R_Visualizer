#include "idadddialog.h"
#include "ui_idadddialog.h"

#include <QDebug>
#include <QColorDialog>

IDAddDialog::IDAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IDAddDialog)
{
    ui->setupUi(this);
    connect(this, &IDAddDialog::accepted, this, &IDAddDialog::readyToCommit);
}

IDAddDialog::~IDAddDialog()
{
    delete ui;
}

void IDAddDialog::colorSelected(const QColor &color)
{
    qDebug() << "Color picked: " << color.name();
    ui->colorLineEdit->setStyleSheet(QString("QLineEdit { background: %1; }").arg(color.name()));
    ui->colorLineEdit->setText(color.name());
}

void IDAddDialog::on_pushButton_clicked()
{
    QColorDialog *colorPicker = new QColorDialog(this);
    connect(colorPicker, &QColorDialog::colorSelected, this, &IDAddDialog::colorSelected);
    colorPicker->exec();
}

void IDAddDialog::readyToCommit()
{
    emit commit(ui->idLineEdit->text().toInt(0, 16), ui->nameLineEdit->text(), QColor(ui->colorLineEdit->text()));
}
