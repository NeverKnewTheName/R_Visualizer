//#ifndef SYSOVRVOBJCONTAINER_H
//#define SYSOVRVOBJCONTAINER_H

//#include <QGraphicsItem>
//#include <QSharedPointer>
//#include <QPointF>

//#include "sysovrvobject.h"
//#include "Msg.h"

//class SysOvrvObjContainer : public QGraphicsItem
//{
//public:
//    SysOvrvObjContainer(const MsgIDType ContainerMsgID, QGraphicsItem *parent = Q_NULLPTR);
//    SysOvrvObjContainer(const SysOvrvObjContainer &ToCopy);
//    SysOvrvObjContainer(SysOvrvObjContainer &&ToMove);

//    ~SysOvrvObjContainer();

//    void AddSysOvrvObj(const SysOvrvObject *const SysOvrvObjToAdd);
//    void RemoveSysOvrvObj(const SysOvrvObject *const SysOvrvObjToRemove);
//    void EditSysOvrvObj(const SysOvrvObject *const SysOvrvObjToEdit);

//    const SysOvrvObject * const getSysOvrvObjAtPos(const QPointF &pos) const;

//    // QGraphicsItem interface
//public:
//    QRectF boundingRect() const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

//protected:
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
//    void focusInEvent(QFocusEvent *event);
//    void focusOutEvent(QFocusEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

//private:
//    MsgIDType ContainerMsgID;
//    bool showFrame;
//    bool DoubleClickDetected;
//};

//#endif // SYSOVRVOBJCONTAINER_H
