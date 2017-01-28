#include "sysovrvtextlabel.h"

#include <QInputDialog>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QGraphicsSceneHoverEvent>

#include <QMenu>


#include "sysovrvobject.h"

#include <QDebug>

SysOvrvTextLabel::SysOvrvTextLabel(QGraphicsItem *parent) :
    QGraphicsSimpleTextItem(parent),
    m_bDoubleClicked(false),
    m_bEditable(true)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
}

SysOvrvTextLabel::SysOvrvTextLabel(const QString &text, QGraphicsItem *parent) :
    QGraphicsSimpleTextItem(parent),
    m_bDoubleClicked(false),
    m_bEditable(true)
{
    setText(text);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

SysOvrvTextLabel::SysOvrvTextLabel(const SysOvrvTextLabel &ToCopy) :
    QGraphicsSimpleTextItem(ToCopy.parentItem()),
    m_bDoubleClicked(ToCopy.m_bDoubleClicked),
    m_bEditable(ToCopy.m_bEditable)
{
    setPos(ToCopy.pos());
    setText(ToCopy.text());
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void SysOvrvTextLabel::setEditable(bool enable)
{
    m_bEditable = enable;
}

void SysOvrvTextLabel::textEdit()
{
    bool ok;
    //ToDO... Find a way to open the dialog in the current position...
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
    Q_UNUSED(event)
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void SysOvrvTextLabel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(QCursor(Qt::OpenHandCursor));
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
    setCursor(QCursor(Qt::OpenHandCursor));
    event->accept();
}

void SysOvrvTextLabel::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "SysOvrvTextLabel::hoverLeaveEvent";
    setCursor(QCursor(Qt::ArrowCursor));
    event->accept();
}

int SysOvrvTextLabel::type() const
{
    return Type;
}


void SysOvrvTextLabel::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *removeAction = menu.addAction("Remove");
    QAction *editAction = menu.addAction("Edit");

    SysOvrvObject * sysOvrvParent = dynamic_cast<SysOvrvObject*>(parentItem());
    if(sysOvrvParent != Q_NULLPTR)
    {
        QAction::connect(removeAction, &QAction::triggered, [this] () {
            this->setParentItem(Q_NULLPTR);
            delete this;
        } );
    }
    else
    {
        qDebug() << "TextLabel has no parent... FAILURE!";
    }
    QAction::connect(editAction, &QAction::triggered, [this] () {
        textEdit();
    } );
    menu.exec(event->screenPos());
}

void SysOvrvTextLabel::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_bEditable)
    {
        qreal distX = event->pos().x() - event->lastPos().x();
        qreal distY = event->pos().y() - event->lastPos().y();
        moveBy(distX,distY);
    }
    QGraphicsSimpleTextItem::mouseMoveEvent(event);
}
