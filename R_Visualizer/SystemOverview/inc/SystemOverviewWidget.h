/**
 * @file SystemOverviewWidget.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The SystemOverviewWidget
 */
#ifndef SYSTEMOVERVIEWWIDGET_H
#define SYSTEMOVERVIEWWIDGET_H

#include <QWidget>
#include <QGraphicsScene>

#include <ISystemOverviewObjectStore.h>
#include <ISystemOverviewObject.h>

class ISystemOverview;

namespace Ui {
class SystemOverviewWidget;
}

/**
 * @brief The SystemOverviewWidget
 */
class SystemOverviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemOverviewWidget(
            ISystemOverview *systemOverview,
            QWidget *parent = Q_NULLPTR
            );
    virtual ~SystemOverviewWidget();

private:
    Ui::SystemOverviewWidget *ui;
    ISystemOverview *systemOverview;
    QGraphicsScene sysOvrvScene;
};

#endif // SYSTEMOVERVIEWWIDGET_H
