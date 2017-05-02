#include "SysOverviewTextLabel.h"

#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

SysOverviewTextLabel::SysOverviewTextLabel(
        const QString &text,
        QGraphicsItem *parent
        ) :
    QGraphicsSimpleTextItem(text,parent),
    editable(false),
    doubleClicked(false)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
}

SysOverviewTextLabel::~SysOverviewTextLabel()
{

}

void SysOverviewTextLabel::setEditable(const bool enable)
{
    editable(enable);
    setFlag(QGraphicsItem::ItemIsMovable,enable);
}

bool SysOverviewTextLabel::isEditable() const
{
    return editable;
}

void SysOverviewTextLabel::textEdit()
{
    if(editable)
    {
        bool ok;
        //ToDO... Find a way to open the dialog in the current position...
        QString inputText = QInputDialog::getText(
                this->scene()->views().at(0)->parentWidget(),
                QString("Object text"),
                QString("Text:"),
                QLineEdit::Normal,
                text(),
                &ok
                );

        if (ok && !inputText.isEmpty())
        {
            setText(inputText);
        }
    }
}


void SysOverviewTextLabel::contextMenuEvent(
        QGraphicsSceneContextMenuEvent *event
        )
{
}

void SysOverviewTextLabel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if(editable)
    {
        setCursor(QCursor(Qt::ClosedHandCursor));
    {
}

void SysOverviewTextLabel::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if(editable)
    {
        setCursor(QCursor(Qt::OpenHandCursor));
        if(doubleClicked)
        {
            textEdit();
        }
    }

    if(doubleClicked)
    {
       doubleClicked  = false;
    }
}

void SysOverviewTextLabel::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    doubleClicked = true;
}

void SysOverviewTextLabel::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(editable)
    {
        setCursor(QCursor(Qt::OpenHandCursor));
    }
}

void SysOverviewTextLabel::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(editable)
    {
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

