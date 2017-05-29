#ifndef SYSOVRVTRIGGEREDITORWIDGET_H
#define SYSOVRVTRIGGEREDITORWIDGET_H

#include <QWidget>

#include "Msg.h"

class SysOvrvTrigger;
class EvaluatorTablemodel;
class TemplateValueEvaluator;

namespace Ui {
class SysOvrvTriggerEditorWidget;
}

class SysOvrvTriggerEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SysOvrvTriggerEditorWidget(QWidget *parent = 0);
    ~SysOvrvTriggerEditorWidget();

private:
    Ui::SysOvrvTriggerEditorWidget *ui;
    EvaluatorTablemodel *evaluatorModel;
    SysOvrvTrigger *triggerToEdit;
    MsgIDType currentID;
    MsgCodeType currentCode;


signals:

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void RUpdatewidgetdata(const QModelIndex &index);
    void on_IDLineEdit_textEdited(const QString &arg1);
    void on_AddEvaluatorPushButton_clicked();
    void EvaluatorAdded(TemplateValueEvaluator*evalToAdd);
    void on_EditEvaluatorPushButton_clicked();
    void on_RemoveEvaluatorPushButton_clicked();
    void on_TriggerTypeComboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void colorChanged(const QColor &newColor);
};

#endif // SYSOVRVTRIGGEREDITORWIDGET_H
