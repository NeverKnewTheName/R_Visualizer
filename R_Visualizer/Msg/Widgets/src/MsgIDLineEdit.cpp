#include "MsgIDLineEdit.h"
#include "ui_msgidlineedit.h"

#include <QString>
#include <QColor>
#include <QColor>

#include "IMsgIDMappingManager.h"

MsgIDLineEdit::MsgIDLineEdit(
        IMsgIDMappingManager *msgIDMappingManager,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgIDLineEdit),
    msgIDMappingManager(msgIDMappingManager)
{
    ui->setupUi(this);
}

MsgIDLineEdit::~MsgIDLineEdit()
{
    delete ui;
}

int MsgIDLineEdit::convertStringToNumber(
        const QString &number
        ) const
{
    const int num = msgIDMappingManager->getMsgIDToAlias(
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

MsgIDType MsgIDLineEdit::getMsgID() const
{
    return MsgIDType(convertStringToNumber(ui->idLineEdit->text()));
}

void MsgIDLineEdit::setMsgID(const MsgIDType &msgID)
{
    ui->idLineEdit->setText(static_cast<QString>(msgID));
}

void MsgIDLineEdit::on_idLineEdit_textChanged(const QString &arg1)
{
}
