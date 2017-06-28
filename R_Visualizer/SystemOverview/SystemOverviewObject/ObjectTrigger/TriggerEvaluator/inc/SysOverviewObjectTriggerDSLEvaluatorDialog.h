#ifndef SYSOVERVIEWOBJECTTRIGGERDSLEVALUATORDIALOG_H
#define SYSOVERVIEWOBJECTTRIGGERDSLEVALUATORDIALOG_H

#include <QWidget>

#include "ISysOverviewObjectTriggerEvaluator.h"

class MessageTypeIdentifier;
class IMsgIDMappingManager;
class IMsgCodeMappingManager;

namespace Ui {
class SysOverviewObjectTriggerDSLEvaluatorDialog;
}

class SysOverviewObjectTriggerDSLEvaluatorDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SysOverviewObjectTriggerDSLEvaluatorDialog(QWidget *parent = 0);
    ~SysOverviewObjectTriggerDSLEvaluatorDialog();

    MessageTypeIdentifier getMsgType() const;

    SysOvrvObjTriggerEvaluatorPtr getEvaluator() const;

    void setMsgIDMappingManager(
            IMsgIDMappingManager *msgIDMappingManager
            );
    void setMsgCodeMappingManager(
            IMsgCodeMappingManager *msgCodeMappingManager
            );

private:
    Ui::SysOverviewObjectTriggerDSLEvaluatorDialog *ui;
};

#endif // SYSOVERVIEWOBJECTTRIGGERDSLEVALUATORDIALOG_H
