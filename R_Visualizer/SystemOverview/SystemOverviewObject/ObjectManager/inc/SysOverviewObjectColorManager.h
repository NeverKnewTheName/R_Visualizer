#ifndef SYSOVERVIEWOBJECTCOLORMANAGER_H
#define SYSOVERVIEWOBJECTCOLORMANAGER_H

#include "ISysOverviewObjectColorManager.h"

class SysOverviewObjectShapeManager;

class SysOverviewObjectColorManager :
        public ISysOverviewObjectColorManagerCRTPHelper<SysOverviewObjectColorManager>
{
public:
    SysOverviewObjectColorManager(
            SysOverviewObjectShapeManager *shapeManager,
            const QColor &fillColor = QColor(Qt::lightGray),
            const QColor &borderColor = QColor(Qt::black)
            );

    SysOverviewObjectColorManager(
            const SysOverviewObjectColorManager &copy
            );

    // ISysOverviewObjectColorManager interface
public:
    virtual void setFillColor(const QColor &color);
    virtual QColor getFillColor() const;
    virtual QColor getHighlightFillColor() const;

    virtual void setBorderColor(const QColor &color);
    virtual QColor getBorderColor() const;

    virtual void setTransparency(const qreal transparency);
    virtual qreal getTransparency() const;

    virtual void setShapeManager(SysOverviewObjectShapeManager *shapeManager);

private:
    SysOverviewObjectShapeManager *shapeManager;
    QColor fillColor;
    QColor borderColor;

};

#endif // SYSOVERVIEWOBJECTCOLORMANAGER_H
