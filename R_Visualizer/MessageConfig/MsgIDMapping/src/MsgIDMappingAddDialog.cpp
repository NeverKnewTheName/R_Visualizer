#include "MsgIDMappingAddDialog.h"
#include "ui_msgidmappingadddialog.h"

#include <QDebug>
#include <QColorDialog>

MsgIDMappingAddDialog::MsgIDMappingAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgIDMappingAddDialog)
{
    ui->setupUi(this);
    connect(
            this,
            &MsgIDMappingAddDialog::accepted,
            this,
            &MsgIDMappingAddDialog::readyToCommit
            );

    setTabOrder(ui->msgIDLineEdit,ui->nameLineEdit);
    setTabOrder(ui->nameLineEdit,ui->colorLineEdit);
    setTabOrder(ui->colorLineEdit,ui->pushButton);
    setTabOrder(ui->pushButton,ui->buttonBox);

    ui->msgIDLineEdit->setFocus();
}

MsgIDMappingAddDialog::~MsgIDMappingAddDialog()
{
    delete ui;
}

void MsgIDMappingAddDialog::colorSelected(const QColor &color)
{
    ui->colorLineEdit->setStyleSheet(
            QString("QLineEdit { background: %1; }").arg(color.name())
            );
    ui->colorLineEdit->setText(color.name());
}

void MsgIDMappingAddDialog::on_pushButton_clicked()
{
    QColorDialog *colorPicker = new QColorDialog(this);

    connect(
            colorPicker,
            &QColorDialog::colorSelected,
            this,
            &MsgIDMappingAddDialog::colorSelected
            );

    colorPicker->exec();
}

void MsgIDMappingAddDialog::readyToCommit()
{
    emit sgnl_commit(
            ui->msgIDLineEdit->getMsgID(),
            ui->nameLineEdit->text(),
            QColor(ui->colorLineEdit->text())
            );
}
