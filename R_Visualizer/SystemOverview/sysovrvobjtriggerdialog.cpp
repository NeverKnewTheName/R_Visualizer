#include "sysovrvobjtriggerdialog.h"
#include "ui_sysovrvobjtriggerdialog.h"

#include "sysovrvtriggermodel.h"
#include "sysovrvobject.h"
#include "sysovrvtriggereditorwidget.h"

#include <QStandardItem>


SysOvrvObjTriggerDialog::SysOvrvObjTriggerDialog(SysOvrvObject *sysOvrvObj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjTriggerDialog),
    ObjectToTrigger(sysOvrvObj),
    stdModel(new QStandardItemModel(this)),
    previewEditor(new SysOvrvTriggerEditorWidget(this))
{
    ui->setupUi(this);

    this->setupModel(sysOvrvObj);

    ui->TriggerColumnView->setPreviewWidget(previewEditor);
//    ui->TriggerColumnView->setResizeGripsVisible(false);

    ui->TriggerColumnView->setModel(stdModel);
//    ui->TriggerColumnView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    QList<int> sizes;
    sizes.append(200);
    sizes.append(200);
    sizes.append(200);
    sizes.append(previewEditor->sizeHint().width()+200);
    ui->TriggerColumnView->setColumnWidths(sizes);

//    connect(ui->TriggerColumnView, &QColumnView::updatePreviewWidget, this->previewEditor, &SysOvrvTriggerEditorWidget::RUpdatewidgetdata);
    connect(ui->TriggerColumnView, SIGNAL(updatePreviewWidget(QModelIndex)), previewEditor, SLOT(RUpdatewidgetdata(QModelIndex)));
}

SysOvrvObjTriggerDialog::~SysOvrvObjTriggerDialog()
{
    delete stdModel;
    delete previewEditor;
    delete ui;
}

void SysOvrvObjTriggerDialog::on_buttonBox_accepted()
{

}

void SysOvrvObjTriggerDialog::on_AddTriggerBtn_clicked()
{

}

void SysOvrvObjTriggerDialog::on_RemoveTriggerBtn_clicked()
{

}

void SysOvrvObjTriggerDialog::on_EditTriggerBtn_clicked()
{

}

void SysOvrvObjTriggerDialog::setupModel(SysOvrvObject *sysOvrvObj)
{
    stdModel->clear();
    QList<MsgIDType> idList = sysOvrvObj->getTriggerIDs();
    for( const MsgIDType &id : idList)
    {
        QStandardItem *pIDItem = new QStandardItem();
        pIDItem->setData(QVariant(id),Qt::DisplayRole);
        QList<MsgCodeType> codeList = sysOvrvObj->getTriggerCodesToID(id);
        for( const MsgCodeType &code : codeList )
        {
            QStandardItem *pCodeItem = new QStandardItem();
            pCodeItem->setData(QVariant(code),Qt::DisplayRole);
            QVector<SysOvrvTrigger*> triggerList = sysOvrvObj->getTriggersToIDandCode(id, code);
            for( SysOvrvTrigger *trigger : triggerList)
            {
                QStandardItem *pTriggerItem = new QStandardItem(trigger->printToString());
                pTriggerItem->setData(QVariant::fromValue(static_cast<void *>(trigger)));
                pCodeItem->appendRow(pTriggerItem);
            }
            pIDItem->appendRow(pCodeItem);
        }
        stdModel->appendRow(pIDItem);
    }

    stdModel->setHeaderData(0,Qt::Horizontal,QString("ID"),Qt::DisplayRole);
    stdModel->setHeaderData(1,Qt::Horizontal,QString("Code"),Qt::DisplayRole);
    stdModel->setHeaderData(2,Qt::Horizontal,QString("TriggerType"),Qt::DisplayRole);
}
