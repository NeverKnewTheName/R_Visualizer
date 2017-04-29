#include "MsgIDLineEdit.h"
#include "ui_msgidlineedit.h"

#include <QString>
#include <QColor>
#include <QColor>

#include "IMsgIDMappingManager.h"

MsgIDLineEdit::MsgIDLineEdit(
        /* IMsgIDMappingManager *msgIDMappingManager, */
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgIDLineEdit),
    msgIDMappingManager(Q_NULLPTR)
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
    int num = 0;

    if(msgIDMappingManager != Q_NULLPTR)
    {
        num = msgIDMappingManager->getMsgIDToAlias(
                    number
                    ).getPrimitiveData();
    }
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

void MsgIDLineEdit::setCompleter(QCompleter *completer)
{
    ui->idLineEdit->setCompleter(completer);
}

void MsgIDLineEdit::setMappingManager(
        IMsgIDMappingManager *msgIDMappingManager
        )
{
    this->msgIDMappingManager = msgIDMappingManager;

    if(backGroundColorChangerConnection)
    {
        disconnect(backGroundColorChangerConnection);
    }

    if(msgIDMappingManager != Q_NULLPTR)
    {
        backGroundColorChangerConnection =
            connect(
                ui->idLineEdit,
                &QLineEdit::textChanged,
                this,
                &MsgIDLineEdit::idLineEditTextChanged
               );
    }
}

void MsgIDLineEdit::idLineEditTextChanged(const QString &arg1)
{
    QColor newBackground;

    if(msgIDMappingManager != Q_NULLPTR)
    {
        newBackground = msgIDMappingManager->getColorToAlias(arg1);
    }

    if(!newBackground.isValid())
    {
        newBackground = QColor(Qt::white);
    }

    ui->idLineEdit->setStyleSheet(
            QString("QLineEdit { background : %1;}")
            .arg(newBackground.name())
            );
}
