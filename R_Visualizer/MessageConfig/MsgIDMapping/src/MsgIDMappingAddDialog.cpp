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

    inputMasks << "\\0\\xhhhh"/*HEX*/
               << "00000"/*DEC*/
               << "\\0\\b bbbb\\ bbbb\\ bbbb\\ bbbb"/*BIN*/;

    QStringList items;
    items << "Hex" << "Dec" << "Bin";
    ui->numericallFormatComboBox->addItems(items);
}

MsgIDMappingAddDialog::~MsgIDMappingAddDialog()
{
    delete ui;
}

int MsgIDMappingAddDialog::parseToNumber(QString numericalString)
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

QString MsgIDMappingAddDialog::parseToString(const int number)
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
    }

    return QString::number(number, idNumericalBase);
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
            MsgIDType(parseToNumber(ui->idLineEdit->text())),
            ui->nameLineEdit->text(),
            QColor(ui->colorLineEdit->text())
            );
}

void MsgIDMappingAddDialog::on_numericallFormatComboBox_currentIndexChanged(
        int index
        )
{
    int enteredNumber =parseToNumber(ui->idLineEdit->text());
    ui->idLineEdit->setInputMask(inputMasks.at(index));
    ui->idLineEdit->setText(parseToString(enteredNumber));
    ui->idLineEdit->setFocus();
    ui->idLineEdit->setCursorPosition(0);
    ui->idLineEdit->selectAll();
}
