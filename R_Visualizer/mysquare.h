#ifndef MYSQUARE_H
#define MYSQUARE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>


class MySquare : public QGraphicsItem
{
public:
    MySquare();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool pressed;

    QColor getMyColor() const;
    void setMyColor(const QColor &value);

private:
    QColor myColor;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYSQUARE_H
