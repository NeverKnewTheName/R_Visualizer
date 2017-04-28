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
    if(num)
    {
        return num;
    }
    else
    {
        return AbstractMsgFieldLineEdit::convertStringToNumber(number);
    }
}

void MsgIDLineEdit::on_idLineEdit_textChanged(const QString &arg1)
{
}
