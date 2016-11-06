#include "sysovrvtriggereditorwidget.h"
#include "ui_sysovrvtriggereditorwidget.h"

#include "sysovrvtrigger.h"
#include "../R_Visualizer_Utilities/templatevalueevaluatorcreatorwidget.h"
#include "../R_Visualizer_Utilities/templatevalueevaluator.h"

#include "evaluatortablemodel.h"

#include <QDialog>

#include <QDebug>

SysOvrvTriggerEditorWidget::SysOvrvTriggerEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SysOvrvTriggerEditorWidget),
    evaluatorModel(new EvaluatorTablemodel(this))
{
    ui->setupUi(this);

    ui->EvaluatorTableView->setModel(evaluatorModel);
    ui->EvaluatorTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->EvaluatorTableView->horizontalHeader()->setStretchLastSection(true);
    ui->EvaluatorTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

SysOvrvTriggerEditorWidget::~SysOvrvTriggerEditorWidget()
{
    delete ui;
}

void SysOvrvTriggerEditorWidget::RUpdatewidgetdata(const QModelIndex &index)
{
    triggerToEdit = static_cast<SysOvrvTrigger*>(index.data(Qt::UserRole+1).value<void *>());
    currentID = static_cast<quint16>(index.parent().parent().data().toUInt());
    currentCode = static_cast<quint8>(index.parent().data().toUInt());
    ui->IDLineEdit->setText(QString::number(currentID));
    ui->CodeLineEdit->setText(QString::number(currentCode));
//    TemplateValueEvaluator *evaluator = triggerToEdit->getEvaluator(); //should be a list... damn dude!
//    evaluatorModel->appendRow(evaluator);
}

void SysOvrvTriggerEditorWidget::on_buttonBox_accepted()
{
    qDebug() << "SysOvrvTriggerEditorWidget accepted!";
    triggerToEdit->printToString();
}

void SysOvrvTriggerEditorWidget::on_buttonBox_rejected()
{
    qDebug() << "SysOvrvTriggerEditorWidget rejected";
}

void SysOvrvTriggerEditorWidget::on_IDLineEdit_textEdited(const QString &arg1)
{

}

void SysOvrvTriggerEditorWidget::on_AddEvaluatorPushButton_clicked()
{
    TemplateValueEvaluatorCreatorWidget *EvalEditor = new TemplateValueEvaluatorCreatorWidget(this);
    EvalEditor->setWindowFlags(Qt::Dialog);
    connect(EvalEditor, SIGNAL(newTemplateValueEvaluatorCreated(TemplateValueEvaluator*)),this->evaluatorModel, SLOT(appendRow(TemplateValueEvaluator*)));
    EvalEditor->show();
}

void SysOvrvTriggerEditorWidget::on_EditEvaluatorPushButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->EvaluatorTableView->selectionModel();
    QModelIndexList selectionIndexList = selectionModel->selectedRows();
    for(QModelIndex &index : selectionIndexList)
    {
        TemplateValueEvaluator *EvalToEdit = static_cast<TemplateValueEvaluator*>(this->evaluatorModel->data(index, Qt::EditRole).value<void *>());
        TemplateValueEvaluatorCreatorWidget *EvalEditor = new TemplateValueEvaluatorCreatorWidget(EvalToEdit, this);
        EvalEditor->setWindowFlags(Qt::Dialog);
        connect(EvalEditor, SIGNAL(newTemplateValueEvaluatorCreated(TemplateValueEvaluator*)),this->evaluatorModel, SLOT(resetInternalData()));
        EvalEditor->show();
    }

}

void SysOvrvTriggerEditorWidget::on_RemoveEvaluatorPushButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->EvaluatorTableView->selectionModel();
    QModelIndexList selectionIndexList = selectionModel->selectedRows();
    if(selectionIndexList.size())
    {
        this->evaluatorModel->removeRows(selectionIndexList.first().row(), selectionIndexList.size());
    }
}
