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

unsigned int SysOvrvObject::objCntr = 0;

SysOvrvObject::SysOvrvObject(QGraphicsItem *parent) :
    ResizableGraphicsItem(parent),
    localObjCntr(objCntr++),
    m_BoundingRect(0,0,100,100),
    objName(std::move(QString(""))),
    myColor(std::move(QColor(Qt::gray))),
    shapeType(ObjShape_Rectangle),
    isChildObject(false),
    isEditable(false),
    doubleClicked(false)
{
    setupSysOvrvObject();
    enableEdit(isEditable);
}

SysOvrvObject::SysOvrvObject(const SysOvrvObject &ToCopy) :
    ResizableGraphicsItem(ToCopy),
    localObjCntr(ToCopy.localObjCntr),
    m_BoundingRect(ToCopy.m_BoundingRect),
    objName(ToCopy.objName),
    myColor(ToCopy.myColor),
    shapeType(ToCopy.shapeType),
    isChildObject(ToCopy.isChildObject),
    isEditable(ToCopy.isEditable),
    doubleClicked(ToCopy.doubleClicked)
{
    QList<QGraphicsItem*> ToCopyChildren = ToCopy.childItems();
    for(QGraphicsItem * const child : ToCopyChildren)
    {
        SysOvrvObject * const ChildSysOvrvObj = dynamic_cast<SysOvrvObject*>(child);
        if(ChildSysOvrvObj != Q_NULLPTR)
        {
            SysOvrvObject *childCopy = ChildSysOvrvObj->clone();
            childCopy->setParentItem(this);
            continue;
        }
        SysOvrvTextLabel * const ChildSysOvrvTextLabel = dynamic_cast<SysOvrvTextLabel*>(child);
        if(ChildSysOvrvTextLabel != Q_NULLPTR)
        {
            SysOvrvTextLabel *childCopy = new SysOvrvTextLabel(*ChildSysOvrvTextLabel);
            childCopy->setParentItem(this);
            continue;
        }
    }
    setPos(ToCopy.pos());
    enableResizing(ToCopy.getResizeEnabled());
    setupSysOvrvObject();
    enableEdit(isEditable);
}

SysOvrvObject::SysOvrvObject(SysOvrvObject &&ToMove) :
    ResizableGraphicsItem(ToMove),
    localObjCntr(ToMove.localObjCntr),
    m_BoundingRect(std::move(ToMove.m_BoundingRect)),
    objName(std::move(ToMove.objName)),
    myColor(std::move(ToMove.myColor)),
    isChildObject(ToMove.isChildObject),
    isEditable(ToMove.isEditable),
    doubleClicked(ToMove.doubleClicked)
{
    QList<QGraphicsItem*> ToMoveChildren = ToMove.childItems();
    for(QGraphicsItem * const child : ToMoveChildren)
    {
        child->setParentItem(this);
    }

    setPos(ToMove.pos());
    enableResizing(ToMove.getResizeEnabled());
    setupSysOvrvObject();
    enableEdit(isEditable);
    ToMove.setParentItem(Q_NULLPTR);
}

SysOvrvObject::~SysOvrvObject()
{
    //Invalidate Parent (if any..)
    /* this->setParentItem(Q_NULLPTR); */
    qDebug() << "(SysOvrvObject::~SysOvrvObject): deleted obj: " << getHashedName();
}

QString SysOvrvObject::translateObjShapeTypeToString(SysOvrvObject::ObjShapeType type)
{
    QString ObjShapeAsString("ERROR");
    switch(type)
    {
    case ObjShape_Rectangle:
        ObjShapeAsString = std::move(QString("rectangle"));
        break;
    case ObjShape_Square:
        ObjShapeAsString = std::move(QString("square"));
        break;
    case ObjShape_Ellipse:
        ObjShapeAsString = std::move(QString("ellipse"));
        break;
    case ObjShape_Circle:
        ObjShapeAsString = std::move(QString("circle"));
        break;
    case ObjShape_Triangle:
        ObjShapeAsString = std::move(QString("triangle"));
        break;
    case ObjShape_Image:
        ObjShapeAsString = std::move(QString("image"));
        break;
    default:
        break;
    }

    return std::move(ObjShapeAsString);
}

QStringList SysOvrvObject::getShapesAsStringList()
{
    QStringList items;
    for( int i = 0; i < NR_of_ObjShapes; i++)
    {
        items << translateObjShapeTypeToString(static_cast<SysOvrvObject::ObjShapeType>(i));
    }

    return std::move(items);
}

QRectF SysOvrvObject::boundingRect() const
{
    return m_BoundingRect;
}

void SysOvrvObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* ResizableGraphicsItem::paint(painter, option, widget); */
    /* painter->drawPixmap(boundingRect(), ObjPixMap, ObjPixMap.rect()); */
}

int SysOvrvObject::type() const
{
    return Type;
}

void SysOvrvObject::setupSysOvrvObject()
{
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemSendsScenePositionChanges);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);
    initResizeCorners();
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
    /* updateShape(); */
}

QString SysOvrvObject::getObjName() const
{
    return objName;
}

void SysOvrvObject::setObjName(const QString &value)
{
    objName = QString(value);
    update();
}

void SysOvrvObject::loadImageFromFile(QWidget *parent)
{
    QString FilePath = QFileDialog::getOpenFileName(parent, QString("Open Image"), QString(), "Images (*.bmp *.jpg *.png)");
    loadImageFromFile(FilePath);
}

void SysOvrvObject::loadImageFromFile(const QString &FilePath)
{
    ObjPixMap = QPixmap(FilePath);
    update();
}

void SysOvrvObject::setShape(SysOvrvObject::ObjShapeType shape)
{
    /* shapeType = shape; */

    /* if(shapeType == ObjShape_Square || shapeType == ObjShape_Circle)//SQUARE || CIRCLE */
    /* { */
    /*     if(m_BoundingRect.width() > m_BoundingRect.height()) */
    /*     { */
    /*         m_BoundingRect.setHeight(m_BoundingRect.width()); */
    /*     } */
    /*     else */
    /*     { */
    /*         m_BoundingRect.setWidth(m_BoundingRect.height()); */
    /*     } */
    /* } */

    /* updateShape(); */
}

SysOvrvObject::ObjShapeType SysOvrvObject::getShape() const
{
    /* return shapeType; */
}

SysOvrvTextLabel * SysOvrvObject::addLabel()
{
    SysOvrvTextLabel *newlabel = new SysOvrvTextLabel(this);
    newlabel->textEdit();
    if(newlabel->text().isEmpty())
    {
        delete newlabel;
        return Q_NULLPTR;
    }
    newlabel->setEditable(true);
    return newlabel;
}

SysOvrvTextLabel * SysOvrvObject::addLabel(SysOvrvTextLabel *label)
{
    label->setParentItem(this);
    return label;
}

SysOvrvTextLabel *SysOvrvObject::addLabel(const QString &text, const qreal x, const qreal y)
{
    if(text.isEmpty())
        return NULL;
    SysOvrvTextLabel *newlabel = new SysOvrvTextLabel(this);
    newlabel->setText(text);
    newlabel->setPos(x,y);
    newlabel->setEditable(true);
    return newlabel;
}

void SysOvrvObject::removeLabel(SysOvrvTextLabel *label)
{

}

SysOvrvObject *SysOvrvObject::duplicate(SysOvrvObject *parentObj)
{
    SysOvrvObject *duplicatedObject = clone();
    if(parentObj != Q_NULLPTR)
    {
        duplicatedObject->setParentItem(parentObj);
    }
    return duplicatedObject;
}

void SysOvrvObject::setAsChild(bool isChild)
{
    this->isChildObject = isChild;
    enableEdit(!isChild);
}

bool SysOvrvObject::isAChild() const
{
    return isChildObject;
}

//void SysOvrvObject::removeChildSysOvrvItem(SysOvrvObject *child)
//{
//    qDebug() << "(SysOvrvObject::removeChildSysOvrvItem): removing " << child->getHashedName() << " from parent: " << getHashedName();
//    childSysOvrvObjects.removeAll(child);
//}

//SysOvrvObject *SysOvrvObject::addChildSysOvrvItem(SysOvrvObject *child) //returns the added child
//{
//    SysOvrvObject *prevParent = dynamic_cast<SysOvrvObject*>(child->parentItem());
//    if(prevParent != Q_NULLPTR)
//    {
//        prevParent->removeChildSysOvrvItem(child);
//    }
//    child->setParentItem(this);

//    if(!childSysOvrvObjects.contains(child))
//    {
//        qDebug() << "(SysOvrvObject::addChildSysOvrvItem): adding " << child->getHashedName() << " to parent: " << getHashedName();
//        childSysOvrvObjects.append(child);
//    }
//    return child;
//}

QVector<SysOvrvObject *> SysOvrvObject::getChidSysOvrvObjects()
{
    QVector<SysOvrvObject *> childSysOvrvObjs;
    QList<QGraphicsItem*> children = childItems();
    for( QGraphicsItem * const child : children)
    {
        SysOvrvObject *ChildSysOvrvObj = dynamic_cast<SysOvrvObject*>(child);
        if(ChildSysOvrvObj != Q_NULLPTR)
        {
            childSysOvrvObjs.append(ChildSysOvrvObj);
        }
    }
    return childSysOvrvObjs;
}

void SysOvrvObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void SysOvrvObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(QCursor(Qt::OpenHandCursor));
    if(doubleClicked)
    {
        doubleClicked = false;
        qDebug() << "MouseRelease DoubleClicked";
    }
}

void SysOvrvObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    doubleClicked = true;
}

void SysOvrvObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->isChildObject)
    {
        SysOvrvObject * parent = dynamic_cast<SysOvrvObject *>(this->parentItem());
        if(parent != Q_NULLPTR)
        {
            parent->mouseMoveEvent(event);
        }
    }
    else
    {
        qreal distX = event->pos().x() - event->lastPos().x();
        qreal distY = event->pos().y() - event->lastPos().y();
        moveBy(distX,distY);
    }
    ResizableGraphicsItem::mouseMoveEvent(event);
    //ToDO Outsource method 
    //Move corners in ResizableGraphicsItem...
    /* initResizeCorners(); */
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
    QList<QGraphicsItem *> children = childItems();
    for(QGraphicsItem *child : children)
    {
        SysOvrvObject *sysOvrvChild = dynamic_cast<SysOvrvObject*>(child);
        if(sysOvrvChild != Q_NULLPTR)
        {
            objChildren.append(QJsonDocument::fromJson(sysOvrvChild->parseToJson()).object());
        }
        else
        {
            SysOvrvTextLabel *ChildTextLabel = dynamic_cast<SysOvrvTextLabel*>(child);
            if(ChildTextLabel != Q_NULLPTR)
            {
                objlabels.append(QJsonDocument::fromJson(ChildTextLabel->parseToJson()).object());
            }
        }
    }
    jsonSysOvrvObj["ChildObjs"] = objChildren;
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
    this->setMyColor(std::move(QColor(jsonSysOvrvObj["ObjColor"].toString())));
    this->setShape(static_cast<ObjShapeType>(jsonSysOvrvObj["ObjShape"].toInt()));

    this->setWidth(static_cast<qreal>(objSize[0].toDouble(100)));
    this->setHeight(static_cast<qreal>(objSize[1].toDouble(100)));

    this->setPos(static_cast<qreal>(objPos[0].toDouble()),static_cast<qreal>(objPos[1].toDouble()));

    for(QJsonValueRef jsonChildObj : objChildren)
    {
        //ToDO...let the parsing happen in the derived classes!
        /* SysOvrvObject *childObj = new SysOvrvObject(this); */
        /* QByteArray jsonParsed = QJsonDocument(jsonChildObj.toObject()).toJson(); */
        /* childObj->parseFromJson(jsonParsed); */
        /* childObj->setAsChild(true); */
    }
    for(QJsonValueRef jsonTextlabelsValue : objlabels)
    {
        SysOvrvTextLabel *textlabel = new SysOvrvTextLabel(this);
        QByteArray jsonParsed = QJsonDocument(jsonTextlabelsValue.toObject()).toJson();
        textlabel->parseFromJson(jsonParsed);
        this->addLabel(textlabel);
    }
}

QPixmap SysOvrvObject::getObjPixMap() const
{
    return ObjPixMap;
}

void SysOvrvObject::setObjPixMap(const QPixmap &value)
{
    ObjPixMap = value;
}

void SysOvrvObject::updateShape(const QRectF &rect)
{
    /* if(shapeType == ObjShape_Image) */
    /* { */
    /*     //        ObjPixMap = QPixmap(FilePath); */
    /* } */
    /* else */
    /* { */
    /*     if(shapeType == ObjShape_Square || shapeType == ObjShape_Circle)//SQUARE || CIRCLE */
    /*     { */
    /*         if(m_BoundingRect.width() > m_BoundingRect.height()) */
    /*         { */
    /*             setHeight(m_BoundingRect.width()); */
    /*         } */
    /*         else */
    /*         { */
    /*             setWidth(m_BoundingRect.height()); */
    /*         } */
    /*     } */


    /*     QRect boundRect = m_BoundingRect.toRect(); */
    /*     ObjPixMap = QPixmap(boundRect.size()); */
    /*     ObjPixMap.fill(Qt::transparent); */

    /*     QPainter painter(&ObjPixMap); */
    /*     boundRect.setWidth(boundRect.width() - painter.pen().width()); */
    /*     boundRect.setHeight(boundRect.height() - painter.pen().width()); */
    /*     QBrush brush(myColor); */

    // /*     if(this->isSelected()/1* || (isChildObject && parentItem() != NULL && parentItem()->isSelected())*/) //ToTHINK visualize children also as selected?? */
    /*     { */
    /*         brush.setColor(myColor.darker()); */
    /*     } */

    /*     painter.setBrush(brush); */
    /*     //        painter.setRenderHint(QPainter::Antialiasing); */

    /*     switch(shapeType) */
    /*     { */
    /*     case ObjShape_Rectangle: // Rect */
    /*     case ObjShape_Square: // Square */
    /*         painter.drawRect(boundRect); */
    /*         break; */
    /*     case ObjShape_Ellipse: */
    /*     case ObjShape_Circle: // Circle */
    /*         painter.drawEllipse(boundRect); */
    /*         break; */
    /*     case ObjShape_Triangle: // Triangle */
    /*     { */
    /*         QPainterPath path; */
    /*         QPointF rectTopMiddle((boundRect.right() - boundRect.left()) / 2, boundRect.top()); */
    /*         path.moveTo(rectTopMiddle); */
    /*         path.lineTo(boundRect.right(), boundRect.bottom()); */
    /*         path.lineTo(boundRect.left(), boundRect.bottom()); */
    /*         path.lineTo(rectTopMiddle); */
    /*         painter.drawPath(path); */
        /* } */
        /*     break; */
        /* case ObjShape_Image: */
        /*     break; */
        /* default: */
        /*     break; */
        /* } */
    /* } */
    /* initResizeCorners(); */
    /* ResizableGraphicsItem::update(rect); */
}

void SysOvrvObject::setParentSysOvrvObj(SysOvrvObject *parentSysOvrvObj)
{
    //    parentSysOvrvObj->addChildSysOvrvItem(this);
    setParentItem(parentSysOvrvObj);
}

void SysOvrvObject::enableEdit(bool enable)
{
    isEditable = enable;
    enableResizing(enable);
    initResizeCorners();

    QList<QGraphicsItem *> children = childItems();
    for(QGraphicsItem *child : children)
    {
        SysOvrvObject *sysOvrvChild = dynamic_cast<SysOvrvObject*>(child);
        if(sysOvrvChild != Q_NULLPTR)
        {
            sysOvrvChild->enableEdit(enable);
            continue;
        }
        SysOvrvTextLabel * sysOvrvTextLabel = dynamic_cast<SysOvrvTextLabel *>(child);
        if(sysOvrvTextLabel != Q_NULLPTR)
        {
            sysOvrvTextLabel->setEditable(enable);
            continue;
        }
    }
}

void SysOvrvObject::enableChildrenEdit(bool enable)
{
    QList<QGraphicsItem *> children = childItems();
    for(QGraphicsItem *child : children)
    {
        SysOvrvObject *sysOvrvChild = dynamic_cast<SysOvrvObject*>(child);
        if(sysOvrvChild != Q_NULLPTR)
        {
            sysOvrvChild->enableEdit(enable);
        }
    }
}

void SysOvrvObject::focusInEvent(QFocusEvent *event)
{
    QList<QGraphicsItem *> children = childItems();
    for(QGraphicsItem *child : children)
    {
        SysOvrvObject *sysOvrvChild = dynamic_cast<SysOvrvObject*>(child);
        if(sysOvrvChild != Q_NULLPTR)
        {
            sysOvrvChild->focusInEvent(event);
        }
    }
    setSelected(true);
    updateShape();
}

void SysOvrvObject::focusOutEvent(QFocusEvent *event)
{
    QList<QGraphicsItem *> children = childItems();
    for(QGraphicsItem *child : children)
    {
        SysOvrvObject *sysOvrvChild = dynamic_cast<SysOvrvObject*>(child);
        if(sysOvrvChild != Q_NULLPTR)
        {
            sysOvrvChild->focusOutEvent(event);
        }
    }
    setSelected(false);
    updateShape();
}

void SysOvrvObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    setCursor(QCursor(Qt::OpenHandCursor));
}

void SysOvrvObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event)
    setCursor(QCursor(Qt::ArrowCursor));
}

void SysOvrvObject::resize(const ResizeRectCorner::CornerPos AnchorPoint, qreal x, qreal y)
{
    QList<QGraphicsItem*> children = childItems();
    for(QGraphicsItem * const child : children)
    {
        SysOvrvObject * SysOvrvChild = dynamic_cast<SysOvrvObject*>(child);
        if(SysOvrvChild != Q_NULLPTR)
        {
            qreal xPos = SysOvrvChild->x();
            qreal yPos = SysOvrvChild->y();
            SysOvrvChild->resize(AnchorPoint, x, y);
            SysOvrvChild->setPos(xPos, yPos);
        }
    }
    ResizableGraphicsItem::resize(AnchorPoint, x, y);
    update();
}

void SysOvrvObject::setWidth(const qreal newWidth)
{
    m_BoundingRect.setWidth(newWidth);
    update();
}

qreal SysOvrvObject::getWidth() const
{
    return m_BoundingRect.width();
}

void SysOvrvObject::setHeight(const qreal newHeight)
{
    m_BoundingRect.setHeight(newHeight);
    update();
}

qreal SysOvrvObject::getHeight() const
{
    return m_BoundingRect.height();
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //


