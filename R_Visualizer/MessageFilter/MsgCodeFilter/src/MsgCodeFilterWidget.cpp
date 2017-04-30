#include "MsgCodeFilterWidget.h"
#include "ui_msgcodefilterwidget.h"

#include <QFile>
#include <QFileDialog>

#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>

#include <QDebug>

#include "MsgCodeFilter.h"
#include "MsgCodeFilterModel.h"


MsgCodeFilterWidget::MsgCodeFilterWidget(
        MsgCodeFilter *msgCodeFilter,
        MsgCodeFilterModel *msgCodeFilterModel,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgCodeFilterWidget),
    msgCodeFilter(msgCodeFilter),
    msgCodeFilterModel(msgCodeFilterModel)
{
    init();
    ui->enableCodeFilterCheckBox->setChecked(
            msgCodeFilter->isFilterEnabled()
            );

    ui->invertCodeFilterCheckBox->setChecked(
            msgCodeFilter->isFilterInverted()
            );

    connect(
            ui->enableCodeFilterCheckBox,
            &QCheckBox::toggled,
            msgCodeFilter,
            &MsgCodeFilter::slt_enableFilter
            );
    connect(
            ui->invertCodeFilterCheckBox,
            &QCheckBox::toggled,
            msgCodeFilter,
            &MsgCodeFilter::slt_invertFilter
            );
}

MsgCodeFilterWidget::~MsgCodeFilterWidget()
{
    delete ui;
}

void MsgCodeFilterWidget::addMsgCode(
        const MsgCodeType &msgCodeToAdd
        )
{
    msgCodeFilter->addMsgCodeToFilter(msgCodeToAdd);
}

void MsgCodeFilterWidget::removeMsgCode(
        const MsgCodeType &msgCodeToRemove
        )
{
    msgCodeFilter->removeMsgCodeFromFilter(msgCodeToRemove);
}

void MsgCodeFilterWidget::on_filterCodeLoadBtn_clicked()
{

}

void MsgCodeFilterWidget::on_filterCodeStoreBtn_clicked()
{

}

void MsgCodeFilterWidget::on_addFilterCodePushButton_clicked()
{
    qsrand(qrand());
    MsgCodeType randomMsgCode(qrand() %100);

    slt_addMsgCode(randomMsgCode);
}

void MsgCodeFilterWidget::on_rmvFilterCodePushButton_clicked()
{
    QItemSelectionModel *selectionModel =
       ui->codeFilterListView->selectionModel();

    QModelIndexList selectionIndexList = selectionModel->selectedRows();

    if(selectionIndexList.size())
    {
        msgCodeFilterModel->removeRows(
                selectionIndexList.first().row(),
                selectionIndexList.size()
                );
    }
}

/* void MsgCodeFilterWidget::on_enableCodeFilterCheckBox_toggled(bool checked) */
/* { */

/* } */

/* void MsgCodeFilterWidget::on_invertCodeFilterCheckBox_toggled(bool checked) */
/* { */

/* } */

void MsgCodeFilterWidget::slt_addMsgCode(
        const MsgCodeType &msgCodeToAdd
        )
{
    addMsgCode(msgCodeToAdd);
}

void MsgCodeFilterWidget::slt_removeMsgCode(
        const MsgCodeType &msgCodeToRemove
        )
{
    removeMsgCode(msgCodeToRemove);
}

void MsgCodeFilterWidget::init()
{
    ui->setupUi(this);
    QSortFilterProxyModel *sortFilterProxyModel = new
        QSortFilterProxyModel(this);
    //ToDO... this is not good... maybe inherit from QAbstractItemModel directly in the interface?
    sortFilterProxyModel->setSourceModel(
            dynamic_cast<QAbstractItemModel*>(msgCodeFilterModel)
            );
    ui->codeFilterListView->setModel(sortFilterProxyModel);
    ui->codeFilterListView->setAlternatingRowColors(true);
    ui->codeFilterListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->codeFilterListView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->codeFilterListView->setEditTriggers(QAbstractItemView::DoubleClicked);
    //ToDO
    //ui->codeFilterListView->setItemDelegate(new CodeEditorDelegate(this));

    //ToDO SCROLL TO BOTTOM
}
