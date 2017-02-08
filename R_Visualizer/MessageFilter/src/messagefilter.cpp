#include "messagefilter.h"
#include "ui_messagefilter.h"

#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QAbstractItemView>

#include "filteriddelegate.cpp"
#include "filtermsgtypedelegate.cpp"

#include "filteridadddialog.h"
#include "filtercodeadddialog.h"

MessageFilter::MessageFilter(
            const IDModel &idModel,
            const MsgTypeModel &msgTypeModel,
            QWidget *parent = 0
        ) :
    QWidget(parent),
    ui(new Ui::MessageFilter),
    filterIDModel(),
    filterCodeModel(),
    filterTimestampModel()
{
    ui->setupUi(this);
    initFilterIDListView();
    initFilterCodeListView();
    initFilterTimestamp();

}

MessageFilter::~MessageFilter()
{
    delete ui;
}


void MessageFilter::initFilterIDListView(const IDModel &idModel)
{
    //    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    //    proxy->setSourceModel(&filterIDModel);
    
    //THE VIEW DOES NOT TAKE OWNERSHIP OF THE MODEL!!!
    ui->idFilterlistView->setModel(&filterIDModel);
    //ui->idFilterlistView->setModel(proxy);
    ui->idFilterlistView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->idFilterlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->idFilterlistView->setAlternatingRowColors(true);
    ui->idFilterlistView->setItemDelegate(new FilterIDDelegate(&idModel, ui->idFilterlistView));

    /* connect( */
    /*         &filterIDModel, */
    /*         &FilterIDStore::rowAdded, */
    /*         ui->idFilterlistView, */
    /*         static_cast<void (QListView::*)(const QModelIndex &)>(&QListView::edit) */
    /*         ); */
}

void MessageFilter::initFilterCodeListView(const MsgTypeModel &msgTypeModel)
{
    //    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    //    proxy->setSourceModel(&filterCodeModel);
    
    //THE VIEW DOES NOT TAKE OWNERSHIP OF THE MODEL!!!
    ui->codeFilterlistView->setModel(&filterCodeModel);
    //ui->codeFilterlistView->setModel(proxy);
    ui->codeFilterlistView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->codeFilterlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->codeFilterlistView->setAlternatingRowColors(true);
    ui->codeFilterlistView->setItemDelegate(new FilterMsgTypeDelegate(&msgTypeModel, ui->codeFilterlistView));

    /* connect( */
    /*         &filterCodeModel, */
    /*         &FilterCodeStore::rowAdded, */
    /*         ui->codeFilterlistView, */
    /*         static_cast<void (QListView::*)(const QModelIndex &)>(&QListView::edit) */
    /*         ); */
}

void MessageFilter::initFilterTimestamp()
{
    //WhatToDo?
    filterTimestampModel.setTimestampFilterTo(ui->filterTimestampToDateTimeEdit->DateTime());
    filterTimestampModel.setTimestampFilterFrom(ui->filterTimestampFromDateTimeEdit->DateTime());
}

const FilterIDStore &MessageFilter::getFilterIDModel() const
{
    return FilterIDModel;
}

const FilterCodeStore &MessageFilter::getFilterCodeModel() const
{
    return FilterCodeModel;
}

const FilterTimestampStore &MessageFilter::getFilterTimestampModel() const
{
    return filterTimestampModel;
}

void MessageFilter::on_enableIDFilterCheckBox_toggled(bool checked)
{
    emit sgnl_IDFilterEnabled(checked);
}

void MessageFilter::on_addFilterIDPushButton_clicked()
{
    /* IDAddDialog *idAddDialog = new IDAddDialog(this); */
    /* connect(idAddDialog, &IDAddDialog::commit, this, &MessageConfig::idAddFinished); */
    /* idAddDialog->exec(); */
    
    FilterIDAddDialog *filterIDAddDiag = new FilterIDAddDialog(idModel, this);
    connect(filterIDAdddialog, &FilterIDAddDialog::commit, this, &MessageFilter::filterIDCommit);
    filterIDAddDiag.exec();
    
    /* // Catch the QModelIndex of the newly created entry in the model */
    /* const QModelIndex &newlyAddedIDIndex = filterIDModel.addID(0x0); */
    /* // Issue an edit of the element */
    /* ui->idFilterlistView->edit(newlyAddedIDIndex); */

    /* filterIDModel.data(newlyAddedIDIndex); */

    /* emit sgnl_IDAddedToFilter(); */
}

void MessageFilter::on_rmvFilterIDPushButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->idFilterlistView->selectionModel();
    QModelIndexList selectionIndexList = selectionModel->selectedRows();
    if(selectionIndexList.size())
    {
        filterIDModel.removeRows(selectionIndexList.first().row(), selectionIndexList.size());
    }
    emit sgnl_IDRemovedFromFilter();
}

void MessageFilter::on_enableCodeFilterCheckBox_toggled(bool checked)
{
    emit sgnl_CodeFilterEnabled(checked);
}

void MessageFilter::on_addFilterCodePushButton_clicked()
{
    FilterCodeAddDialog *filterCodeAddDialog = new FilterCodeAddDialog(msgTypeModel, this);
    connect(filterCodeAddDialog, &FilterCodeAddDialog::commit, this, &MessageFilter::filterCodeCommit);
    filterCodeAddDialog.exec();
}

void MessageFilter::on_rmvFilterCodePushButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->codeFilterlistView->selectionModel();
    QModelIndexList selectionIndexList = selectionModel->selectedRows();
    if(selectionIndexList.size())
    {
        filterCodeModel.removeRows(selectionIndexList.first().row(), selectionIndexList.size());
    }

    emit sngl_CodeRemovedFromFilter();
}

void MessageFilter::on_enableTimestampFromFilterCheckBox_toggled(bool checked)
{
    emit sgnl_TimestampFilterFromEnabled(checked);
}

void MessageFilter::on_filterTimeStampFromDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    if(ui->filterTimestampToDateTimeEdit->dateTime() < dateTime)
    {
        ui->filterTimestampToDateTimeEdit->setDateTime(dateTime);
    }

    filterTimestampStore.setTimestampFilterFrom(dateTime);

    emit sgnl_TimestampFromChanged();
}

void MessageFilter::on_enableTimestampToFilterCheckBox_toggled(bool checked)
{
    emit sgnl_TimestampFilterToEnabled(checked);
}

void MessageFilter::on_filterTimeStampToDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    if(ui->filterTimestampFromDateTimeEdit->dateTime() > dateTime)
    {
        ui->filterTimestampFromDateTimeEdit->setDateTime(dateTime);
    }

    filterTimestampStore.setTimestampFilterTo(dateTime);

    emit sgnl_TimestampToChanged();
}

void MessageFilter::filterIDCommit(const MsgIDType idToCommit)
{
    filterIDModel.addID(idToCommit);
}

void MessageFilter::filterCodeCommit(const MsgCodeType codeToCommit)
{
    filterCodeModel.addCode(codeToCommit);
}
