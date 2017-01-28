#ifndef SYSOVRVOBJTRIGGERDIALOG_H
#define SYSOVRVOBJTRIGGERDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

class SysOvrvObject;
class SysOvrvTriggerModel;
class SysOvrvTriggerEditorWidget;

namespace Ui {
class SysOvrvObjTriggerDialog;
}

class SysOvrvObjTriggerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SysOvrvObjTriggerDialog(SysOvrvObject *sysOvrvObj, QWidget *parent = 0);
    ~SysOvrvObjTriggerDialog();

private slots:
    void on_buttonBox_accepted();

    void on_AddTriggerBtn_clicked();

    void on_RemoveTriggerBtn_clicked();

    void on_EditTriggerBtn_clicked();

private:
    void setupModel(SysOvrvObject *sysOvrvObj);

    Ui::SysOvrvObjTriggerDialog *ui;
    SysOvrvObject *ObjectToTrigger;
    SysOvrvTriggerModel *TriggerModel;
    QStandardItemModel *stdModel;
    SysOvrvTriggerEditorWidget *previewEditor;
};

#endif // SYSOVRVOBJTRIGGERDIALOG_H
