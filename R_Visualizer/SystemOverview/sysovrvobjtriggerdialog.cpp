#include "sysovrvobjtriggerdialog.h"
#include "ui_sysovrvobjtriggerdialog.h"

#include "sysovrvtriggermodel.h"
#include "sysovrvobject.h"

#include <QStandardItem>

Q_DECLARE_METATYPE(QList<quint16>)
Q_DECLARE_METATYPE(QList<quint8>)

SysOvrvObjTriggerDialog::SysOvrvObjTriggerDialog(SysOvrvObject *sysOvrvObj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysOvrvObjTriggerDialog),
    ObjectToTrigger(sysOvrvObj)
{
    ui->setupUi(this);
//    TriggerModel = new SysOvrvTriggerModel(this);
    stdModel = new QStandardItemModel(this);
    QList<quint16> idList = sysOvrvObj->getTriggerIDs();
    for( quint16 id : idList)
    {
        QStandardItem *pIDItem = new QStandardItem();
        pIDItem->setData(QVariant(id),Qt::DisplayRole);
        QList<quint8> codeList = sysOvrvObj->getTriggerCodesToID(id);
        for( quint8 code : codeList )
        {
            QStandardItem *pCodeItem = new QStandardItem();
            pCodeItem->setData(QVariant(code),Qt::DisplayRole);
            QVector<SysOvrvTrigger*> triggerList = sysOvrvObj->getTriggersToIDandCode(id, code);
            for( SysOvrvTrigger * trigger : triggerList)
            {
                QStandardItem *pTriggerItem = new QStandardItem(trigger->printToString());
//                pTriggerItem->setData(QVariant(static_cast<void *>(trigger)));
                pCodeItem->appendRow(pTriggerItem);
            }
//            pCodeItem->setData(QVariant(triggerList));
            pIDItem->appendRow(pCodeItem);
        }
//        pIDItem->setData(QVariant(codeList));
        stdModel->appendRow(pIDItem);
    }
//    stdModel->invisibleRootItem()->setData(QVariant(idList));
//    stdModel->setHorizontalHeaderItem(0, new QStandardItem("ID"));
//    stdModel->setHorizontalHeaderItem(1, new QStandardItem("Code"));
//    stdModel->setHorizontalHeaderItem(2, new QStandardItem("TriggerType"));
//    QStringList headers;
//    headers << "ID" << "Code" << "TriggerType";
//    stdModel->setHorizontalHeaderLabels(headers);
//    stdModel->setHeaderData(0,Qt::Horizontal,QString("ID"),Qt::DisplayRole);
//    stdModel->setHeaderData(1,Qt::Horizontal,QString("Code"),Qt::DisplayRole);
//    stdModel->setHeaderData(2,Qt::Horizontal,QString("TriggerType"),Qt::DisplayRole);

    ui->TriggerColumnView->setModel(stdModel);
}

SysOvrvObjTriggerDialog::~SysOvrvObjTriggerDialog()
{
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
