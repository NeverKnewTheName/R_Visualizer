#include "MsgIDFilterWidget.h"
#include "ui_msgidfilterwidget.h"

#include <QFile>
#include <QFileDialog>

#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>

#include <QDebug>

#include "MsgIDFilterModel.h"

MsgIDFilterWidget::MsgIDFilterWidget(
        MsgIDFilterModel *msgIDFilterModel,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgIDFilterWidget),
    msgIDFilterModel(msgIDFilterModel)
{
    init();
}

MsgIDFilterWidget::~MsgIDFilterWidget()
{
    delete ui;
}

void MsgIDFilterWidget::on_addFilterIDPushButton_clicked()
{
    qsrand(qrand());
    MsgIDType randomMsgID(qrand() %100);

    msgIDFilterModel->addMsgID(randomMsgID);
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

void MsgIDFilterWidget::on_enableIDFilterCheckBox_toggled(bool checked)
{

}

void MsgIDFilterWidget::on_checkBox_toggled(bool checked)
{

}

void MsgIDFilterWidget::slt_addMsgID(const MsgIDType &msgIDToAdd)
{
}

void MsgIDFilterWidget::slt_removeMsgID(const MsgIDType &msgIDToRemove)
{
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
