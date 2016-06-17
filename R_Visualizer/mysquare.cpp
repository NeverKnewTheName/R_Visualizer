#include "mysquare.h"

MySquare::MySquare()
{
    myColor = QColor(Qt::red);
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
    QBrush brush(myColor);

    if(pressed)
    {
        brush.setColor(myColor.darker());
    }

    painter->fillRect(rect, brush);
    painter->drawEllipse(rect);
    painter->drawRect(rect);
}

QColor MySquare::getMyColor() const
{
    return myColor;
}

void MySquare::setMyColor(const QColor &value)
{
    myColor = value;
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
