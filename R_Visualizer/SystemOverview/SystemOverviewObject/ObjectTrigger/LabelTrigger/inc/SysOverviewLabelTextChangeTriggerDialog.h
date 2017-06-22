#ifndef SYSOVERVIEWLABELTEXTCHANGETRIGGERDIALOG_H
#define SYSOVERVIEWLABELTEXTCHANGETRIGGERDIALOG_H

#include <QDialog>

#include "ISysOverviewLabelTrigger.h"

#include "SysOverviewTextLabel.h"

class IMsgIDMappingManager;
class IMsgCodeMappingManager;

namespace Ui {
class SysOverviewLabelTextChangeTriggerDialog;
}

class SysOverviewLabelTextChangeTriggerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SysOverviewLabelTextChangeTriggerDialog(
            SysOverviewTextLabel *textLabel,
            QWidget *parent = 0
            );
    ~SysOverviewLabelTextChangeTriggerDialog();

    void setMsgIDMappingManager(
            IMsgIDMappingManager *msgIDMappingManager
            );
    void setMsgCodeMappingManager(
            IMsgCodeMappingManager *msgCodeMappingManager
            );

signals:
    void sgnl_commitTrigger(SysOvrvLabelTriggerPtr triggerToCommit);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SysOverviewLabelTextChangeTriggerDialog *ui;
    SysOverviewTextLabel *textLabel;
};

#endif // SYSOVERVIEWLABELTEXTCHANGETRIGGERDIALOG_H
