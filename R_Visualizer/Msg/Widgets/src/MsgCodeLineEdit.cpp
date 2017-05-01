#include "MsgCodeLineEdit.h"
#include "ui_msgcodelineedit.h"

#include <QString>
#include <QColor>
#include <QColor>
#include <QTimer>

#include "IMsgCodeMappingManager.h"

MsgCodeLineEdit::MsgCodeLineEdit(
        /* IMsgCodeMappingManager *msgCodeMappingManager, */
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgCodeLineEdit),
    msgCodeMappingManager(Q_NULLPTR)
{
    ui->setupUi(this);

    connect(
            ui->codeLineEdit,
            &QLineEdit::returnPressed,
            this,
            &MsgCodeLineEdit::sgnl_EditingFinished
           );
}

MsgCodeLineEdit::~MsgCodeLineEdit()
{
    delete ui;
}

int MsgCodeLineEdit::convertStringToNumber(
        const QString &number
        ) const
{
    int num = 0;

    if(msgCodeMappingManager != Q_NULLPTR)
    {
        num = msgCodeMappingManager->getMsgCodeToAlias(
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

MsgCodeType MsgCodeLineEdit::getMsgCode() const
{
    return MsgCodeType(convertStringToNumber(ui->codeLineEdit->text()));
}

void MsgCodeLineEdit::setMsgCode(const MsgCodeType &msgCode)
{
    ui->codeLineEdit->setText(static_cast<QString>(msgCode));
    QTimer::singleShot(0,ui->codeLineEdit,SLOT(selectAll()));
    QTimer::singleShot(0,ui->codeLineEdit,SLOT(setFocus()));
}

void MsgCodeLineEdit::setCompleter(QCompleter *completer)
{
    ui->codeLineEdit->setCompleter(completer);
}

void MsgCodeLineEdit::setMappingManager(
        IMsgCodeMappingManager *msgCodeMappingManager
        )
{
    this->msgCodeMappingManager = msgCodeMappingManager;

    if(backGroundColorChangerConnection)
    {
        disconnect(backGroundColorChangerConnection);
    }

    if(msgCodeMappingManager != Q_NULLPTR)
    {
        backGroundColorChangerConnection =
            connect(
                ui->codeLineEdit,
                &QLineEdit::textChanged,
                this,
                &MsgCodeLineEdit::codeLineEditTextChanged
               );
    }
}

void MsgCodeLineEdit::codeLineEditTextChanged(const QString &arg1)
{
    QColor newBackground;

    if(msgCodeMappingManager != Q_NULLPTR)
    {
        newBackground = msgCodeMappingManager->getColorToAlias(arg1);
    }

    if(!newBackground.isValid())
    {
        newBackground = QColor(Qt::white);
    }

    ui->codeLineEdit->setStyleSheet(
            QString("QLineEdit { background : %1;}")
            .arg(newBackground.name())
            );
}
