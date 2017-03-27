#include "codelineedit.h"

#include <QString>
#include <QColor>

#include "MessageConfig.h"

#include <QDebug>

CodeLineEdit::CodeLineEdit( QWidget *parent ) :
    QLineEdit(parent),
    msgConfig(nullptr)
{
}

CodeLineEdit::CodeLineEdit( const MessageConfig *msgConfig, QWidget *parent ) :
    QLineEdit(parent),
    msgConfig(msgConfig)
{
    if(msgConfig != nullptr)
    {
        msgConfigChanged();
    }
}

CodeLineEdit::~CodeLineEdit()
{
}

void CodeLineEdit::setMsgConfig(const MessageConfig *msgConfig)
{
    this->msgConfig = msgConfig;
    if(msgConfig != nullptr)
    {
        msgConfigChanged();
    }
}

MsgCodeType CodeLineEdit::getCode() const
{
    const QString &codeTypeText = text();
    bool conversionOK;
    MsgCodeType retrievedCode = codeTypeText.toInt(&conversionOK, (codeTypeText.startsWith("0x")) ? 16 : 0);

    if(!conversionOK)
    {
        if(msgConfig != nullptr)
        {
            retrievedCode = msgConfig->getCodeToName(codeTypeText);
        }
        else
        {
            retrievedCode = 0;
        }
    }

    qDebug() << "CodeLineEdit getCode(): " << retrievedCode;

    return retrievedCode;
}

void CodeLineEdit::msgConfigChanged()
{
    if(colorizeLineEditConnection)
    {
        QObject::disconnect(colorizeLineEditConnection);
    }
    QCompleter *codeCompleter = msgConfig->createCodeNameCompleter(this);
    setCompleter(codeCompleter);
    colorizeLineEditConnection = connect(this, &QLineEdit::textChanged, [=](const QString &text){
            QColor color = msgConfig->getColorToCodeName(text);
            QString colorName("white");
            if(color.isValid())
            {
                colorName = color.name();
            }
            this->setStyleSheet(QString("background: %1").arg(colorName));
            });
}
