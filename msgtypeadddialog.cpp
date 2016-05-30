#include "msgtypeadddialog.h"
#include "ui_msgtypeadddialog.h"

#include "msgtypeformatterdialog.h"

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

void MsgTypeAddDialog::formatSelected(const QString &formatString)
{
    qDebug() << "format specified: " << formatString;
    ui->formatPlainTextEdit->clear();
    ui->formatPlainTextEdit->textCursor().insertText(formatString);
}

void MsgTypeAddDialog::readyToCommit()
{
    qDebug() << ui->formatPlainTextEdit->document()->toPlainText();
    emit commit(ui->codeLineEdit->text().toInt(0,16), ui->nameLineEdit->text(), ui->formatPlainTextEdit->document()->toPlainText(), QColor(ui->colorLineEdit->text()));
    //emit QDialog::accepted();
}

void MsgTypeAddDialog::on_colorPickerPushButton_clicked()
{
    QColorDialog *colorPicker = new QColorDialog(this);
    connect(colorPicker, &QColorDialog::colorSelected, this, &MsgTypeAddDialog::colorSelected);
    colorPicker->exec();
}

void MsgTypeAddDialog::on_formatterPushButton_clicked()
{
    MsgTypeFormatterDialog *formatter = new MsgTypeFormatterDialog(this);
    connect(formatter, &MsgTypeFormatterDialog::commit, this, &MsgTypeAddDialog::formatSelected);
    formatter->setFormatString(ui->formatPlainTextEdit->document()->toPlainText());
    formatter->exec();
}
