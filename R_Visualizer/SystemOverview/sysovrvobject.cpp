#include "sysovrvobject.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QFocusEvent>

#include <QDebug>

SysOvrvObject::SysOvrvObject(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    isChildObject(false),
    m_BoundingRect(0,0,100,100),
    corners(NULL),
    isInResizeMode(false)
{
    myColor = QColor(Qt::gray);
    shapeType = ObjShape_Rectangle;
    setupSysOvrvObject();
}

SysOvrvObject::SysOvrvObject(SysOvrvObject *obj, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    isChildObject(false),
    m_BoundingRect(0,0,obj->getWidth(),obj->getHeight()),
    corners(NULL),
    isInResizeMode(false)
{
    *this = *obj;
    setupSysOvrvObject();
}

QRectF SysOvrvObject::boundingRect() const
{
    return m_BoundingRect;
}

void SysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(myColor);

    if(this->isSelected()/* || (isChildObject && parentItem() != NULL && parentItem()->isSelected())*/) //ToTHINK visualize children also as selected??
    {
        brush.setColor(myColor.darker());
    }

    painter->setBrush(brush);

    switch(shapeType)
    {
    case ObjShape_Rectangle: // Rect
        painter->drawRect(rect);
        break;
    case ObjShape_Square: // Square
        rect.setY(rect.x());
        painter->drawRect(rect);
        break;
    case ObjShape_Ellipse:
        painter->drawEllipse(rect);
        break;
    case ObjShape_Circle: // Circle
        painter->drawEllipse(rect);
        break;
    case ObjShape_Triangle: // Triangle
    {
        QPainterPath path;
        QPointF rectTopMiddle((rect.right() - rect.left()) / 2, rect.top());
        path.moveTo(rectTopMiddle);
        path.lineTo(rect.right(), rect.bottom());
        path.lineTo(rect.left(), rect.bottom());
        path.lineTo(rectTopMiddle);
        painter->drawPath(path);
    }
        break;
    }
}

void SysOvrvObject::setupSysOvrvObject()
{
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemSendsScenePositionChanges);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);
}

QColor SysOvrvObject::getMyColor() const
{
    return this->myColor;
}

void SysOvrvObject::setMyColor(const QColor &value)
{
    myColor = QColor(value);
}

QHash<QString, SysOvrvObject *> &SysOvrvObject::getObjStore()
{
    return objStore;
}

void SysOvrvObject::setObjStore(QHash<QString, SysOvrvObject *> &value)
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

void SysOvrvObject::setShape(ObjShapeTypes shape)
{
    shapeType = shape;
    if(shapeType == ObjShape_Square || shapeType == ObjShape_Circle)//SQUARE || CIRCLE
    {
        if(m_BoundingRect.width() > m_BoundingRect.height())
        {
            m_BoundingRect.setHeight(m_BoundingRect.width());
        }
        else
        {
            m_BoundingRect.setWidth(m_BoundingRect.height());
        }
        updateCorners();
    }
    this->update();
}

SysOvrvObject::ObjShapeTypes SysOvrvObject::getShape() const
{
    return shapeType;
}

SysOvrvObject &SysOvrvObject::operator=(const SysOvrvObject &obj)
{

    this->objName = obj.getObjName();
    this->setObjStore(const_cast<SysOvrvObject &>(obj).getObjStore());
    this->myColor = obj.getMyColor();
    this->shapeType = obj.getShape();
    this->m_BoundingRect.setWidth(obj.getWidth());
    this->m_BoundingRect.setHeight(obj.getHeight());
    this->isInResizeMode = obj.getIsInResizeMode();

    this->update();
    return *this;
}

void SysOvrvObject::setAsChild(bool isChild)
{
    this->isChildObject = isChild;
}

void SysOvrvObject::setResizeMode(bool modeON)
{
    isInResizeMode = modeON;
    showResizeCorners(modeON);
    for(auto child : childSysOvrvObjects)
        child->setResizeMode(modeON);
}

bool SysOvrvObject::getIsInResizeMode() const
{
    return isInResizeMode;
}

void SysOvrvObject::showResizeCorners(bool show)
{
    if(show)
    {
        if(corners == NULL)
        {
            qDebug() << "Creating Corners!";
            corners = new ResizeRectCorner[4];
            for(int i = 0; i < 4; i++)
            {
                corners[i].setParentItem(this);
                corners[i].setCornerPos(static_cast<ResizeRectCorner::CornerPos>(i));
                corners[i].setRect(QRectF(0,0,10,10));
            }
        }
        updateCorners();
    }
    else
    {
        if(corners != NULL)
        {
            qDebug() << "Deleting Corners!";
            delete[] corners;
            corners = NULL;
        }
    }
}

qreal SysOvrvObject::getWidth() const
{
    return m_BoundingRect.width();
}

void SysOvrvObject::setWidth(qreal newWidth)
{
    qDebug() << "Changing width of obj: " << objName << " old: " << getWidth() << " new: " << newWidth;
    if(newWidth < 0)
        return;
    prepareGeometryChange();
    m_BoundingRect.setWidth(newWidth);
    if(shapeType == ObjShape_Square || shapeType == ObjShape_Circle) // SQUARE || CIRCLE
        m_BoundingRect.setHeight(newWidth);
    updateCorners();
}

void SysOvrvObject::adjustWidth(qreal factor)
{
    setWidth(m_BoundingRect.width()*factor);
    for(SysOvrvObject * child : childSysOvrvObjects)
        child->adjustWidth(factor);
}

qreal SysOvrvObject::getHeight() const
{
    return m_BoundingRect.height();
}

void SysOvrvObject::setHeight(qreal newHeight)
{
    qDebug() << "Changing height of obj: " << objName << " old: " << getHeight() << " new: " << newHeight;
    if(newHeight < 0)
        return;
    prepareGeometryChange();
    m_BoundingRect.setHeight(newHeight);
    if(shapeType == ObjShape_Square || shapeType == ObjShape_Circle) // SQUARE || CIRCLE
        m_BoundingRect.setWidth(newHeight);
    updateCorners();
}

void SysOvrvObject::adjustHeight(qreal factor)
{
    setHeight(m_BoundingRect.height()*factor);
    for(SysOvrvObject * child : childSysOvrvObjects)
        child->adjustHeight(factor);
}

void SysOvrvObject::addChildSysOvrvItem(SysOvrvObject *child)
{
    childSysOvrvObjects.append(child);
    child->setParentItem(this);
}

QVector<SysOvrvObject *> &SysOvrvObject::getChidSysOvrvObjects()
{
    return childSysOvrvObjects;
}

void SysOvrvObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //    QGraphicsItem::mousePressEvent(event);
}

void SysOvrvObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //    QGraphicsItem::mouseReleaseEvent(event);
    //    setFocus(Qt::MouseFocusReason);
    //    setSelected(true);
}

void SysOvrvObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //    QGraphicsItem::mouseDoubleClickEvent(event);
}

void SysOvrvObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->isChildObject)
    {
        qgraphicsitem_cast<SysOvrvObject *>(this->parentItem())->mouseMoveEvent(event);
    }
    else
    {
        qreal distX = event->pos().x() - event->lastPos().x();
        qreal distY = event->pos().y() - event->lastPos().y();
        moveBy(distX,distY);
    }
    //    QGraphicsItem::mouseMoveEvent(event);
}

void SysOvrvObject::updateCorners()
{
    if(!isInResizeMode || corners == NULL)
        return;

    QPointF curPoint;

    curPoint = m_BoundingRect.topLeft();
    curPoint.setX(curPoint.rx()-10);
    curPoint.setY(curPoint.ry()-10);
    corners[0].setPos(curPoint); //leftTop
    corners[0].update();
    curPoint = m_BoundingRect.bottomLeft();
    curPoint.setX(curPoint.rx()-10);
    corners[1].setPos(curPoint); //leftBottom
    corners[1].update();
    curPoint = m_BoundingRect.topRight();
    curPoint.setY(curPoint.ry()-10);
    corners[2].setPos(curPoint); //rightTop
    corners[2].update();
    curPoint = m_BoundingRect.bottomRight();
    corners[3].setPos(curPoint); //rightBottom
    corners[3].update();
}

void SysOvrvObject::focusInEvent(QFocusEvent *event)
{
    setSelected(true);
    qDebug() << "has now focus: " << this->getObjName();
}

void SysOvrvObject::focusOutEvent(QFocusEvent *event)
{
    setSelected(false);
    qDebug() << "lost focus: " << this->getObjName();
}
