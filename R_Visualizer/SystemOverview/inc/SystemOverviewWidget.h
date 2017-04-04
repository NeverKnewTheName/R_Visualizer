#ifndef SYSTEMOVERVIEWWIDGET_H
#define SYSTEMOVERVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class SystemOverviewWidget;
}

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
