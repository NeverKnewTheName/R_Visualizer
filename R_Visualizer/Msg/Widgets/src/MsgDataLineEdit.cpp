#include "MsgDataLineEdit.h"
#include "ui_msgdatalineedit.h"

#include "IMsgDataMappingManager.h"

#include <QDebug>

MsgDataLineEdit::MsgDataLineEdit(
        IMsgDataMappingManager *msgDataMappingManager,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgDataLineEdit),
    msgDataMappingManager(msgDataMappingManager),
    formatData({
            std::make_tuple(
                    16,
                    2,
                    QString("0x"),
                    QString(
                      "hh hh hh hh hh hh hh"
                      ),
                    QString("HEX")
                    ),
            std::make_tuple(
                    10,
                    3,
                    QString(" D"),
                    QString(
                      "000 000 000 000 000 000 000"
                      ),
                    QString("DEC Data")
                    ),
            std::make_tuple(
                    10,
                    0,
                    QString(" V"),
                    QString(
                      "00000000000000000"
                      ),
                    QString("DEC Value")
                    ),
            std::make_tuple(
                    2,
                    8,
                    QString("0b"),
                    QString(
                      "bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb\\ bbbbbbbb"
                      ),
                    QString("BIN")
                    )
            }),
            currentFormatIndex(0)
{
    ui->setupUi(this);

    for(auto &tuple : formatData)
    {
        ui->numFormatComboBox->addItem(std::get<4>(tuple));
    }
}

MsgDataLineEdit::~MsgDataLineEdit()
{
    delete ui;
}

QString MsgDataLineEdit::convertFormat(
        QString &number,
        const int oldFormatIndex,
        const int newFormatIndex
        )
{
    const int oldBase = std::get<0>(formatData.at(oldFormatIndex));
    const int newBase = std::get<0>(formatData.at(newFormatIndex));
    const int oldFieldWidth = std::get<1>(formatData.at(oldFormatIndex));
    const int newFieldWidth = std::get<1>(formatData.at(newFormatIndex));

    number = number.simplified(); //remove leading and trailing whitespace

    qDebug() << "Simplified number: " << number;
    QStringList bytes;

    if(oldFieldWidth == 0)
    {
        //There is no whitespace separated formatting
        int num = number.toInt(0,oldBase);

        while(num)
        {
            qDebug() << "num: " << num;
            bytes.prepend(
                        QString::number(
                            num & 0xFFu,
                            oldBase
                            )
                        );
            num = num >> 8;
        }
    }
    else
    {
        bytes = number.split(' '); //split into bytes
    }

    qDebug() << "Splits: " << bytes;

    if(newFieldWidth == 0)
    {
        //parse the bytes to a unformatted number

        int num = 0;
        int cntr = bytes.size();
        for(QString &byte : bytes)
        {
           cntr--;
           num += byte.toInt(0,oldBase) << 8 * cntr;
        }

        number = QString::number(num,newBase);
    }
    else
    {
        // The number string needs formatting
        for(QString &byte : bytes)
        {
            byte = QString("%1").arg(
                    byte.toInt(0,oldBase),
                    newFieldWidth,
                    newBase,
                    QLatin1Char('0')
                    );
        }

        number = bytes.join(' ');
    }
    return number;
}

int MsgDataLineEdit::convertToNumber(const QString &number) const
{
}

void MsgDataLineEdit::on_dataLineEdit_textChanged(const QString &arg1)
{

}

void MsgDataLineEdit::on_numFormatComboBox_currentIndexChanged(int index)
{
    QString number = ui->dataLineEdit->text();

    qDebug() << "Old Number: " << number;

    convertFormat(number,currentFormatIndex,index);

    qDebug() << "New Number: " << number;

    currentFormatIndex = index;

    const QString &formatSpec = std::get<2>(formatData.at(index));
    const QString &inputMask = std::get<3>(formatData.at(index));

    ui->dataLineEdit->setInputMask(inputMask);
    ui->dataLineEdit->setText(number);
    ui->numPrefixLabel->setText(formatSpec);

    qDebug() << "Set Text: " << ui->dataLineEdit->text();

}
