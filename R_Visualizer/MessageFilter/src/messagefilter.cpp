#include "messagefilter.h"
#include "ui_messagefilter.h"

#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QAbstractItemView>

#include "filteriddelegate.cpp"
#include "filtermsgtypedelegate.cpp"

MessageFilter::MessageFilter(
            const IDModel &idModel,
            const MsgTypeModel &msgTypeModel,
            QWidget *parent = 0
        ) :
    QWidget(parent),
    ui(new Ui::MessageFilter)
{
    ui->setupUi(this);
    initFilterIDListView();
    initFilterCodeListView();
}

MessageFilter::~MessageFilter()
{
    delete ui;
}


void MessageFilter::initFilterIDListView(const IDModel &idModel)
{
    //    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    //    proxy->setSourceModel(&filterIDModel);
    ui->idFilterlistView->setModel(&filterIDModel);
    ui->idFilterlistView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->idFilterlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->idFilterlistView->setAlternatingRowColors(true);
    ui->idFilterlistView->setItemDelegate(new FilterIDDelegate(&idModel, ui->idFilterlistView));

    connect(&filterIDModel, &FilterIDStore::rowAdded, ui->idFilterlistView, static_cast<void (QListView::*)(const QModelIndex &)>(&QListView::edit));
}

void MessageFilter::initFilterCodeListView(const MsgTypeModel &msgTypeModel)
{
    //    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    //    proxy->setSourceModel(&filterCodeModel);
    ui->codeFilterlistView->setModel(&filterCodeModel);
    ui->codeFilterlistView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->codeFilterlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->codeFilterlistView->setAlternatingRowColors(true);
    ui->codeFilterlistView->setItemDelegate(new FilterMsgTypeDelegate(&msgTypeModel, ui->codeFilterlistView));

    connect(&filterCodeModel, &FilterCodeStore::rowAdded, ui->codeFilterlistView, static_cast<void (QListView::*)(const QModelIndex &)>(&QListView::edit));
}
