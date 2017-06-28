#ifndef SYSOVERVIEWOBJECTSHAPEMANAGERWIDGET_H
#define SYSOVERVIEWOBJECTSHAPEMANAGERWIDGET_H

#include "ISysOverviewObjectManagerSubWidget.h"

#include "ISystemOverviewObject.h"

namespace Ui {
class SysOverviewObjectShapeManagerWidget;
}

class SysOverviewObjectShapeManagerWidget : public ISysOverviewObjectManagerSubWidget
{
    Q_OBJECT

public:
    explicit SysOverviewObjectShapeManagerWidget(
            ISysOvrvObjPtr sysOvrvObj,
            QWidget *parent = Q_NULLPTR
            );
    ~SysOverviewObjectShapeManagerWidget();

private:
    void setupWidget();

private slots:
    void on_shapeComboBox_currentIndexChanged(int index);

    void on_transparencySpinBox_valueChanged(int arg1);

    void on_colorLE_editingFinished();

private:
    Ui::SysOverviewObjectShapeManagerWidget *ui;
    ISysOvrvObjPtr sysOvrvObj;

    // ISysOverviewObjectManagerSubWidget interface
public:
    virtual void updateSysOverviewObject(ISysOvrvObjPtr sysOvrvObj);
};

#endif // SYSOVERVIEWOBJECTSHAPEMANAGERWIDGET_H
