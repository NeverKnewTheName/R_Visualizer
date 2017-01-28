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
    inputMasks << "\\0\\xhh"/*HEX*/
               << "000"/*DEC*/
               << "\\0\\b bbbb\\ bbbb"/*BIN*/;

    QStringList items;
    items << "Hex" << "Dec" << "Bin";
    ui->numericallFormatComboBox->addItems(items);
}

MsgTypeAddDialog::~MsgTypeAddDialog()
{
    delete ui;
}

int MsgTypeAddDialog::parseToNumber(QString numericalString)
{
    int idNumericalBase;
    if(numericalString.contains("0x"))
    {
        idNumericalBase = 16;
    }
    else if(numericalString.contains("0b"))
    {
        idNumericalBase = 2;
        numericalString.replace(" ","").replace("0b","");
        qDebug() << numericalString;
    }
    else
    {
        idNumericalBase = 10;
    }
    return numericalString.toInt(0, idNumericalBase);
}

QString MsgTypeAddDialog::parseToString(int number)
{
    int idNumericalBase = ui->numericallFormatComboBox->currentIndex();
    if(idNumericalBase == 0)
    {
        idNumericalBase = 16;
    }
    else if(idNumericalBase == 1)
    {
        idNumericalBase = 10;
    }
    else if(idNumericalBase == 2)
    {
        idNumericalBase = 2;
    }
    return QString::number(number, idNumericalBase);
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
    emit commit(this->parseToNumber(ui->codeLineEdit->text()), ui->nameLineEdit->text(), ui->formatPlainTextEdit->document()->toPlainText(), QColor(ui->colorLineEdit->text()));
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

void MsgTypeAddDialog::on_numericallFormatComboBox_currentIndexChanged(int index)
{
    int enteredNumber = this->parseToNumber(ui->codeLineEdit->text());
    ui->codeLineEdit->setInputMask(inputMasks.at(index));
    ui->codeLineEdit->setText(this->parseToString(enteredNumber));
    ui->codeLineEdit->setFocus();
    ui->codeLineEdit->setCursorPosition(0);
    ui->codeLineEdit->selectAll();
}
