#include "SysOverviewObjectShapeManager.h"

#include "ISystemOverviewObject.h"
#include "SysOverviewObjectColorManager.h"

SysOverviewObjectShapeManager::SysOverviewObjectShapeManager(
        ISystemOverviewObject *sysOverviewObject,
        SysOverviewObjectShapeManager::SysOverviewObjectShape shape
        ) :
    ISysOverviewObjectManagerCRTPHelper(
        ISysOverviewObjectManager::ShapeType
        ),
    sysOverviewObject(sysOverviewObject),
    colorManager(
        SysOvrvObjColorManagerPtr(
            new SysOverviewObjectColorManager(this)
            )
        ),
    shape(shape)
{

}

SysOverviewObjectShapeManager::SysOverviewObjectShapeManager(
        ISystemOverviewObject *sysOverviewObject,
        SysOvrvObjColorManagerPtr colorManager,
        SysOverviewObjectShapeManager::SysOverviewObjectShape shape
        ) :
    ISysOverviewObjectManagerCRTPHelper(
        ISysOverviewObjectManager::ShapeType
        ),
    sysOverviewObject(sysOverviewObject),
    colorManager(std::move(colorManager)),
    shape(shape)
{
    this->colorManager->setShapeManager(this);
}

SysOverviewObjectShapeManager::SysOverviewObjectShapeManager(
        const SysOverviewObjectShapeManager &copy
        ) :
    ISysOverviewObjectManagerCRTPHelper(
        ISysOverviewObjectManager::ShapeType
        ),
    sysOverviewObject(copy.sysOverviewObject),
    colorManager(copy.colorManager->clone()),
    shape(copy.shape)
{
    this->colorManager->setShapeManager(this);
}

SysOverviewObjectShapeManager::~SysOverviewObjectShapeManager()
{

}

void SysOverviewObjectShapeManager::setSysOverviewObject(ISystemOverviewObject *newSysOverviewObject)
{
    this->sysOverviewObject = newSysOverviewObject;
}

SysOverviewObjectShapeManager::SysOverviewObjectShape SysOverviewObjectShapeManager::getShape() const
{
    return this->shape;
}

void SysOverviewObjectShapeManager::setShape(
        const SysOverviewObjectShapeManager::SysOverviewObjectShape &shape
        )
{
    this->shape = shape;
}

SysOvrvObjColorManagerPtr SysOverviewObjectShapeManager::getColorManager() const
{
    return SysOvrvObjColorManagerPtr(colorManager->clone());
}

void SysOverviewObjectShapeManager::setColorManager(
        SysOvrvObjColorManagerPtr colorManager
        )
{
    this->colorManager.reset(colorManager.release());
    sysOverviewObject->update();
}

void SysOverviewObjectShapeManager::paint(
        QPainter *painter,
        const QRectF &boundingRect,
        const ObjectState objectState
        )
{
    painter->save();

    QColor curObjFillColor;
    QColor curObjBorderColor =
            colorManager->getBorderColor();

    switch(objectState)
    {
    case ObjectState_Normal:
        curObjFillColor = colorManager->getFillColor();
        break;
    case ObjectState_Highlighted:
        curObjFillColor = colorManager->getHighlightFillColor();
        break;
    case ObjectState_Selected:
        curObjFillColor = colorManager->getHighlightFillColor();
        curObjFillColor.darker(100);
        curObjBorderColor = QColor(Qt::blue);
        break;
    case ObjectState_Disabled:
        curObjFillColor = QColor(Qt::gray);
        curObjBorderColor = QColor(Qt::lightGray);
        break;
    }

    painter->setBrush(QBrush(curObjFillColor));
    painter->setPen(curObjBorderColor);

    switch(shape)
    {
    case SysOvrvShape_Rectangle:
        painter->drawRect(boundingRect);
        break;
    case SysOvrvShape_Square:
        painter->drawRect(boundingRect);
        break;
    case SysOvrvShape_Ellipse:
        painter->drawEllipse(boundingRect);
        break;
    case SysOvrvShape_Circle:
        painter->drawEllipse(boundingRect);
        break;
    case SysOvrvShape_Triangle:
    {
        QPointF rectTopMiddle(
                    (
                        (
                            boundingRect.right() -
                            boundingRect.left()
                         ) /
                        2
                    ),
                    boundingRect.top()
                    );
        QPainterPath path(rectTopMiddle);

        path.lineTo(boundingRect.bottomRight());
        path.lineTo(boundingRect.bottomLeft());
        path.lineTo(rectTopMiddle);

        painter->drawPath(path);
    }
        break;
    }

    painter->restore();
}

void SysOverviewObjectShapeManager::update()
{
    sysOverviewObject->update();
}

QString SysOverviewObjectShapeManager::translateShapeToString(
        const SysOverviewObjectShapeManager::SysOverviewObjectShape &shape
        )
{
    switch(shape)
    {
    case SysOvrvShape_Rectangle:
        return QString("Rectangle");
        break;
    case SysOvrvShape_Square:
        return QString("Square");
        break;
    case SysOvrvShape_Ellipse:
        return QString("Ellipse");
        break;
    case SysOvrvShape_Circle:
        return QString("Circle");
        break;
    case SysOvrvShape_Triangle:
        return QString("Triangle");
        break;
    default:
        return QString("UNDEFINED");
    }
}

QStringList SysOverviewObjectShapeManager::listShapes()
{
    QStringList shapeNames;


    for(int cntr = 0; cntr < SysOvrvShape_NR_OF_SHAPES; ++cntr)
    {
        shapeNames << translateShapeToString(static_cast<SysOverviewObjectShape>(cntr));
    }

    return shapeNames;
}

