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
    }
    else
    {
        idNumericalBase = 10;
    }
    return numericalString.toInt(0, idNumericalBase);
}

QString MsgCodeMappingAddDialog::parseToString(const int number)
{
    int idNumericalBase = ui->numericallFormatComboBox->currentIndex();

    switch(idNumericalBase)
    {
        case 0:
            idNumericalBase = 16;
            break;
        case 1:
            idNumericalBase = 10;
            break;
        case 2:
            idNumericalBase = 2;
            break;
        default:
            idNumericalBase = 10;
            break;
    }

    return QString::number(number, idNumericalBase);
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
            MsgCodeType(this->parseToNumber(ui->codeLineEdit->text())),
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
    colorPicker->exec();
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
