#include "sysovrvobject.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

SysOvrvObject::SysOvrvObject()
{
    pressed = false;
    myColor = QColor(Qt::gray);
    //setFlag(ItemIsMovable);
}

QRectF SysOvrvObject::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void SysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(myColor);

    if(pressed)
    {
        brush.setColor(myColor.darker());
    }

    painter->setBrush(brush);

    switch(shapeType)
    {
    case 0: // Rect
        painter->drawRect(rect);
        break;
    case 1: // Square
        rect.setY(rect.x());
        painter->drawRect(rect);
        break;
    case 2: // Circle
        painter->drawEllipse(rect);
        break;
    case 3: // Triangle
    {
        QVector<QLineF> linesTriangle;
        QPointF rectTopMiddle(rect.right() - rect.left(), rect.top());
        linesTriangle.append(QLineF(rect.bottomLeft(),rectTopMiddle));
        linesTriangle.append(QLineF(rect.bottomRight(),rectTopMiddle));
        linesTriangle.append(QLineF(rect.bottomLeft(), rect.bottomRight()));
        painter->drawLines(linesTriangle);
    }
        break;
    }

//    painter->fillRect(rect, brush);
//    painter->drawEllipse(rect);
    //painter->drawRect(rect);
}

QHash<QString, SysOvrvObject *> SysOvrvObject::getObjStore() const
{
    return objStore;
}

void SysOvrvObject::setObjStore(const QHash<QString, SysOvrvObject *> &value)
{
    objStore = value;
}

QString SysOvrvObject::getObjName() const
{
    return objName;
}

void SysOvrvObject::setObjName(const QString &value)
{
    objName = value;
}

void SysOvrvObject::setShape(int shape)
{
    shapeType = shape;
    this->update();
}

void SysOvrvObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void SysOvrvObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void SysOvrvObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}
