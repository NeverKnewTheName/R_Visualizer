#include "idlineedit.h"

#include <QString>
#include <QColor>

#include "IMsgIDMappingManager.h"

#include <QDebug>

IDLineEdit::IDLineEdit( QWidget *parent ) :
    QLineEdit(parent),
    msgIDMappingManager(Q_NULLPTR)
    /* msgIDAliasCompleter(Q_NULLPTR) */
{
}

IDLineEdit::IDLineEdit(
        const IMsgIDMappingManager *msgIDMappingManager,
        QCompleter *msgIDAliasCompleter,
        QWidget *parent
        ) :
    QLineEdit(parent),
    msgIDMappingManager(msgIDMappingManager)
    /* msgIDAliasCompleter(msgIDAliasCompleter) */
{
    connectMsgIDMapping();
    setCompleter(msgIDAliasCompleter);
}

IDLineEdit::~IDLineEdit()
{
}

void IDLineEdit::setMsgIDMapping(const IMsgIDMappingManager *msgIDMappingManagerManager)
{
    this->msgIDMappingManager = msgIDMappingManagerManager;
    connectMsgIDMapping();
}

MsgIDType IDLineEdit::getMsgID() const
{
    const QString &idNameText = text();
    MsgIDType retrievedID = convertTextToMsgID(idNameText);
    qDebug() << "IDLineEdit getID: " << static_cast<QString>(retrievedID);

    return retrievedID;
}

void IDLineEdit::connectMsgIDMapping()
{
    if(msgIDMappingManager == Q_NULLPTR)
    {
        return;
    }
    if(colorizeLineEditConnection)
    {
        QObject::disconnect(colorizeLineEditConnection);
    }
    colorizeLineEditConnection = connect(
        this,
        &QLineEdit::textChanged, [=](const QString &text){
            QColor color = msgIDMappingManager->getColorToAlias(text);
            QString colorName("white");
            if(color.isValid())
            {
               colorName = color.name();
            }
            setStyleSheet(QString("background: %1").arg(colorName));
        }
        );
}

MsgIDType IDLineEdit::convertTextToMsgID(const QString &text) const
{
    bool conversionOK;
    MsgIDType retrievedID(
            text.toInt(
                &conversionOK,
                (text.startsWith("0x")) ? 16 : 0
                )
            );

    /* If the Conversion failed (e.g. the entered value is neither a base 16 or
     * 10 integer, the IDModel that is used for completion is queried for the
     * editor content
     */
    if(!conversionOK)
    {
        if(msgIDMappingManager != Q_NULLPTR)
        {
            retrievedID = msgIDMappingManager->getMsgIDToAlias(text);
        }
        else
        {
            retrievedID = MsgIDType(0);
        }
    }
    return retrievedID;
}
