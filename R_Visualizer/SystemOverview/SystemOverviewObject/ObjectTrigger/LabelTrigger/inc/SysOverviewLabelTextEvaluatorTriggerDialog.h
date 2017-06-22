#ifndef SYSOVERVIEWLABELTEXTEVALUATORTRIGGERDIALOG_H
#define SYSOVERVIEWLABELTEXTEVALUATORTRIGGERDIALOG_H

#include <QDialog>

#include "ISysOverviewLabelTrigger.h"

#include "SysOverviewTextLabel.h"

class IMsgIDMappingManager;
class IMsgCodeMappingManager;

namespace Ui {
class SysOverviewLabelTextEvaluatorTriggerDialog;
}

class SysOverviewLabelTextEvaluatorTriggerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SysOverviewLabelTextEvaluatorTriggerDialog(
            SysOverviewTextLabel *textLabel,
            QWidget *parent = 0
            );
    ~SysOverviewLabelTextEvaluatorTriggerDialog();

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
    Ui::SysOverviewLabelTextEvaluatorTriggerDialog *ui;
    SysOverviewTextLabel *textLabel;
};

#endif // SYSOVERVIEWLABELTEXTEVALUATORTRIGGERDIALOG_H
