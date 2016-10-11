#ifndef SYSOVERVIEWGRAPHICSVIEW_H
#define SYSOVERVIEWGRAPHICSVIEW_H

#include "sysovrvobjectstore.h"

#include <QGraphicsView>

class SysOverviewGraphicsView : public QGraphicsView
{
public:
    SysOverviewGraphicsView(QWidget *parent = 0);

    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

    SysOvrvObject *getCurrentObject() const;
    SysOvrvObjectStore *getObjectStore() const;
    const QPointF &GetCurrentMousePos() const;

private:
    SysOvrvObjectStore *sysOvrvObjStore;
    SysOvrvObject *currentObject;
    QPointF currentMousePos;
};

#endif // SYSOVERVIEWGRAPHICSVIEW_H
