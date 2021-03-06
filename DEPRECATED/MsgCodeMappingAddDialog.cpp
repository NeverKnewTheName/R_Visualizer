#include "msgtypeadddialog.h"
#include "ui_msgtypeadddialog.h"

#include "msgtypeformatterdialog.h"

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

    inputMasks << "\\0\\xhh"/*HEX*/
               << "000"/*DEC*/
               << "\\0\\b bbbb\\ bbbb"/*BIN*/;

    QStringList items;
    items << "Hex" << "Dec" << "Bin";
    ui->numericallFormatComboBox->addItems(items);
}

MsgCodeMappingAddDialog::~MsgCodeMappingAddDialog()
{
    delete ui;
}

int MsgCodeMappingAddDialog::parseToNumber(QString numericalString)
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

QString MsgCodeMappingAddDialog::parseToString(int number)
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

void MsgCodeMappingAddDialog::colorSelected(const QColor &color)
{
    qDebug() << "Color picked: " << color.name();
    ui->colorLineEdit->setStyleSheet(
            QString("QLineEdit { background: %1; }").arg(color.name())
            );
    ui->colorLineEdit->setText(color.name());
}

void MsgCodeMappingAddDialog::formatSelected(const QString &formatString)
{
    qDebug() << "format specified: " << formatString;
    ui->formatPlainTextEdit->clear();
    ui->formatPlainTextEdit->textCursor().insertText(formatString);
}

void MsgCodeMappingAddDialog::readyToCommit()
{
    emit commit(
            MsgCodeType(this->parseToNumber(ui->codeLineEdit->text())),
            ui->nameLineEdit->text(),
            ui->formatPlainTextEdit->document()->toPlainText(),
            QColor(ui->colorLineEdit->text())
            );
    //emit QDialog::accepted();
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
    colorPicker->exec();
}

void MsgCodeMappingAddDialog::on_formatterPushButton_clicked()
{
    MsgCodeMappingFormatterDialog *formatter =
        new MsgCodeMappingFormatterDialog(this);

    connect(
            formatter,
            &MsgCodeMappingFormatterDialog::commit,
            this,
            &MsgCodeMappingAddDialog::formatSelected
            );

    formatter->setFormatString(
            ui->formatPlainTextEdit->document()->toPlainText()
            );
    formatter->exec();
}

void MsgCodeMappingAddDialog::on_numericallFormatComboBox_currentIndexChanged(
        int index
        )
{
    int enteredNumber = this->parseToNumber(ui->codeLineEdit->text());
    ui->codeLineEdit->setInputMask(inputMasks.at(index));
    ui->codeLineEdit->setText(this->parseToString(enteredNumber));
    ui->codeLineEdit->setFocus();
    ui->codeLineEdit->setCursorPosition(0);
    ui->codeLineEdit->selectAll();
}
