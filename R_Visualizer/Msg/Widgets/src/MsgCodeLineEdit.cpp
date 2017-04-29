#include "MsgCodeLineEdit.h"
#include "ui_msgcodelineedit.h"

#include <QString>
#include <QColor>
#include <QColor>

#include "IMsgCodeMappingManager.h"

MsgCodeLineEdit::MsgCodeLineEdit(
        IMsgCodeMappingManager *msgCodeMappingManager,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgCodeLineEdit),
    msgCodeMappingManager(msgCodeMappingManager)
{
    ui->setupUi(this);
}

MsgCodeLineEdit::~MsgCodeLineEdit()
{
    delete ui;
}

int MsgCodeLineEdit::convertStringToNumber(
        const QString &number
        ) const
{
    const int num = msgCodeMappingManager->getMsgCodeToAlias(
                number
                ).getPrimitiveData();
    /**
     * checking for zero is valid here since 0 is an invalid MsgID anyway
     */
    if(num)
    {
        return num;
    }
    else
    {
        return AbstractMsgFieldLineEdit::convertStringToNumber(number);
    }
}

MsgCodeType MsgCodeLineEdit::getMsgCode() const
{
    return MsgCodeType(convertStringToNumber(ui->codeLineEdit->text()));
}

void MsgCodeLineEdit::setMsgCode(const MsgCodeType &msgCode)
{
    ui->codeLineEdit->setText(static_cast<QString>(msgCode));
}

void MsgCodeLineEdit::on_codeLineEdit_textChanged(const QString &arg1)
{

}
