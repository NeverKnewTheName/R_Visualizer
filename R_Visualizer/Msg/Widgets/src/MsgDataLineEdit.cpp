#include "MsgDataLineEdit.h"
#include "ui_msgdatalineedit.h"

#include "IMsgDataMappingManager.h"

#include <QFocusEvent>
#include <QTimer>

#include <QDebug>

MsgDataLineEdit::MsgDataLineEdit(
        /* IMsgDataMappingManager *msgDataMappingManager, */
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgDataLineEdit),
    msgDataMappingManager(Q_NULLPTR),
    lineEditCursorHelper(new LineEditCursorHelper(this)),
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

    connect(
            ui->dataLineEdit,
            &QLineEdit::returnPressed,
            this,
            &MsgDataLineEdit::sgnl_EditingFinished
           );

    for(auto &tuple : formatData)
    {
        ui->numFormatComboBox->addItem(std::get<4>(tuple));
    }

    lineEditCursorHelper->installHelper(ui->dataLineEdit);
}

MsgDataLineEdit::~MsgDataLineEdit()
{
    delete ui;
}

MsgDataType MsgDataLineEdit::getMsgData() const
{
    QString number = ui->dataLineEdit->text().simplified();
    MsgDataType msgData;

    if(number.isEmpty())
    {
        return msgData;
    }

    int base = std::get<0>(formatData.at(currentFormatIndex));

    const int fieldWidth = std::get<1>(formatData.at(currentFormatIndex));
    if(fieldWidth == 0)
    {
        number = convertFormat(number, currentFormatIndex,0);
        base = std::get<0>(formatData.at(0));
    }

    QStringList bytes = number.split(' ');

    for(const QString &byte : bytes)
    {
        msgData.append(MsgDataByteType(byte.toInt(0,base)));
    }

    return msgData;
}

void MsgDataLineEdit::setMsgData(const MsgDataType &msgData)
{
    ui->numFormatComboBox->setCurrentIndex(0);
    QString msgDataAsString;
    for(const MsgDataByteType &byte : msgData)
    {
        msgDataAsString.append(QString::number(byte.getPrimitiveData(),16) + " ");
    }
    ui->dataLineEdit->setText(msgDataAsString.trimmed());
    QTimer::singleShot(0,ui->dataLineEdit,SLOT(setFocus()));
}

QString MsgDataLineEdit::convertFormat(
        QString &number,
        const int oldFormatIndex,
        const int newFormatIndex
        ) const
{
    number = number.simplified(); //remove leading and trailing whitespace

    if(number.isEmpty())
    {
        return number;
    }
    const int oldBase = std::get<0>(formatData.at(oldFormatIndex));
    const int newBase = std::get<0>(formatData.at(newFormatIndex));
    const int oldFieldWidth = std::get<1>(formatData.at(oldFormatIndex));
    const int newFieldWidth = std::get<1>(formatData.at(newFormatIndex));

    //qDebug() << "Simplified number: " << number;
    QStringList bytes;

    if(oldFieldWidth == 0)
    {
        //There is no whitespace separated formatting
        int num = number.toInt(0,oldBase);

        while(num)
        {
            //qDebug() << "num: " << num;
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

    //qDebug() << "Splits: " << bytes;

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
    /* return numberFromBytes( */
    /*         extractBytes( */
    /*             number, */
    /*             oldBase, */
    /*             oldFieldWidth */
    /*             ), */
    /*         oldBase, */
    /*         newBase, */
    /*         newFieldWidth */
    /*         ); */
}

QStringList MsgDataLineEdit::extractBytes(
        QString &number,
        int base,
        int width
        )
{
    QStringList bytes;

    if(width == 0)
    {
        //There is no whitespace separated formatting
        int num = number.toInt(0,base);

        while(num)
        {
            //qDebug() << "num: " << num;
            bytes.prepend(
                        QString::number(
                            num & 0xFFu,
                            base
                            )
                        );
            num = num >> 8;
        }
    }
    else
    {
        bytes = number.split(' '); //split into bytes
    }

    return bytes;
}

QString MsgDataLineEdit::numberFromBytes(
        QStringList bytes,
        int oldBase,
        int newBase,
        int width
        )
{
    QString number;

    if(width == 0)
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
                    width,
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

    //qDebug() << "Old Number: " << number;

    convertFormat(number,currentFormatIndex,index);

    //qDebug() << "New Number: " << number;

    currentFormatIndex = index;

    const QString &formatSpec = std::get<2>(formatData.at(index));
    const QString &inputMask = std::get<3>(formatData.at(index));

    ui->dataLineEdit->setInputMask(inputMask);
    ui->dataLineEdit->setText(number);
    ui->numPrefixLabel->setText(formatSpec);
    ui->dataLineEdit->setFocus();
    ui->dataLineEdit->setCursorPosition(0);
    /* ui->dataLineEdit->selectAll(); */

    //qDebug() << "Set Text: " << ui->dataLineEdit->text();

}


void MsgDataLineEdit::focusInEvent(QFocusEvent *event)
{
    ui->dataLineEdit->setFocus();
}
