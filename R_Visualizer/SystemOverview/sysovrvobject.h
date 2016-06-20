#ifndef SYSOVRVOBJECT_H
#define SYSOVRVOBJECT_H

#include <QGraphicsItem>
#include <QHash>


class SysOvrvObject : public QGraphicsItem
{
public:
    explicit SysOvrvObject();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool pressed;

    QColor getMyColor() const;
    void setMyColor(const QColor &value);

    QHash<QString, SysOvrvObject *> getObjStore() const;
    void setObjStore(const QHash<QString, SysOvrvObject *> &value);

    QString getObjName() const;
    void setObjName(const QString &value);

    void setShape(int shape);

private:
    QString objName;
    QColor myColor;
    int shapeType;
    QHash<QString, SysOvrvObject *> objStore;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

};

#endif // SYSOVRVOBJECT_H
