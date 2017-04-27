#include "MsgDataMappingAddDialog.h"
#include "ui_msgdatamappingadddialog.h"

#include <QDebug>
#include <QColorDialog>

MsgDataMappingAddDialog::MsgDataMappingAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgDataMappingAddDialog)
{
    ui->setupUi(this);

    connect(
            this,
            &MsgDataMappingAddDialog::accepted,
            this,
            &MsgDataMappingAddDialog::slt_ReadyToCommit
           );

    numericalFormatStringList
        << "\\0\\xhhhh"/*HEX*/
       << "00000"/*DEC*/
       << "\\0\\b bbbb\\ bbbb\\ bbbb\\ bbbb"/*BIN*/;

    QStringList items;
    items << "Hex" << "Dec" << "Bin";
    ui->idNumericalFormatComboBox->addItems(items);
    ui->codeNumericalFormatComboBox->addItems(items);
}

MsgDataMappingAddDialog::~MsgDataMappingAddDialog()
{
    delete ui;
}

int MsgDataMappingAddDialog::numericalSelectionToBase(
        const int numericalSelection
        )
{
    switch(numericalSelection)
    {
        case 0:
            return 16;
            break;
        case 1:
            return 10;
            break;
        case 2:
            return 2;
            break;
        default:
            return 10;
    }
}

int MsgDataMappingAddDialog::parseIDStringToNumber()
{
    QString numericalString =
        ui->idLineEdit->text();

    return parseToNumber(
            numericalString
            );
}

int MsgDataMappingAddDialog::parseCodeStringToNumber()
{
    QString numericalString =
        ui->codeLineEdit->text();

    return parseToNumber(
            numericalString
            );
}

int MsgDataMappingAddDialog::parseToNumber(
        QString numericalString
        )
{
    int numericalBase;
    if(numericalString.contains("0x"))
    {
        numericalBase = 16;
    }
    else if(numericalString.contains("0b"))
    {
        numericalBase = 2;
        numericalString.replace(" ","").replace("0b","");
    }
    else
    {
        numericalBase = 10;
    }

    return numericalString.toInt(0, numericalBase);
}

QString MsgDataMappingAddDialog::parseIDToString(const int id)
{
    const int numericalSelection =
        ui->idNumericalFormatComboBox->currentIndex();

    return parseToString(id,numericalSelection);
}

QString MsgDataMappingAddDialog::parseCodeToString(const int code)
{
    const int numericalSelection =
        ui->codeNumericalFormatComboBox->currentIndex();

    return parseToString(code,numericalSelection);
}

QString MsgDataMappingAddDialog::parseToString(
        const int number,
        const int numericalSelection
        )
{
    return QString::number(
            number,
            numericalSelectionToBase(numericalSelection)
            );
}

void MsgDataMappingAddDialog::slt_ColorSelected(
        const QColor &color
        )
{
    ui->colorLineEdit->setStyleSheet(
            QString("QLineEdit { background: %1; }").arg(color.name())
            );
    ui->colorLineEdit->setText(color.name());
}

void MsgDataMappingAddDialog::slt_ReadyToCommit()
{
    emit sgnl_Commit(
            MsgIDType(parseIDStringToNumber()),
            MsgCodeType(parseCodeStringToNumber()),
            ui->formatterPlainTextEdit->toPlainText(),
            QColor(ui->colorLineEdit->text())
            );
}

void MsgDataMappingAddDialog::on_idNumericalFormatComboBox_currentIndexChanged(
        int index
        )
{
    int enteredNumber = parseIDStringToNumber();
    ui->idLineEdit->setInputMask(numericalFormatStringList.at(index));
    ui->idLineEdit->setText(parseIDToString(enteredNumber));
    ui->idLineEdit->setFocus();
    ui->idLineEdit->setCursorPosition(0);
    ui->idLineEdit->selectAll();
}

void MsgDataMappingAddDialog::on_codeNumericalFormatComboBox_currentIndexChanged(
        int index
        )
{
    int enteredNumber = parseCodeStringToNumber();
    ui->codeLineEdit->setInputMask(numericalFormatStringList.at(index));
    ui->codeLineEdit->setText(parseCodeToString(enteredNumber));
    ui->codeLineEdit->setFocus();
    ui->codeLineEdit->setCursorPosition(0);
    ui->codeLineEdit->selectAll();
}

void MsgDataMappingAddDialog::on_formatterPushButton_clicked()
{

}

void MsgDataMappingAddDialog::on_colorPickerPushButton_clicked()
{
    QColorDialog *colorPicker = new QColorDialog(this);
    connect(
            colorPicker,
            &QColorDialog::colorSelected,
            this,
            &MsgDataMappingAddDialog::slt_ColorSelected
            );
    colorPicker->exec();
}
