#include "codelineedit.h"

#include <QString>
#include <QColor>

#include "IMsgCodeMapping.h"

#include <QDebug>

CodeLineEdit::CodeLineEdit( QWidget *parent ) :
    QLineEdit(parent),
    msgCodeMapping(Q_NULLPTR)
{
}

CodeLineEdit::CodeLineEdit(
        const IMsgCodeMapping *msgCodeMapping,
        QCompleter *msgCodeAliasCompleter,
        QWidget *parent
        ) :
    QLineEdit(parent),
    msgCodeMapping(msgCodeMapping)
{
    if(msgCodeAliasCompleter != Q_NULLPTR)
    {
        setCompleter(msgCodeAliasCompleter);
    }
    connectMsgCodeMapping();
}

CodeLineEdit::~CodeLineEdit()
{
}

void CodeLineEdit::setMsgCodeMapping(const IMsgCodeMapping *msgCodeMapping)
{
    this->msgCodeMapping = msgCodeMapping;
    connectMsgCodeMapping();
}

MsgCodeType CodeLineEdit::getMsgCode() const
{
    const QString &codeTypeText = text();

    MsgCodeType retrievedCode = convertTextToMsgCode(codeTypeText);

    qDebug() << "CodeLineEdit getMsgCode(): "
        << static_cast<QString>(retrievedCode);

    return retrievedCode;
}

void CodeLineEdit::connectMsgCodeMapping()
{
    if(colorizeLineEditConnection)
    {
        QObject::disconnect(colorizeLineEditConnection);
    }
    colorizeLineEditConnection = connect(
            this,
            &QLineEdit::textChanged, [=](const QString &text){
                QColor color = msgCodeMapping->getColorToAlias(text);
                QString colorName("white");
                if(color.isValid())
                {
                    colorName = color.name();
                }
                this->setStyleSheet(QString("background: %1").arg(colorName));
            }
        );
}

MsgCodeType CodeLineEdit::convertTextToMsgCode(const QString &text) const
{
    bool conversionOK;
    MsgCodeType retrievedCode(
            text.toInt(
                &conversionOK,
                (text.startsWith("0x")) ? 16 : 0
                )
            );

    if(!conversionOK)
    {
        if(msgCodeMapping != Q_NULLPTR)
        {
            retrievedCode = msgCodeMapping->getMsgCodeToAlias(text);
        }
        else
        {
            retrievedCode = MsgCodeType(0);
        }
    }
    return retrievedCode;
}
