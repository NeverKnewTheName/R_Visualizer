/**
 * @file sysoverviewgraphicsview.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief Provides a GraphicsView specific for #SysOvrvObject
 */
#ifndef SYSOVERVIEWGRAPHICSVIEW_H
#define SYSOVERVIEWGRAPHICSVIEW_H

class QPointF;
class QContextMenuEvent;

#include <QGraphicsView>

class SysOvrvObject;

class SysOverviewGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    SysOverviewGraphicsView(QWidget *parent = Q_NULLPTR);

    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

    SysOvrvObject *getObjAtPos(const QPointF &pos) const;

    void enableEditing(const bool enable);

private:
    bool editingEnabled;

signals:
    void sgnl_addObjRequest(const QPointF &pos);
    void sgnl_updateObjRequest(SysOvrvObject *obj);
    void sgnl_removeObjRequest(SysOvrvObject *obj);
    void sgnl_duplicateObjRequest(SysOvrvObject *obj);
};

#endif // SYSOVERVIEWGRAPHICSVIEW_H
