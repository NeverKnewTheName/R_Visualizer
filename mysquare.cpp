#include "mysquare.h"

MySquare::MySquare()
{
    pressed = false;
    setFlag(ItemIsMovable);
}

QRectF MySquare::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void MySquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::blue);

    if(pressed)
    {
        brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::green);
    }

    painter->fillRect(rect, brush);
    painter->drawEllipse(rect);
    painter->drawRect(rect);
}

void MySquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MySquare::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
