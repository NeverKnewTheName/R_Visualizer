#include "SysOverviewObjectColorManager.h"

#include "SysOverviewObjectShapeManager.h"

SysOverviewObjectColorManager::SysOverviewObjectColorManager(
        SysOverviewObjectShapeManager *shapeManager,
        const QColor &fillColor,
        const QColor &borderColor
        ) :
    shapeManager(shapeManager),
    fillColor(fillColor),
    borderColor(borderColor)
{

}

SysOverviewObjectColorManager::SysOverviewObjectColorManager(
        const SysOverviewObjectColorManager &copy
        ) :
    shapeManager(copy.shapeManager),
    fillColor(copy.fillColor),
    borderColor(copy.borderColor)
{

}

void SysOverviewObjectColorManager::setFillColor(const QColor &color)
{
    fillColor = color;
    shapeManager->update();
}

QColor SysOverviewObjectColorManager::getFillColor() const
{
    return fillColor;
}

QColor SysOverviewObjectColorManager::getHighlightFillColor() const
{
    QColor curObjColor(fillColor);

    if(curObjColor.alphaF()<0.1)
    {
        curObjColor.setAlphaF(0.1);
    }
    curObjColor = curObjColor.darker();

    return curObjColor;
}

void SysOverviewObjectColorManager::setBorderColor(const QColor &color)
{
    borderColor = color;
    shapeManager->update();
}

QColor SysOverviewObjectColorManager::getBorderColor() const
{
    return borderColor;
}

void SysOverviewObjectColorManager::setTransparency(const qreal transparency)
{
    fillColor.setAlphaF(transparency);
    shapeManager->update();
}

qreal SysOverviewObjectColorManager::getTransparency() const
{
    return fillColor.alphaF();
}

void SysOverviewObjectColorManager::setShapeManager(
        SysOverviewObjectShapeManager *shapeManager
        )
{
    this->shapeManager = shapeManager;
}
