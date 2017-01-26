//#include "sysovrvobjcontainer.h"

//#include <QMenu>
//#include <QAction>


//#include <QDebug>

//SysOvrvObjContainer::SysOvrvObjContainer(const MsgIDType ContainerMsgID, QGraphicsItem *parent) :
//    QGraphicsItem(parent),
//    ContainerMsgID(ContainerMsgID),
//    showFrame(true),
//    DoubleClickDetected(false)
//{

//}

//SysOvrvObjContainer::SysOvrvObjContainer(const SysOvrvObjContainer &ToCopy) :
//    QGraphicsItem(ToCopy.parentItem()),
//    ContainerMsgID(ToCopy.ContainerMsgID),
//    showFrame(ToCopy.showFrame),
//    DoubleClickDetected(ToCopy.DoubleClickDetected)
//{
//}

//const SysOvrvObject * const SysOvrvObjContainer::getSysOvrvObjAtPos(const QPointF &pos) const
//{
////    QGraphicsItem * ItemAtPos = itemAt(pos);
////    qgraphicsitem_cast<SysOvrvObject*>(itemAt(event->pos()));
//}


//QRectF SysOvrvObjContainer::boundingRect() const
//{
//}

//void SysOvrvObjContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//}

//void SysOvrvObjContainer::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
//{
////    QMenu menu(this);
////    currentMousePos = mapToScene(event->pos());
////    currentObject = parentWidget();

////    if(currentObject == NULL)
////    {
////        QAction * actionAdd = menu.addAction("Add Object");
//////        connect(actionAdd, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::addObject);
////    }
////    else
////    {
////        while(currentObject->parentItem() != NULL)
////            currentObject = qgraphicsitem_cast<SysOvrvObject*>(currentObject->parentItem());

////        QAction * actionRmv = menu.addAction("Remove Object");
////        QAction * actionUpdt = menu.addAction("Update Object");
////        QAction * duplicateSelectedObject = menu.addAction("Duplicate Object");
//////        connect(actionRmv, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::rmvObject);
//////        connect(actionUpdt, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::updtObject);
//////        connect(duplicateSelectedObject, &QAction::triggered, this->sysOvrvObjStore, &SysOvrvObjectStore::duplicateObject);
////    }

////    menu.exec(event->globalPos());
//}

//void SysOvrvObjContainer::focusInEvent(QFocusEvent *event)
//{
//}

//void SysOvrvObjContainer::focusOutEvent(QFocusEvent *event)
//{
//}

//void SysOvrvObjContainer::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//}

//void SysOvrvObjContainer::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
//{
//}

//void SysOvrvObjContainer::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//}

//void SysOvrvObjContainer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//}

//void SysOvrvObjContainer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    if(DoubleClickDetected)
//    {
//        DoubleClickDetected = false;
//        showFrame = !showFrame;
//    }
//    else
//    {
//        showFrame = true;
//    }
//}

//void SysOvrvObjContainer::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
//{
//    DoubleClickDetected = true;
//}
