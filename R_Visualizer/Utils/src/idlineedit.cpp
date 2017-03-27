#include "idlineedit.h"

#include <QString>
#include <QColor>

#include "MessageConfig.h"

#include <QDebug>

IDLineEdit::IDLineEdit( QWidget *parent ) :
    QLineEdit(parent),
    msgConfig(nullptr)
{
}

IDLineEdit::IDLineEdit( const MessageConfig *msgConfig, QWidget *parent ) :
    QLineEdit(parent),
    msgConfig(msgConfig)
{
    if(msgConfig != nullptr)
    {
        msgConfigChanged();
    }
}

IDLineEdit::~IDLineEdit()
{
}

void IDLineEdit::setMsgConfig(const MessageConfig *msgConfig)
{
    this->msgConfig = msgConfig;
    if(msgConfig != nullptr)
    {
        msgConfigChanged();
    }
}

MsgIDType IDLineEdit::getID() const
{
    const QString &idNameText = text();
    bool conversionOK;
    MsgIDType retrievedID = idNameText.toInt(&conversionOK, (idNameText.startsWith("0x")) ? 16 : 0);

    /* If the Conversion failed (e.g. the entered value is neither a base 16 or 10 integer,
     * the IDModel that is used for completion is queried for the editor content
     */
    if(!conversionOK)
    {
        if(msgConfig != nullptr)
        {
            retrievedID = msgConfig->getIDToName(idNameText);
        }
        else
        {
            retrievedID = 0;
        }
    }

    qDebug() << "IDLineEdit getID: " << retrievedID;

    return retrievedID;
}

void IDLineEdit::msgConfigChanged()
{
    if(colorizeLineEditConnection)
    {
        QObject::disconnect(colorizeLineEditConnection);
    }
    QCompleter *idCompleter = msgConfig->createIDNameCompleter(this);
    setCompleter(idCompleter);
    colorizeLineEditConnection = connect(this, &QLineEdit::textChanged, [=](const QString &text){
            QColor color = msgConfig->getColorToIDName(text);
            QString colorName("white");
            if(color.isValid())
            {
               colorName = color.name();
            }
            this->setStyleSheet(QString("background: %1").arg(colorName));
            });
}
