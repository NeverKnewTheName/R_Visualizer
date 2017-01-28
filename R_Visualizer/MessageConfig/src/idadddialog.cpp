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
    inputMasks << "\\0\\xhhhh"/*HEX*/
               << "00000"/*DEC*/
               << "\\0\\b bbbb\\ bbbb\\ bbbb\\ bbbb"/*BIN*/;

    QStringList items;
    items << "Hex" << "Dec" << "Bin";
    ui->numericallFormatComboBox->addItems(items);
}

IDAddDialog::~IDAddDialog()
{
    delete ui;
}

int IDAddDialog::parseToNumber(QString numericalString)
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

QString IDAddDialog::parseToString(int number)
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
    emit commit(this->parseToNumber(ui->idLineEdit->text()), ui->nameLineEdit->text(), QColor(ui->colorLineEdit->text()));
}

void IDAddDialog::on_numericallFormatComboBox_currentIndexChanged(int index)
{
    int enteredNumber = this->parseToNumber(ui->idLineEdit->text());
    ui->idLineEdit->setInputMask(inputMasks.at(index));
    ui->idLineEdit->setText(this->parseToString(enteredNumber));
    ui->idLineEdit->setFocus();
    ui->idLineEdit->setCursorPosition(0);
    ui->idLineEdit->selectAll();
}
