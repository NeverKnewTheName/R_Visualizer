#ifndef SYSOVERVIEWOBJECTTRIGGERMSGTYPEEVALUATORDIALOG_H
#define SYSOVERVIEWOBJECTTRIGGERMSGTYPEEVALUATORDIALOG_H

#include <QWidget>

#include "ISysOverviewObjectTriggerEvaluator.h"

class MessageTypeIdentifier;
class IMsgIDMappingManager;
class IMsgCodeMappingManager;

namespace Ui {
class SysOverviewObjectTriggerMsgTypeEvaluatorDialog;
}

class SysOverviewObjectTriggerMsgTypeEvaluatorDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SysOverviewObjectTriggerMsgTypeEvaluatorDialog(QWidget *parent = 0);
    ~SysOverviewObjectTriggerMsgTypeEvaluatorDialog();

    MessageTypeIdentifier getMsgType() const;

    SysOvrvObjTriggerEvaluatorPtr getEvaluator() const;

    void setMsgIDMappingManager(
            IMsgIDMappingManager *msgIDMappingManager
            );
    void setMsgCodeMappingManager(
            IMsgCodeMappingManager *msgCodeMappingManager
            );

private:
    Ui::SysOverviewObjectTriggerMsgTypeEvaluatorDialog *ui;
};

#endif // SYSOVERVIEWOBJECTTRIGGERMSGTYPEEVALUATORDIALOG_H
