/**
 *  @file SystemOverviewGraphicsView.h
 * @author Christian Neuberger
 * @date date
 *
 * @brief Modified QGraphicsView for the SystemOverview
 */
#ifndef SYSTEMOVERVIEWGRAPHICSVIEW_H
#define SYSTEMOVERVIEWGRAPHICSVIEW_H

#include <QGraphicsView>

class ISystemOverviewObject;

/**
 * @brief The SystemOverviewGraphicsView class
 */
class SystemOverviewGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    SystemOverviewGraphicsView(QWidget *parent = Q_NULLPTR);

signals:
    void sgnl_RequestAddObject(const QPointF &position);
    void sgnl_RequestRemoveObject(ISystemOverviewObject *objectToRemove);
    void sgnl_RequestEditObject(ISystemOverviewObject *objectToEdit);

protected:
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // SYSTEMOVERVIEWGRAPHICSVIEW_H
