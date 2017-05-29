#include "codelineedit.h"

#include <QString>
#include <QColor>

#include "IMsgCodeMappingManager.h"

#include <QDebug>

CodeLineEdit::CodeLineEdit( QWidget *parent ) :
    QLineEdit(parent),
    msgCodeMappingManager(Q_NULLPTR)
{
}

CodeLineEdit::CodeLineEdit(
        const IMsgCodeMappingManager *msgCodeMappingManagerManager,
        QCompleter *msgCodeAliasCompleter,
        QWidget *parent
        ) :
    QLineEdit(parent),
    msgCodeMappingManager(msgCodeMappingManager)
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

void CodeLineEdit::setMsgCodeMapping(const IMsgCodeMappingManager *msgCodeMappingManagerManager)
{
    this->msgCodeMappingManager = msgCodeMappingManagerManager;
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
                QColor color = msgCodeMappingManager->getColorToAlias(text);
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
        if(msgCodeMappingManager != Q_NULLPTR)
        {
            retrievedCode = msgCodeMappingManager->getMsgCodeToAlias(text);
        }
        else
        {
            retrievedCode = MsgCodeType(0);
        }
    }
    return retrievedCode;
}
