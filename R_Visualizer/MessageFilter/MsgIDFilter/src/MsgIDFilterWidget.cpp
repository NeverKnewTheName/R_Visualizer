#include "MsgIDFilterWidget.h"
#include "ui_msgidfilterwidget.h"

#include <QFile>
#include <QFileDialog>

#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>

#include <QDebug>

#include "MsgIDFilter.h"
#include "MsgIDFilterModel.h"

MsgIDFilterWidget::MsgIDFilterWidget(
        MsgIDFilter *msgIDFilter,
        MsgIDFilterModel *msgIDFilterModel,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgIDFilterWidget),
    msgIDFilter(msgIDFilter),
    msgIDFilterModel(msgIDFilterModel)
{
    init();

    ui->enableIDFilterCheckBox->setChecked(
            msgIDFilter->isFilterEnabled()
            );

    ui->invertIDFilterCheckBox->setChecked(
            msgIDFilter->isFilterInverted()
            );

    connect(
            ui->enableIDFilterCheckBox,
            &QCheckBox::toggled,
            msgIDFilter,
            &MsgIDFilter::slt_enableFilter
            );
    connect(
            ui->invertIDFilterCheckBox,
            &QCheckBox::toggled,
            msgIDFilter,
            &MsgIDFilter::slt_invertFilter
            );
}

MsgIDFilterWidget::~MsgIDFilterWidget()
{
    delete ui;
}

void MsgIDFilterWidget::on_addFilterIDPushButton_clicked()
{
    qsrand(qrand());
    MsgIDType randomMsgID(qrand() %100);

    slt_addMsgID(randomMsgID);
}

void MsgIDFilterWidget::on_rmvFilterIDPushButton_clicked()
{
    QItemSelectionModel *selectionModel =
       ui->idFilterListView->selectionModel();

    QModelIndexList selectionIndexList = selectionModel->selectedRows();

    if(selectionIndexList.size())
    {
        msgIDFilterModel->removeRows(
                selectionIndexList.first().row(),
                selectionIndexList.size()
                );
    }
}

void MsgIDFilterWidget::on_filterIDSaveBtn_clicked()
{

}

void MsgIDFilterWidget::on_filterIDLoadBtn_clicked()
{

}

/* void MsgIDFilterWidget::on_enableIDFilterCheckBox_toggled(bool checked) */
/* { */
/*     msgIDFilter->enableFilter(checked); */
/* } */

/* void MsgIDFilterWidget::on_checkBox_toggled(bool checked) */
/* { */
/*     msgIDFilter->invertFilter(checked); */
/* } */

void MsgIDFilterWidget::slt_addMsgID(const MsgIDType &msgIDToAdd)
{
    msgIDFilter->addMsgIDToFilter(msgIDToAdd);
}

void MsgIDFilterWidget::slt_removeMsgID(const MsgIDType &msgIDToRemove)
{
    msgIDFilter->removeMsgIDFromFilter(msgIDToRemove);
}

void MsgIDFilterWidget::init()
{
    ui->setupUi(this);
    QSortFilterProxyModel *sortFilterProxyModel = new
        QSortFilterProxyModel(this);
    //ToDO... this is not good... maybe inherit from QAbstractItemModel directly in the interface?
    sortFilterProxyModel->setSourceModel(
            dynamic_cast<QAbstractItemModel*>(msgIDFilterModel)
            );
    ui->idFilterListView->setModel(sortFilterProxyModel);
    ui->idFilterListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idFilterListView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    //ToDO
    //ui->idFilterListView->setItemDelegate(new IDEditorDelegate(this));

    //ToDO SCROLL TO BOTTOM
}
