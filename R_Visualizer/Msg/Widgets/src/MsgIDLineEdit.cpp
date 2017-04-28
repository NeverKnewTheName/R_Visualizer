#include "MsgIDLineEdit.h"
#include "ui_msgidlineedit.h"

#include <QString>
#include <QColor>
#include <QColor>

#include "IMsgMappingManager.h"

MsgIDLineEdit::MsgIDLineEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgIDLineEdit),
    numData({
            std::make_tuple(16, "HEX", "\\0==xhhhh"),
            std::make_tuple(10, "DEC", "0000"),
            std::make_tuple(2, "BIN", "\\0\\b bbbb\\ bbbb\\ bbbb\\ bbbb")
            })
{
    ui->setupUi(this);

    QStringList numSpecifiers;

    for(int i = 0; i < numData.size(); ++i)
    {
        numSpecifiers.append(
                std::get<1>(numData.at(i));
                );
    }

    ui->numFormatComboBox->addItems(numFormatStringList);
}

MsgIDLineEdit::~MsgIDLineEdit()
{
    delete ui;
}

int MsgIDLineEdit::convertStringToNumber(
        const QString &number
        ) const
{
    int base;
    QString num(number);

    if(num.contains("0x"))
    {
        base = 16;
    }
    else if(num.contains("0b"))
    {
        base = 2;
        num.replace(" ","").replace("0b","");
    }
    else
    {
        base = 10;
    }
    return num.toInt(0, base);
}

QString MsgIDLineEdit::convertNumberToString(
        const int number,
        const int base
        ) const
{
    return QString::number(number, base);
}

void MsgIDLineEdit::on_idLineEdit_textChanged(const QString &arg1)
{
    const int number = convertStringToNumber(arg1);

}

void MsgIDLineEdit::on_numFormatComboBox_currentIndexChanged(int index)
{
    const QString &numString = ui->idLineEdit->text();
    const int number = convertStringToNumber(numString);

    std::tie(base,formatSpec,inputMask) = numData.at(index);

    ui->idLineEdit->setInputMask(
            inputMask
            );
    const QString &newNumber = convertNumberToString(
            number,
            base
            );

    ui->idLineEdit->setText(newNumber);
    ui->idLineEdit->setFocus();
    ui->idLineEdit->setCursorPosition(0);
    ui->idLineEdit->selectAll();
}
