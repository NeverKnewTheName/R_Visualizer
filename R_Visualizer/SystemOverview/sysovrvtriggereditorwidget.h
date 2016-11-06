#ifndef SYSOVRVTRIGGEREDITORWIDGET_H
#define SYSOVRVTRIGGEREDITORWIDGET_H

#include <QWidget>

class SysOvrvTrigger;
class EvaluatorTablemodel;

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
    quint16 currentID;
    quint8 currentCode;


signals:

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void RUpdatewidgetdata(const QModelIndex &index);
    void on_IDLineEdit_textEdited(const QString &arg1);
    void on_AddEvaluatorPushButton_clicked();
    void on_EditEvaluatorPushButton_clicked();
    void on_RemoveEvaluatorPushButton_clicked();
};

#endif // SYSOVRVTRIGGEREDITORWIDGET_H
