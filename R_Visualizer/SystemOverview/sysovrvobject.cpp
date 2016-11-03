#include "sysovrvobject.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QFocusEvent>
#include <QCursor>
#include <QSize>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

int SysOvrvObject::objCntr = 0;

SysOvrvObject::SysOvrvObject(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    isChildObject(false),
    m_BoundingRect(0,0,100,100),
    corners(NULL),
    isInResizeMode(false)
{
    localObjCntr = objCntr++;
    myColor = QColor(Qt::gray);
    shapeType = ObjShape_Rectangle;
    setupSysOvrvObject();
//    qDebug() << "(SysOvrvObject::SysOvrvObject): created obj: " << getHashedName();
}

SysOvrvObject::SysOvrvObject(SysOvrvObject *obj, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    isChildObject(false),
    m_BoundingRect(0,0,obj->getWidth(),obj->getHeight()),
    corners(NULL),
    isInResizeMode(false)
{
    localObjCntr = objCntr++;
    operator =(*obj);
    setupSysOvrvObject();
//    qDebug() << "(SysOvrvObject::SysOvrvObject): created obj: " << getHashedName() << " from object: " << obj->getHashedName();
}

SysOvrvObject::~SysOvrvObject()
{
    qDebug() << "(SysOvrvObject::~SysOvrvObject): deleting obj: " << getHashedName();
    SysOvrvObject *parent = qgraphicsitem_cast<SysOvrvObject *>(parentItem());
    int i = 0;
    for(SysOvrvObject *child : childSysOvrvObjects)
    {
        qDebug() << "Delete Child: " << i++;
//        qDebug() << "(SysOvrvObject::~SysOvrvObject): Delete Child: " << static_cast<SysOvrvObject*>(child)->getHashedName() << " of " << getHashedName();
        delete child;
    }
    childSysOvrvObjects.clear();
    if(parent != NULL)
    {
//        qDebug() << "(SysOvrvObject::~SysOvrvObject): removing"  << getHashedName() << "from parent: " << parent->getHashedName();
        parent->removeChildSysOvrvItem(this);
    }
    showResizeCorners(false);
    qDebug() << "(SysOvrvObject::~SysOvrvObject): deleted obj: " << getHashedName();
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
    painter->setBrush(QBrush(Qt::red));
    painter->drawText(rect, getHashedName());
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

QString SysOvrvObject::getObjName() const
{
    return objName;
}

void SysOvrvObject::setObjName(const QString &value)
{
    objName = QString(value);
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

SysOvrvObject *SysOvrvObject::duplicate(SysOvrvObject *parentObj)
{
    SysOvrvObject *duplicatedObject = new SysOvrvObject();

    duplicatedObject->setPos(this->pos());
    duplicatedObject->setObjName("d_" + this->getObjName()); // is the duplicate token really needed?
    duplicatedObject->setMyColor(this->getMyColor());
    duplicatedObject->setShape(this->getShape());
    duplicatedObject->m_BoundingRect.setWidth(this->getWidth());
    duplicatedObject->m_BoundingRect.setHeight(this->getHeight());
    duplicatedObject->setResizeMode(this->getIsInResizeMode());
    duplicatedObject->setAsChild(true);
    SysOvrvObject *parent = (parentObj != NULL) ? qgraphicsitem_cast<SysOvrvObject*>(this->parentItem()) : parentObj;
    //ToDO!!! -- PROBABLE BUG HERE
    if(parent != NULL)
    {
        parent->addChildSysOvrvItem(duplicatedObject);
    }

    for(SysOvrvObject *child : childSysOvrvObjects)
    {
        duplicatedObject->addChildSysOvrvItem(child->duplicate(this));
    }

    duplicatedObject->update();
    return duplicatedObject;
}

SysOvrvObject &SysOvrvObject::operator=(const SysOvrvObject &obj)
{
    this->setPos(obj.pos());
    this->setObjName(obj.getObjName());
    this->setMyColor(obj.getMyColor());
    this->setShape(obj.getShape());
    this->m_BoundingRect.setWidth(obj.getWidth());
    this->m_BoundingRect.setHeight(obj.getHeight());
    this->setResizeMode(obj.getIsInResizeMode());
    SysOvrvObject *parent = qgraphicsitem_cast<SysOvrvObject*>(obj.parentItem());
    if(parent != NULL)
    {
        parent->addChildSysOvrvItem(this);
    }
    QVector<SysOvrvObject*> children = QVector<SysOvrvObject*>(const_cast<SysOvrvObject&>(obj).getChidSysOvrvObjects());
    int sizeOfChildren = children.size();
    //for(SysOvrvObject *child : const_cast<SysOvrvObject&>(obj).getChidSysOvrvObjects())
    for(int i = 0; i < sizeOfChildren; i++)
    {
        addChildSysOvrvItem(new SysOvrvObject(children.at(i)));
    }
    this->isChildObject = obj.isAChild();

    this->update();
    return *this;
}

void SysOvrvObject::setAsChild(bool isChild)
{
    this->isChildObject = isChild;
}

bool SysOvrvObject::isAChild() const
{
    return isChildObject;
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
    if(newWidth < 0.1)
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
    if(newHeight < 0.1)
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

void SysOvrvObject::removeChildSysOvrvItem(SysOvrvObject *child)
{
    qDebug() << "(SysOvrvObject::removeChildSysOvrvItem): removing " << child->getHashedName() << " from parent: " << getHashedName();
    //ToTHINK !!!!
    //ToDO !!!
    qDebug() << "size before: " <<childSysOvrvObjects.size();
    childSysOvrvObjects.removeAll(child);
    qDebug() << "size after: " <<childSysOvrvObjects.size();
//    QVector<SysOvrvObject*>::Iterator it;
//    for(it = childSysOvrvObjects.begin(); it != childSysOvrvObjects.end(); it++)
//    {
//        if(*it == child)
//        {
//            childSysOvrvObjects.remove(childSysOvrvObjects.indexOf(child));
//            childSysOvrvObjects.erase(it);
//        }
//    }
}

SysOvrvObject *SysOvrvObject::addChildSysOvrvItem(SysOvrvObject *child) //returns the added child
{
    qDebug() << "(SysOvrvObject::addChildSysOvrvItem): trying to add " << child->getHashedName() << " to parent: " << getHashedName();
    if(!childSysOvrvObjects.contains(child))
    {
        qDebug() << "(SysOvrvObject::addChildSysOvrvItem): adding " << child->getHashedName() << " to parent: " << getHashedName();
        childSysOvrvObjects.append(child);
    }
    child->setParentItem(this);
    return child;
}

QVector<SysOvrvObject *> &SysOvrvObject::getChidSysOvrvObjects()
{
    return childSysOvrvObjects;
}

void SysOvrvObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //    QGraphicsItem::mousePressEvent(event);
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void SysOvrvObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //    QGraphicsItem::mouseReleaseEvent(event);
    //    setFocus(Qt::MouseFocusReason);
    //    setSelected(true);

    setCursor(QCursor(Qt::OpenHandCursor));
}

void SysOvrvObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //    QGraphicsItem::mouseDoubleClickEvent(event);
}

void SysOvrvObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->isChildObject)
    {
        SysOvrvObject * parent = qgraphicsitem_cast<SysOvrvObject *>(this->parentItem());
        if(parent != NULL)
                parent->mouseMoveEvent(event);
    }
    else
    {
        qreal distX = event->pos().x() - event->lastPos().x();
        qreal distY = event->pos().y() - event->lastPos().y();
        moveBy(distX,distY);
    }
    //    QGraphicsItem::mouseMoveEvent(event);
}

QString SysOvrvObject::getHashedName() const
{
    return QString("%1__%2").arg(this->objName).arg(this->localObjCntr);
}

QByteArray SysOvrvObject::parseToJson() const
{
    QJsonObject jsonSysOvrvObj;
    QJsonArray objSize;
    QJsonArray objPos;
    QJsonArray objChildren;

    jsonSysOvrvObj["ObjName"] = this->getObjName();
    jsonSysOvrvObj["ObjColor"] = this->getMyColor().name(QColor::HexRgb);
    jsonSysOvrvObj["ObjShape"] = this->getShape();
    objSize.append(QJsonValue(static_cast<double>(m_BoundingRect.width())));
    objSize.append(QJsonValue(static_cast<double>(m_BoundingRect.height())));
    jsonSysOvrvObj["ObjSize"] = objSize;
    objPos.append(QJsonValue(static_cast<double>(pos().x())));
    objPos.append(QJsonValue(static_cast<double>(pos().y())));
    jsonSysOvrvObj["ObjPos"] = objPos;
    for(SysOvrvObject *child : childSysOvrvObjects)
    {
        objChildren.append(QJsonDocument::fromJson(child->parseToJson()).object());
    }
    jsonSysOvrvObj["ChildObjs"] = objChildren;
    return QJsonDocument(jsonSysOvrvObj).toJson();
}

void SysOvrvObject::parseFromJson(QByteArray &jsonByteArray)
{
    QJsonObject jsonSysOvrvObj = QJsonDocument::fromJson(jsonByteArray).object();
    QJsonArray objSize = jsonSysOvrvObj["ObjSize"].toArray();
    QJsonArray objPos = jsonSysOvrvObj["ObjPos"].toArray();
    QJsonArray objChildren = jsonSysOvrvObj["ChildObjs"].toArray();

    if(objSize.size() != 2)
    {
        qDebug() << "Invalid size parameter ObjSize in JSON file";
        return;
    }
    if(objPos.size() != 2)
    {
        qDebug() << "Invalid size parameter ObjPos in JSON file";
        return;
    }
    if(!jsonSysOvrvObj["ObjName"].isString())
    {
        qDebug() << "Invalid parameter ObjName in JSON file";
        return;
    }
    if(!jsonSysOvrvObj["ObjColor"].isString())
    {
        qDebug() << "Invalid parameter ObjColor in JSON file";
        return;
    }

    this->setObjName(jsonSysOvrvObj["ObjName"].toString());
    this->setMyColor(QColor(jsonSysOvrvObj["ObjColor"].toString()));
    this->setShape(static_cast<ObjShapeTypes>(jsonSysOvrvObj["ObjShape"].toInt()));

    this->setWidth(objSize[0].toInt(10));
    this->setHeight(objSize[1].toInt(10));

    this->setPos(static_cast<qreal>(objPos[0].toDouble()),static_cast<qreal>(objPos[1].toDouble()));

    for(QJsonValueRef jsonChildObj : objChildren)
    {
        SysOvrvObject *childObj = new SysOvrvObject();
        QByteArray jsonParsed = QJsonDocument(jsonChildObj.toObject()).toJson();
        childObj->parseFromJson(jsonParsed);
        this->addChildSysOvrvItem(childObj);
        childObj->setAsChild(true);
    }
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
    for(SysOvrvObject *child : childSysOvrvObjects)
    {
        child->focusInEvent(event);
    }
}

void SysOvrvObject::focusOutEvent(QFocusEvent *event)
{
    setSelected(false);
    for(SysOvrvObject *child : childSysOvrvObjects)
    {
        child->focusOutEvent(event);
    }
}

void SysOvrvObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::OpenHandCursor));
}

void SysOvrvObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::ArrowCursor));
}
