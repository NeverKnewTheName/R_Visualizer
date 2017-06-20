#ifndef SYSOVERVIEWOBJECTMANAGERWIDGET_H
#define SYSOVERVIEWOBJECTMANAGERWIDGET_H

#include <QWidget>

#include "ISystemOverviewObject.h"

namespace Ui {
class SysOverviewObjectManagerWidget;
}

class SysOverviewObjectManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SysOverviewObjectManagerWidget(
            QWidget *parent = Q_NULLPTR
            );
    explicit SysOverviewObjectManagerWidget(
            ISysOvrvObjPtr sysOvrvObj,
            QWidget *parent = Q_NULLPTR
            );
    ~SysOverviewObjectManagerWidget();

    void updateSysOverviewObject(ISysOvrvObjPtr sysOvrvObj);

private:
    void setupWidget();

private slots:
    void on_objectTypeComboBox_currentIndexChanged(int index);

private:
    Ui::SysOverviewObjectManagerWidget *ui;
    ISysOvrvObjPtr sysOvrvObj;
};

#endif // SYSOVERVIEWOBJECTMANAGERWIDGET_H
