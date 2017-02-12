#include "messagefilter.h"
#include "ui_messagefilter.h"

#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QAbstractItemView>

#include "idmodel.h"
#include "msgtypemodel.h"

#include "filteriddelegate.cpp"
#include "filtermsgtypedelegate.cpp"

#include "filteridadddialog.h"
#include "filtercodeadddialog.h"

MessageFilter::MessageFilter(
            const IDModel &idModel,
            const MsgTypeModel &msgTypeModel,
            QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MessageFilter),
    filterIDModel(),
    filterCodeModel(),
    filterTimestampModel(),
    idModel(idModel),
    msgTypeModel(msgTypeModel)
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

void MessageFilter::initFilterIDListView()
{
    //    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    //    proxy->setSourceModel(&filterIDModel);
    
    //THE VIEW DOES NOT TAKE OWNERSHIP OF THE MODEL!!!
    ui->idFilterlistView->setModel(&filterIDModel);
    //ui->idFilterlistView->setModel(proxy);
    ui->idFilterlistView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->idFilterlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->idFilterlistView->setAlternatingRowColors(true);
    ui->idFilterlistView->setItemDelegate(new FilterIDDelegate(idModel, ui->idFilterlistView));
}

void MessageFilter::initFilterCodeListView()
{
    //    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    //    proxy->setSourceModel(&filterCodeModel);
    
    //THE VIEW DOES NOT TAKE OWNERSHIP OF THE MODEL!!!
    ui->codeFilterlistView->setModel(&filterCodeModel);
    //ui->codeFilterlistView->setModel(proxy);
    ui->codeFilterlistView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->codeFilterlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->codeFilterlistView->setAlternatingRowColors(true);
    ui->codeFilterlistView->setItemDelegate(new FilterMsgTypeDelegate(msgTypeModel, ui->codeFilterlistView));
}

void MessageFilter::initFilterTimestamp()
{
    //Init the model
    filterTimestampModel.setTimestampFilterTo(ui->filterTimeStampToDateTimeEdit->dateTime());
    filterTimestampModel.setTimestampFilterFrom(ui->filterTimeStampFromDateTimeEdit->dateTime());
}

bool MessageFilter::filterMsg(const Msg &msgToFilter) const
{
    bool filterResult = true;

    filterResult &= filterMsgID(msgToFilter.getId());
    filterResult &= filterMsgCode(msgToFilter.getCode());
    filterResult &= filterMsgTimestampSpan(msgToFilter.getTimestamp());

    return filterResult;
}

bool MessageFilter::filterMsgID(const MsgIDType msgIDToFilter) const
{
    bool idFilterResult = true;
    
    if(ui->enableIDFilterCheckBox->isChecked())
    {
        idFilterResult &= filterIDModel.containsID(msgIDToFilter);
    }

    return idFilterResult;
}

bool MessageFilter::filterMsgCode(const MsgCodeType msgCodeToFilter) const
{
    bool codeFilterResult = true;

    if(ui->enableCodeFilterCheckBox->isChecked())
    {
        codeFilterResult &= filterCodeModel.containsCode(msgCodeToFilter);
    }

    return codeFilterResult;
}

bool MessageFilter::filterMsgTimestampSpan(const QDateTime &msgTimestamp) const
{
    bool timestampFilterResult = true;

    timestampFilterResult &= filterMsgTimestampFrom(msgTimestamp);
    timestampFilterResult &= filterMsgTimestampTo(msgTimestamp);

    return timestampFilterResult;
}

bool MessageFilter::filterMsgTimestampFrom(const QDateTime &msgTimestamp) const
{
    bool filterTimestampFromResult = true;

    if(ui->enableTimestampFromFilterCheckBox->isChecked())
    {
        filterTimestampFromResult &= 
            ui->filterTimeStampFromDateTimeEdit->dateTime()
            <=
            msgTimestamp;
    }

    return filterTimestampFromResult;
}

bool MessageFilter::filterMsgTimestampTo(const QDateTime &msgTimestamp) const
{
    bool filterTimestampToResult = true;

    if(ui->enableTimestampToFilterCheckBox->isChecked())
    {
        filterTimestampToResult &= 
            ui->filterTimeStampToDateTimeEdit->dateTime()
            >=
            msgTimestamp;
    }

    return filterTimestampToResult;
}

const FilterIDStore &MessageFilter::getFilterIDModel() const
{
    return filterIDModel;
}

const FilterCodeStore &MessageFilter::getFilterCodeModel() const
{
    return filterCodeModel;
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
    FilterIDAddDialog *filterIDAddDiag = new FilterIDAddDialog(idModel, this);
    connect(filterIDAddDiag, &FilterIDAddDialog::commit, this, &MessageFilter::filterIDCommit);
    filterIDAddDiag->exec();
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
    filterCodeAddDialog->exec();
}

void MessageFilter::on_rmvFilterCodePushButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->codeFilterlistView->selectionModel();
    QModelIndexList selectionIndexList = selectionModel->selectedRows();
    if(selectionIndexList.size())
    {
        filterCodeModel.removeRows(selectionIndexList.first().row(), selectionIndexList.size());
    }

    emit sgnl_CodeRemovedFromFilter();
}

void MessageFilter::on_enableTimestampFromFilterCheckBox_toggled(bool checked)
{
    emit sgnl_TimestampFilterFromEnabled(checked);
}

void MessageFilter::on_filterTimeStampFromDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    if(ui->filterTimeStampToDateTimeEdit->dateTime() < dateTime)
    {
        ui->filterTimeStampToDateTimeEdit->setDateTime(dateTime);
    }

    filterTimestampModel.setTimestampFilterFrom(dateTime);

    emit sgnl_TimestampFromChanged();
}

void MessageFilter::on_enableTimestampToFilterCheckBox_toggled(bool checked)
{
    emit sgnl_TimestampFilterToEnabled(checked);
}

void MessageFilter::on_filterTimeStampToDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    if(ui->filterTimeStampFromDateTimeEdit->dateTime() > dateTime)
    {
        ui->filterTimeStampFromDateTimeEdit->setDateTime(dateTime);
    }

    filterTimestampModel.setTimestampFilterTo(dateTime);

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
