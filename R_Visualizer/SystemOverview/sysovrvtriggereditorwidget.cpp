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
    evaluatorModel(NULL)
{
    ui->setupUi(this);
    ui->EvaluatorTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

SysOvrvTriggerEditorWidget::~SysOvrvTriggerEditorWidget()
{
    if(evaluatorModel != NULL)
        delete evaluatorModel;
    delete ui;
}

void SysOvrvTriggerEditorWidget::RUpdatewidgetdata(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    EvaluatorTablemodel *oldModel = evaluatorModel;

    evaluatorModel = new EvaluatorTablemodel(this);
    ui->EvaluatorTableView->setModel(evaluatorModel);

    if( oldModel != NULL )
    {
        delete oldModel;
    }

    triggerToEdit = static_cast<SysOvrvTrigger*>(index.data(Qt::UserRole+1).value<void *>());
    currentID = static_cast<quint16>(index.parent().parent().data().toUInt());
    currentCode = static_cast<quint8>(index.parent().data().toUInt());
    ui->IDLineEdit->setText(QString::number(currentID));
    ui->CodeLineEdit->setText(QString::number(currentCode));
    QVector<TemplateValueEvaluator*> evaluatorList = triggerToEdit->getEvaluators();
    for(TemplateValueEvaluator *evaluator : evaluatorList)
    {
        evaluatorModel->appendRow(evaluator);
    }
}

void SysOvrvTriggerEditorWidget::on_buttonBox_accepted()
{
    qDebug() << "SysOvrvTriggerEditorWidget accepted!";
    //    triggerToEdit->printToString();
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
    connect(EvalEditor, SIGNAL(newTemplateValueEvaluatorCreated(TemplateValueEvaluator*)),this, SLOT(EvaluatorAdded(TemplateValueEvaluator*)));
    EvalEditor->setAttribute(Qt::WA_DeleteOnClose, true);
    EvalEditor->setWindowModality(Qt::WindowModal);
    EvalEditor->show();
}

void SysOvrvTriggerEditorWidget::EvaluatorAdded(TemplateValueEvaluator *evalToAdd)
{
    triggerToEdit->addEvaluator(evalToAdd);
    evaluatorModel->appendRow(evalToAdd);
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
    for( QModelIndex &index : selectionIndexList)
    {
        TemplateValueEvaluator *EvalToDelete = static_cast<TemplateValueEvaluator*>(index.data(Qt::EditRole).value<void *>());
        this->evaluatorModel->removeRow(EvalToDelete);
        triggerToEdit->removeEvaluator(EvalToDelete);
        delete EvalToDelete;
    }
}
