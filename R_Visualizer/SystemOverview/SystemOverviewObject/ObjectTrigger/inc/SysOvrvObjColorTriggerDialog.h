#ifndef SYSOVRVOBJCOLORTRIGGERDIALOG_H
#define SYSOVRVOBJCOLORTRIGGERDIALOG_H

#include <QDialog>

#include "ISysOverviewObjectTrigger.h"

class ISystemOverviewObject;

class IMsgIDMappingManager;
class IMsgCodeMappingManager;

namespace Ui {
class SysOvrvObjColorTriggerDialog;
}

class SysOvrvObjColorTriggerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SysOvrvObjColorTriggerDialog(
            ISystemOverviewObject *sysOvrvObject,
            QWidget *parent = 0
            );
    ~SysOvrvObjColorTriggerDialog();

    void setMsgIDMappingManager(
            IMsgIDMappingManager *msgIDMappingManager
            );
    void setMsgCodeMappingManager(
            IMsgCodeMappingManager *msgCodeMappingManager
            );

signals:
    void sgnl_commitTrigger(SysOvrvObjTriggerPtr triggerToCommit);

private slots:
    void on_triggerColorLE_editingFinished();

    void on_buttonBox_accepted();

private:
    Ui::SysOvrvObjColorTriggerDialog *ui;
    ISystemOverviewObject *sysOvrvObject;
};

#endif // SYSOVRVOBJCOLORTRIGGERDIALOG_H
