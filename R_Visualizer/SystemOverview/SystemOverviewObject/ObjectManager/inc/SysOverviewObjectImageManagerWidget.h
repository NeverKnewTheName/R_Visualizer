#ifndef SYSOVERVIEWOBJECTIMAGEMANAGERWIDGET_H
#define SYSOVERVIEWOBJECTIMAGEMANAGERWIDGET_H

#include "ISysOverviewObjectManagerSubWidget.h"

namespace Ui {
class SysOverviewObjectImageManagerWidget;
}

class SysOverviewObjectImageManagerWidget : public ISysOverviewObjectManagerSubWidget
{
    Q_OBJECT

public:
    explicit SysOverviewObjectImageManagerWidget(
            ISysOvrvObjPtr sysOvrvObj,
            QWidget *parent = Q_NULLPTR
            );
    ~SysOverviewObjectImageManagerWidget();

private slots:
    void on_imagePickerBtn_clicked();

    void on_applyBtn_clicked();

    void on_imagePathLineEdit_editingFinished();

private:
    Ui::SysOverviewObjectImageManagerWidget *ui;
    ISysOvrvObjPtr sysOvrvObj;

    // ISysOverviewObjectManagerSubWidget interface
public:
    virtual void updateSysOverviewObject(ISysOvrvObjPtr sysOvrvObj);
};

#endif // SYSOVERVIEWOBJECTIMAGEMANAGERWIDGET_H
