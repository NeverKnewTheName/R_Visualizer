#include "messageconfig.h"
#include "ui_messageconfig.h"

#include "idadddialog.h"
#include "ideditordelegate.h"
#include "msgtypeadddialog.h"
#include "msgtypeeditordelegate.h"
#include "filteriddelegate.h"
#include "filtermsgtypedelegate.h"
#include <QFile>
#include <QFileDialog>

#include <QJsonDocument>

#include <QDebug>

#include <QSortFilterProxyModel>

MessageConfig::MessageConfig(IDModel *idModel, MsgTypeModel *msgTypeModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageConfig),
    idModel(idModel),
    msgTypeModel(msgTypeModel),
    idFilterEnabled(false),
    codeFilterEnabled(false),
    timeStampFilterFromEnabled(false),
    timeStampFilterToEnabled(false)
  //filterTimestampStore(this)//ToDO
{
    ui->setupUi(this);

    filterIDModel = new FilterIDStore(idModel, this);
    filterCodeModel = new FilterCodeStore(msgTypeModel, this);
    filterTimestampStore = new FilterTimestampStore(this);
    this->initIDTableView();
    this->initMsgTypeTableView();
    this->initFilterIDListView();
    this->initFilterCodeListView();
    //connect(ui->filterTimeStampFromDateTimeEdit, &QDateTimeEdit::editingFinished, this, &MessageConfig::slt_timestampFromChanged);
    connect(ui->filterTimeStampFromDateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &MessageConfig::slt_timestampFromChanged);
    connect(this, &MessageConfig::sgnl_timestampFromChanged, filterTimestampStore, &FilterTimestampStore::timestampFromChanged);
    connect(ui->filterTimeStampToDateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &MessageConfig::slt_timestampToChanged);
    connect(this, &MessageConfig::sgnl_timestampToChanged, filterTimestampStore, &FilterTimestampStore::timestampToChanged);
}

MessageConfig::~MessageConfig()
{
    delete ui;
}

FilterIDStore *MessageConfig::getFilterIDModel() const
{
    return this->filterIDModel;
}

FilterCodeStore *MessageConfig::getFilterCodeModel() const
{
    return this->filterCodeModel;
}

FilterTimestampStore *MessageConfig::getFilterTimestampModel() const
{
    return this->filterTimestampStore;
}

void MessageConfig::initIDTableView()
{
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(idModel);
    ui->idTableView->setSortingEnabled(true);
    ui->idTableView->setModel(proxy);
    ui->idTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->idTableView->verticalHeader()->hide();
    ui->idTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->idTableView->setItemDelegate(new IDEditorDelegate(ui->idTableView));



    //ToDO scrollToBottom might not be the best slot to address....
    connect(idModel, &IDModel::rowsInserted, ui->idTableView, &QTableView::scrollToBottom);
    //DEBUG//
    //    idModel->add(0xFF, new IDRep(0xFF00, QString("Master"), QColor(Qt::blue)));
    //    idModel->add(0xF0, new IDRep(0xF000, QString("PC"), QColor(Qt::green)));
    //DEBUG//
}

void MessageConfig::initMsgTypeTableView()
{
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(msgTypeModel);
    ui->msgTypeTableView->setSortingEnabled(true);
    ui->msgTypeTableView->setModel(proxy);
    ui->msgTypeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->msgTypeTableView->verticalHeader()->hide();
    ui->msgTypeTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->msgTypeTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    ui->msgTypeTableView->setItemDelegate(new MsgTypeEditorDelegate(ui->msgTypeTableView));

    //ToDO scrollToBottom might not be the best slot to address....
    connect(msgTypeModel, &MsgTypeModel::rowsInserted, ui->msgTypeTableView, &QTableView::scrollToBottom);
    //DEBUG//
    //    msgTypeModel->add(new MsgTypeRep(0x02, QString("Start"), QColor(Qt::green)));
    //    msgTypeModel->add(new MsgTypeRep(0x03, QString("Stop"), QColor(Qt::red)));
    //DEBUG//
}

void MessageConfig::initFilterIDListView()
{
    //    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    //    proxy->setSourceModel(&filterIDModel);
    ui->idFilterlistView->setModel(filterIDModel);
    ui->idFilterlistView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    //    ui->idFilterlistView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    ui->idFilterlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->idFilterlistView->setAlternatingRowColors(true);
    ui->idFilterlistView->setItemDelegate(new FilterIDDelegate(idModel, ui->idFilterlistView));

    //connect(filterIDModel, &FilterIDStore::rowAdded, this, &MessageConfig::filterIDAdded);
    connect(filterIDModel, &FilterIDStore::rowAdded, ui->idFilterlistView, static_cast<void (QListView::*)(const QModelIndex &)>(&QListView::edit));
}

void MessageConfig::initFilterCodeListView()
{
    //    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    //    proxy->setSourceModel(&filterCodeModel);
    ui->codeFilterlistView->setModel(filterCodeModel);
    ui->codeFilterlistView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->codeFilterlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->codeFilterlistView->setAlternatingRowColors(true);
    ui->codeFilterlistView->setItemDelegate(new FilterMsgTypeDelegate(msgTypeModel, ui->codeFilterlistView));
    connect(filterCodeModel, &FilterCodeStore::rowAdded, ui->codeFilterlistView, static_cast<void (QListView::*)(const QModelIndex &)>(&QListView::edit));
}

void MessageConfig::idAddFinished(const int id, const QString name, const QColor color)
{
    emit sgnlIdAddFinished(id,name,color);
}

void MessageConfig::msgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color)
{
    emit sgnlMsgTypeAddFinished(code, codeName, messageFormat, color);
}

void MessageConfig::filterIDAdded(unsigned int pos)
{
    QModelIndex index = filterIDModel->index(pos);
    qDebug() << "index row: " << index;
    ui->idFilterlistView->edit(index);
    //emit startEditFilterID(filterIDModel->index(pos));
}

void MessageConfig::slt_timestampFromChanged()
{
    qDebug() << ui->filterTimeStampFromDateTimeEdit->dateTime();
    if(ui->filterTimeStampToDateTimeEdit->dateTime() < ui->filterTimeStampFromDateTimeEdit->dateTime())
    {
        ui->filterTimeStampToDateTimeEdit->setDateTime(ui->filterTimeStampFromDateTimeEdit->dateTime());
    }
    emit sgnl_timestampFromChanged(ui->filterTimeStampFromDateTimeEdit->dateTime());
}

void MessageConfig::slt_timestampToChanged()
{
    qDebug() << ui->filterTimeStampToDateTimeEdit->dateTime();
    if(ui->filterTimeStampToDateTimeEdit->dateTime() < ui->filterTimeStampFromDateTimeEdit->dateTime())
    {
        ui->filterTimeStampFromDateTimeEdit->setDateTime(ui->filterTimeStampToDateTimeEdit->dateTime());
    }
    emit sgnl_timestampToChanged(ui->filterTimeStampToDateTimeEdit->dateTime());
}

void MessageConfig::applyRole(UserRoleMngr::UserRole roleToSwitchTo)
{
    if(roleToSwitchTo == UserRoleMngr::NormalUserRole)
    {
        ui->idAddBtn->setVisible(false);
        ui->idRmvBtn->setVisible(false);
        ui->idStoreBtn->setVisible(false);
        ui->idTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->msgTypeAddBtn->setVisible(false);
        ui->msgTypeRmvBtn->setVisible(false);
        ui->msgTypeStoreBtn->setVisible(false);
        ui->msgTypeTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    }
    else if(roleToSwitchTo == UserRoleMngr::AdminRole)
    {
        ui->idAddBtn->setVisible(true);
        ui->idRmvBtn->setVisible(true);
        ui->idStoreBtn->setVisible(true);
        ui->idTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
        ui->msgTypeAddBtn->setVisible(true);
        ui->msgTypeRmvBtn->setVisible(true);
        ui->msgTypeStoreBtn->setVisible(true);
        ui->msgTypeTableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    }
}


void MessageConfig::on_idLoadBtn_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    //ToDO
    // read file content
    idModel->parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
    // parse file
    // populate ui
    // close file
    jsonOpenFile.close();
}

void MessageConfig::on_idStoreBtn_clicked()
{

    QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
    qDebug() << saveLoc;
    QFile jsonSaveFile(saveLoc);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    }
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    jsonSaveFile.write(this->idModel->parseToJSON()); //ToDO check for error (-1)
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}


void MessageConfig::on_idAddBtn_clicked()
{
    IDAddDialog *idAddDialogg = new IDAddDialog(this);
    connect(idAddDialogg, &IDAddDialog::commit, this, &MessageConfig::idAddFinished);
    idAddDialogg->exec();
}

void MessageConfig::on_idRmvBtn_clicked()
{
    QModelIndexList selection = ui->idTableView->selectionModel()->selectedRows();
    for(auto &selectedItem : selection)
    {
        qDebug() << "Remove row: " << selectedItem.row() << " from IDModel";
        this->idModel->removeRow(selectedItem.row(), QModelIndex());
    }
}

void MessageConfig::on_msgTypeLoadBtn_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    //ToDO
    // read file content
    msgTypeModel->parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
    // parse file
    // populate ui
    // close file
    jsonOpenFile.close();
}

void MessageConfig::on_msgTypeStoreBtn_clicked()
{
    QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
    qDebug() << saveLoc;
    QFile jsonSaveFile(saveLoc);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    }
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    jsonSaveFile.write(this->msgTypeModel->parseToJSON()); //ToDO check for error (-1)
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MessageConfig::on_msgTypeAddBtn_clicked()
{
    MsgTypeAddDialog *msgTypeAddDialogg = new MsgTypeAddDialog(this);
    connect(msgTypeAddDialogg, &MsgTypeAddDialog::commit, this, &MessageConfig::msgTypeAddFinished);
    msgTypeAddDialogg->exec();
}

void MessageConfig::on_msgTypeRmvBtn_clicked()
{
    QModelIndexList selection = ui->msgTypeTableView->selectionModel()->selectedRows();
    for(auto &selectedItem : selection)
    {
        qDebug() << "Remove row: " << selectedItem.row() << " from MsgTypeModel";
        this->msgTypeModel->removeRow(selectedItem.row(), QModelIndex());
    }
}


void MessageConfig::on_enableIDFilterPushButton_clicked()
{
    idFilterEnabled = !idFilterEnabled;
    ui->enableIDFilterPushButton->setText((idFilterEnabled) ? QString("Disable") : QString("Enable"));
    emit filterIDstateChange(idFilterEnabled);
}

void MessageConfig::on_addFilterIDPushButton_clicked()
{
    this->filterIDModel->addID(0x0);
}

void MessageConfig::on_rmvFilterIDPushButton_clicked()
{
    QModelIndex selectedIndex = ui->idFilterlistView->selectionModel()->currentIndex();
    if(selectedIndex.isValid())
        this->filterIDModel->removeID(selectedIndex);
}

void MessageConfig::on_enableCodeFilterPushButton_clicked()
{
    codeFilterEnabled = !codeFilterEnabled;
    ui->enableCodeFilterPushButton->setText((codeFilterEnabled) ? QString("Disable") : QString("Enable"));
    emit filterCodestateChange(codeFilterEnabled);
}

void MessageConfig::on_addFilterCodePushButton_clicked()
{
    this->filterCodeModel->addCode(0x0);
}

void MessageConfig::on_rmvFilterCodePushButton_clicked()
{
    QModelIndex selectedIndex = ui->codeFilterlistView->selectionModel()->currentIndex();
    if(selectedIndex.isValid())
        this->filterCodeModel->removeCode(selectedIndex);
}

void MessageConfig::on_enableTimestampFromFilterPushButton_clicked()
{
    timeStampFilterFromEnabled = !timeStampFilterFromEnabled;
    ui->enableTimestampFromFilterPushButton->setText((timeStampFilterFromEnabled) ? QString("Disable") : QString("Enable"));

    emit filterTimestampFromStateChange(timeStampFilterFromEnabled);
}

void MessageConfig::on_enableTimestampToFilterPushButton_clicked()
{
    timeStampFilterToEnabled = !timeStampFilterToEnabled;
    ui->enableTimestampToFilterPushButton->setText((timeStampFilterToEnabled) ? QString("Disable") : QString("Enable"));

    emit filterTimestampToStateChange(timeStampFilterToEnabled);
}
