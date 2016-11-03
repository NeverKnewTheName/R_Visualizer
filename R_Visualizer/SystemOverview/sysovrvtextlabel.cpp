#include "sysovrvtextlabel.h"

#include <QInputDialog>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QGraphicsSceneHoverEvent>

#include <QDebug>

SysOvrvTextLabel::SysOvrvTextLabel(QGraphicsItem *parent) :
    QGraphicsSimpleTextItem(parent),
    m_bDoubleClicked(false),
    m_bEditable(false)
{

    setFlag(QGraphicsItem::ItemIsFocusable);
}

void SysOvrvTextLabel::setEditable(bool enable)
{
    m_bEditable = enable;
    setFlag(QGraphicsItem::ItemIsMovable,enable);
}

void SysOvrvTextLabel::textEdit()
{
    bool ok;
    QString inputText = QInputDialog::getText(this->scene()->views().at(0)->parentWidget(), QString("Object text"),
                                         QString("Text:"), QLineEdit::Normal,
                                         text(), &ok);
    if (ok && !inputText.isEmpty())
        setText(inputText);
}

QByteArray SysOvrvTextLabel::parseToJson() const
{
    QJsonObject jsonSysOvrvTextLableObj;
    QJsonArray objPos;

    jsonSysOvrvTextLableObj["TextLableText"] = text();
    objPos.append(QJsonValue(static_cast<double>(x())));
    objPos.append(QJsonValue(static_cast<double>(y())));
    jsonSysOvrvTextLableObj["TextLablePos"] = objPos;

    return QJsonDocument(jsonSysOvrvTextLableObj).toJson();
}

void SysOvrvTextLabel::parseFromJson(QByteArray &jsonByteArray)
{
    QJsonObject jsonSysOvrvTextLableObj = QJsonDocument::fromJson(jsonByteArray).object();;
    QJsonArray objPos = jsonSysOvrvTextLableObj["TextLablePos"].toArray();

    setText(jsonSysOvrvTextLableObj["TextLableText"].toString());
    setPos(static_cast<qreal>(objPos.at(0).toDouble(0)), static_cast<qreal>(objPos.at(1).toDouble(0)));
}

void SysOvrvTextLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void SysOvrvTextLabel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_bDoubleClicked)
    {
        m_bDoubleClicked = false;
        qDebug() << "SysOvrvTextLabel::mouseReleaseEvent DoubleClicked";
        if(m_bEditable)
        {
            textEdit();
        }
    }
}

void SysOvrvTextLabel::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_bDoubleClicked = true;
}

void SysOvrvTextLabel::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "SysOvrvTextLabel::hoverEnterEvent";
    setCursor(QCursor(Qt::SizeAllCursor));
    event->accept();
}

void SysOvrvTextLabel::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "SysOvrvTextLabel::hoverLeaveEvent";
    setCursor(QCursor(Qt::ArrowCursor));
    event->accept();
}



