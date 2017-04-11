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
    explicit SystemOverviewWidget(QWidget *parent = 0);
    ~SystemOverviewWidget();

private:
    Ui::SystemOverviewWidget *ui;
};

#endif // SYSTEMOVERVIEWWIDGET_H
