#include "AbstractMsgFieldLineEdit.h"

AbstractMsgFieldLineEdit::AbstractMsgFieldLineEdit()
{

}

int AbstractMsgFieldLineEdit::convertStringToNumber(
        const QString &number
        ) const
{
    int base;
    QString num(number.simplified());

    if(num.startsWith("0x"))
    {
        base = 16;
    }
    else if(num.startsWith("0b"))
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
