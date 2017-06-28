#include "MsgCodeMappingAddDialog.h"
#include "ui_msgcodemappingadddialog.h"

#include <QDebug>
#include <QColorDialog>

MsgCodeMappingAddDialog::MsgCodeMappingAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgCodeMappingAddDialog)
{
    ui->setupUi(this);
    connect(
            this,
            &MsgCodeMappingAddDialog::accepted,
            this,
            &MsgCodeMappingAddDialog::readyToCommit
            );

    setTabOrder(ui->msgCodeLineEdit,ui->nameLineEdit);
    setTabOrder(ui->nameLineEdit,ui->colorLineEdit);
    setTabOrder(ui->colorLineEdit,ui->colorPickerPushButton);
    setTabOrder(ui->colorPickerPushButton,ui->buttonBox);

    ui->msgCodeLineEdit->setFocus();
}

MsgCodeMappingAddDialog::~MsgCodeMappingAddDialog()
{
    delete ui;
}

void MsgCodeMappingAddDialog::colorSelected(const QColor &color)
{
    ui->colorLineEdit->setStyleSheet(
            QString("QLineEdit { background: %1; }").arg(color.name())
            );
    ui->colorLineEdit->setText(color.name());
}

void MsgCodeMappingAddDialog::readyToCommit()
{
    emit commit(
            ui->msgCodeLineEdit->getMsgCode(),
            ui->nameLineEdit->text(),
            QColor(ui->colorLineEdit->text())
            );
}

void MsgCodeMappingAddDialog::on_colorPickerPushButton_clicked()
{
    QColorDialog *colorPicker = new QColorDialog(this);
    connect(
            colorPicker,
            &QColorDialog::colorSelected,
            this,
            &MsgCodeMappingAddDialog::colorSelected
            );
    colorPicker->setAttribute(Qt::WA_DeleteOnClose);
    colorPicker->exec();
}
