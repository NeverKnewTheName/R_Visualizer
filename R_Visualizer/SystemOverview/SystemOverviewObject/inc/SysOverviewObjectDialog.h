#ifndef SYSOVERVIEWOBJECTDIALOG_H
#define SYSOVERVIEWOBJECTDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QSharedPointer>
#include <QAbstractButton>

#include "ISystemOverviewObject.h"
#include "SystemOverviewObject.h"
#include "SysOverviewTextLabel.h"

namespace Ui {
class SysOverviewObjectDialog;
}

class SysOverviewObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SysOverviewObjectDialog(
            ISysOvrvObjPtr sysOvrvObj,
            QWidget *parent = Q_NULLPTR
            );

    ~SysOverviewObjectDialog();
    ISysOvrvObjPtr getObject() const;

private:
    void setupDialog();
    void setupButtons();
    void saveSysOverviewObj();
    void openSysOverviewObj();

signals:
    void sgnl_CommitObject(ISysOvrvObjPtr obj);

private slots:
    void on_colorPickerBtn_clicked();

    void on_addObjectBtn_clicked();

    void on_removeObjectBtn_clicked();

    void on_editObjectBtn_clicked();

    void on_addLabelBtn_clicked();

    void on_removeLabelBtn_clicked();

    void on_addTriggerBtn_clicked();

    void on_removeTriggerBtn_clicked();

    void on_editTriggerBtn_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_nameLE_editingFinished();

    void on_buttonBox_rejected();

private:
    static void setupSysOvrvObj(ISysOvrvObjPtr obj);
    static void setupChildSysOvrvObj(ISysOvrvObjPtr obj);
    static void prepareSysOvrvObjForCommit(ISysOvrvObjPtr obj);

private:
    Ui::SysOverviewObjectDialog *ui;
    QGraphicsScene scene;
    ISysOvrvObjPtr sysOvrvObj;
    ISysOvrvObjPtr sysOvrvObjSave;

    ISysOvrvObjPtr selectedObj;
    SysOvrvTextLabelPtr selectedTextLabel;
};

#endif // SYSOVERVIEWOBJECTDIALOG_H
