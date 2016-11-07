#include "sysovrvobject.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QFocusEvent>
#include <QCursor>
#include <QSize>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QInputDialog>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QFileDialog>
#include <QImageReader>

#include <QDebug>

int SysOvrvObject::objCntr = 0;

SysOvrvObject::SysOvrvObject(QGraphicsItem *parent) :
    QGraphicsItem(parent),
    isChildObject(false),
    doubleClicked(false),
    m_BoundingRect(0,0,100,100),
    corners(NULL),
    isInResizeMode(false)
{
    localObjCntr = objCntr++;
    myColor = QColor(Qt::gray);
    setShape(ObjShape_Rectangle);
    setupSysOvrvObject();
}

//SysOvrvObject::SysOvrvObject(SysOvrvObject *obj, QGraphicsItem *parent) :
//    QGraphicsItem(parent)
//{
//    localObjCntr = objCntr++;
//    *this = *obj;
//    setupSysOvrvObject();
//}

SysOvrvObject::~SysOvrvObject()
{
    qDebug() << "(SysOvrvObject::~SysOvrvObject): deleting obj: " << getHashedName();
    SysOvrvObject *parent = qgraphicsitem_cast<SysOvrvObject *>(parentItem());
    int i = 0;
    //Destroy children
    for(SysOvrvObject *child : childSysOvrvObjects)
    {
        qDebug() << "Delete Child: " << i++;
        //        qDebug() << "(SysOvrvObject::~SysOvrvObject): Delete Child: " << static_cast<SysOvrvObject*>(child)->getHashedName() << " of " << getHashedName();
        delete child;
    }
    childSysOvrvObjects.clear();
    //remove this item from its parent if any
    if(parent != NULL)
    {
        //        qDebug() << "(SysOvrvObject::~SysOvrvObject): removing"  << getHashedName() << "from parent: " << parent->getHashedName();
        parent->removeChildSysOvrvItem(this);
    }
    //destroy resize corners
    showResizeCorners(false); //will automagically also destroy the corners if any

    //destroy text labels
    for(SysOvrvTextLabel * textlabel: objTextlabels)
    {
        delete textlabel;
    }
    objTextlabels.clear();
    qDebug() << "(SysOvrvObject::~SysOvrvObject): deleted obj: " << getHashedName();
}

QRectF SysOvrvObject::boundingRect() const
{
    return m_BoundingRect;
}

void SysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->drawPixmap(rect, ObjPixMap, ObjPixMap.rect());
}

void SysOvrvObject::setupSysOvrvObject()
{
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemSendsScenePositionChanges);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);
    update();
}

QColor SysOvrvObject::getMyColor() const
{
    return this->myColor;
}

void SysOvrvObject::setMyColor(const QColor &value)
{
    myColor = QColor(value);
    update();
}

QString SysOvrvObject::getObjName() const
{
    return objName;
}

void SysOvrvObject::setObjName(const QString &value)
{
    objName = QString(value);
}

void SysOvrvObject::loadImageFromFile()
{
    QString FilePath = QFileDialog::getOpenFileName(Q_NULLPTR, QString("Open Image"), QString(), "Images (*.bmp *.jpg *.png)");
    ObjPixMap = QPixmap(FilePath);
}

void SysOvrvObject::setShape(SysOvrvObject::ObjShapeType shape)
{
    shapeType = shape;

    if(shapeType == ObjShape_Image)
    {
    }
    else if(shapeType == ObjShape_Square || shapeType == ObjShape_Circle)//SQUARE || CIRCLE
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

SysOvrvObject::ObjShapeType SysOvrvObject::getShape() const
{
    return shapeType;
}

SysOvrvTextLabel * SysOvrvObject::addLabel()
{
    SysOvrvTextLabel *newlabel = new SysOvrvTextLabel(this);
    objTextlabels.append(newlabel);
    newlabel->textEdit();
    if(newlabel->text().isEmpty())
    {
        delete newlabel;
        return NULL;
    }
    newlabel->setEditable(true);
    return newlabel;
}

SysOvrvTextLabel * SysOvrvObject::addLabel(SysOvrvTextLabel *label)
{
    if(!objTextlabels.contains(label))
        objTextlabels.append(label);
    return label;
}

SysOvrvTextLabel *SysOvrvObject::addLabel(QString text, qreal x, qreal y)
{
    if(text.isEmpty())
        return NULL;
    SysOvrvTextLabel *newlabel = new SysOvrvTextLabel(this);
    objTextlabels.append(newlabel);
    newlabel->setText(text);
    newlabel->setPos(x,y);
    newlabel->setEditable(true);
    return newlabel;
}

SysOvrvObject *SysOvrvObject::duplicate(SysOvrvObject *parentObj)
{
    SysOvrvObject *duplicatedObject = new SysOvrvObject();

    duplicatedObject->setPos(this->pos());
    duplicatedObject->setObjPixMap(this->getObjPixMap());
    duplicatedObject->setShape(this->getShape());
    duplicatedObject->setObjName("d_" + this->getObjName()); // is the duplicate token really needed?
    duplicatedObject->setMyColor(this->getMyColor());
    duplicatedObject->m_BoundingRect.setWidth(this->getWidth());
    duplicatedObject->m_BoundingRect.setHeight(this->getHeight());
    duplicatedObject->setResizeMode(this->getIsInResizeMode());
    duplicatedObject->setAsChild(true);

    for(SysOvrvTextLabel *textlabel : objTextlabels)
    {
        duplicatedObject->addLabel(textlabel->text(), textlabel->x(), textlabel->y());
    }

    for(SysOvrvObject *child : childSysOvrvObjects)
    {
        duplicatedObject->addChildSysOvrvItem(child->duplicate(this));
    }

    SysOvrvObject *parent = (parentObj == NULL) ? qgraphicsitem_cast<SysOvrvObject*>(this->parentItem()) : parentObj;
    //ToDO!!! -- PROBABLE BUG HERE
    if(parent != NULL)
    {
        parent->addChildSysOvrvItem(duplicatedObject);
    }

    duplicatedObject->update();
    return duplicatedObject;
}

void SysOvrvObject::setAsChild(bool isChild)
{
    this->isChildObject = isChild;
    for(SysOvrvTextLabel * textlabel : this->objTextlabels)
    {
        textlabel->setEditable(!isChild);
    }
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
    update();
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
    update();
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
    childSysOvrvObjects.removeAll(child);
}

SysOvrvObject *SysOvrvObject::addChildSysOvrvItem(SysOvrvObject *child) //returns the added child
{
    SysOvrvObject *prevParent = qgraphicsitem_cast<SysOvrvObject*>(child->parentItem());
    if(prevParent != NULL)
    {
        prevParent->removeChildSysOvrvItem(child);
    }
    child->setParentItem(this);

    if(!childSysOvrvObjects.contains(child))
    {
        qDebug() << "(SysOvrvObject::addChildSysOvrvItem): adding " << child->getHashedName() << " to parent: " << getHashedName();
        childSysOvrvObjects.append(child);
    }
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
    if(doubleClicked)
    {
        doubleClicked = false;
        qDebug() << "MouseRelease DoubleClicked";
    }
}

void SysOvrvObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //    QGraphicsItem::mouseDoubleClickEvent(event);
    qDebug() << "DoubleClickEvent";
    doubleClicked = true;
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
    QJsonArray objlabels;

    jsonSysOvrvObj["ObjName"] = this->getObjName();
    jsonSysOvrvObj["ObjColor"] = this->getMyColor().name(QColor::HexRgb);
    jsonSysOvrvObj["ObjShape"] = this->getShape();
    objSize.append(QJsonValue(static_cast<double>(m_BoundingRect.width())));
    objSize.append(QJsonValue(static_cast<double>(m_BoundingRect.height())));
    jsonSysOvrvObj["ObjSize"] = objSize;
    objPos.append(QJsonValue(static_cast<double>(x())));
    objPos.append(QJsonValue(static_cast<double>(y())));
    jsonSysOvrvObj["ObjPos"] = objPos;
    for(SysOvrvObject *child : childSysOvrvObjects)
    {
        objChildren.append(QJsonDocument::fromJson(child->parseToJson()).object());
    }
    jsonSysOvrvObj["ChildObjs"] = objChildren;
    for(SysOvrvTextLabel *textlabel : objTextlabels)
    {
        objlabels.append(QJsonDocument::fromJson(textlabel->parseToJson()).object());
    }
    jsonSysOvrvObj["Textlabels"] = objlabels;
    return QJsonDocument(jsonSysOvrvObj).toJson();
}

void SysOvrvObject::parseFromJson(QByteArray &jsonByteArray)
{
    QJsonObject jsonSysOvrvObj = QJsonDocument::fromJson(jsonByteArray).object();
    QJsonArray objSize = jsonSysOvrvObj["ObjSize"].toArray();
    QJsonArray objPos = jsonSysOvrvObj["ObjPos"].toArray();
    QJsonArray objChildren = jsonSysOvrvObj["ChildObjs"].toArray();
    QJsonArray objlabels = jsonSysOvrvObj["Textlabels"].toArray();

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
    this->setShape(static_cast<ObjShapeType>(jsonSysOvrvObj["ObjShape"].toInt()));

    this->setWidth(static_cast<qreal>(objSize[0].toDouble(100)));
    this->setHeight(static_cast<qreal>(objSize[1].toDouble(100)));

    this->setPos(static_cast<qreal>(objPos[0].toDouble()),static_cast<qreal>(objPos[1].toDouble()));

    for(QJsonValueRef jsonChildObj : objChildren)
    {
        SysOvrvObject *childObj = new SysOvrvObject();
        QByteArray jsonParsed = QJsonDocument(jsonChildObj.toObject()).toJson();
        childObj->parseFromJson(jsonParsed);
        this->addChildSysOvrvItem(childObj);
        childObj->setAsChild(true);
    }
    for(QJsonValueRef jsonTextlabelsValue : objlabels)
    {
        SysOvrvTextLabel *textlabel = new SysOvrvTextLabel(this);
        QByteArray jsonParsed = QJsonDocument(jsonTextlabelsValue.toObject()).toJson();
        textlabel->parseFromJson(jsonParsed);
        this->addLabel(textlabel);
    }
}

void SysOvrvObject::addTrigger(quint16 id, quint8 code, SysOvrvTrigger *newTrigger)
{
    LocalTriggerStore[id][code].append(newTrigger);
    addChildsTrigger(id, code, newTrigger);
}

void SysOvrvObject::addChildsTrigger(quint16 id, quint8 code, SysOvrvTrigger *newChildTrigger)
{
    GlobalTriggerStore[id][code].append(newChildTrigger);
    SysOvrvObject *parent = qgraphicsitem_cast<SysOvrvObject*>(parentItem());
    if(parent != NULL)
        parent->addChildsTrigger(id, code, newChildTrigger);
}

void SysOvrvObject::removeTrigger(quint16 id, quint8 code, SysOvrvTrigger *triggerToRemove)
{
    LocalTriggerStore[id][code].removeAll(triggerToRemove);
    removeChildsTrigger(id, code, triggerToRemove);
}

void SysOvrvObject::removeChildsTrigger(quint16 id, quint8 code, SysOvrvTrigger *triggerToRemove)
{
    GlobalTriggerStore[id][code].removeAll(triggerToRemove);
    SysOvrvObject *parent = qgraphicsitem_cast<SysOvrvObject*>(parentItem());
    if(parent != NULL)
        parent->removeChildsTrigger(id, code, triggerToRemove);
}

void SysOvrvObject::msgReceived(quint16 id, quint8 code, QByteArray &canData)
{
    qDebug() << getHashedName() << ": received msg " << id << " - " << code;
    QVector<SysOvrvTrigger*> triggers = GlobalTriggerStore[id][code];
    for(SysOvrvTrigger *trigger : triggers)
    {
        trigger->trigger(canData);
    }
}

QList<quint16> SysOvrvObject::getTriggerIDs() const
{
    return GlobalTriggerStore.uniqueKeys();
}

QList<quint8> SysOvrvObject::getTriggerCodesToID(quint16 id) const
{
    return GlobalTriggerStore.value(id).uniqueKeys();
}

QVector<SysOvrvTrigger *> SysOvrvObject::getTriggersToIDandCode(quint16 id, quint8 code)
{
    return GlobalTriggerStore.value(id).value(code);
}

QPixmap SysOvrvObject::getObjPixMap() const
{
    return ObjPixMap;
}

void SysOvrvObject::setObjPixMap(const QPixmap &value)
{
    ObjPixMap = value;
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

void SysOvrvObject::update(const QRectF &rect)
{
    if(shapeType == ObjShape_Image)
    {
//        ObjPixMap = QPixmap(FilePath);
    }
    else
    {
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

        ObjPixMap = QPixmap(m_BoundingRect.size().toSize());
        ObjPixMap.fill(Qt::white);

        QPainter painter(&ObjPixMap);
        QBrush brush(myColor);

        if(this->isSelected()/* || (isChildObject && parentItem() != NULL && parentItem()->isSelected())*/) //ToTHINK visualize children also as selected??
        {
            brush.setColor(myColor.darker());
        }

        painter.setBrush(brush);
        painter.setRenderHint(QPainter::Antialiasing);

        switch(shapeType)
        {
        case ObjShape_Rectangle: // Rect
        case ObjShape_Square: // Square
            painter.drawRect(m_BoundingRect);
            break;
        case ObjShape_Ellipse:
        case ObjShape_Circle: // Circle
            painter.drawEllipse(m_BoundingRect);
            break;
        case ObjShape_Triangle: // Triangle
        {
            QPainterPath path;
            QPointF rectTopMiddle((m_BoundingRect.right() - m_BoundingRect.left()) / 2, m_BoundingRect.top());
            path.moveTo(rectTopMiddle);
            path.lineTo(m_BoundingRect.right(), m_BoundingRect.bottom());
            path.lineTo(m_BoundingRect.left(), m_BoundingRect.bottom());
            path.lineTo(rectTopMiddle);
            painter.drawPath(path);
        }
            break;
        case ObjShape_Image:
            break;
        }
    }
    QGraphicsItem::update(rect);
}

void SysOvrvObject::focusInEvent(QFocusEvent *event)
{
    setSelected(true);
    update();
    for(SysOvrvObject *child : childSysOvrvObjects)
    {
        child->focusInEvent(event);
    }
}

void SysOvrvObject::focusOutEvent(QFocusEvent *event)
{
    setSelected(false);
    update();
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
