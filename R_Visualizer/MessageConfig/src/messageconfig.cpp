#include "messageconfig.h"
#include "ui_messageconfig.h"

#include "idadddialog.h"
#include "ideditordelegate.h"
#include "msgtypeadddialog.h"
#include "msgtypeeditordelegate.h"
#include <QFile>
#include <QFileDialog>

#include <QJsonDocument>

#include <QDebug>

#include <QSortFilterProxyModel>

MessageConfig::MessageConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageConfig),
    idModel(idModel),
    msgTypeModel(msgTypeModel),
  //filterTimestampStore(this)//ToDO
{
    ui->setupUi(this);

    this->initIDTableView();
    this->initMsgTypeTableView();
}

MessageConfig::~MessageConfig()
{
    delete ui;
}

void MessageConfig::initIDTableView()
{
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(&idModel);
    ui->idTableView->setSortingEnabled(true);
    ui->idTableView->setModel(proxy);
    ui->idTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->idTableView->verticalHeader()->hide();
    ui->idTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->idTableView->setItemDelegate(new IDEditorDelegate(ui->idTableView));

    //ToDO scrollToBottom might not be the best slot to address....
    connect(&idModel, &IDModel::rowsInserted, ui->idTableView, &QTableView::scrollToBottom);
}

void MessageConfig::initMsgTypeTableView()
{
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(&msgTypeModel);
    ui->msgTypeTableView->setSortingEnabled(true);
    ui->msgTypeTableView->setModel(proxy);
    ui->msgTypeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->msgTypeTableView->verticalHeader()->hide();
    ui->msgTypeTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->msgTypeTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    ui->msgTypeTableView->setItemDelegate(new MsgTypeEditorDelegate(ui->msgTypeTableView));

    //ToDO scrollToBottom might not be the best slot to address....
    connect(&msgTypeModel, &MsgTypeModel::rowsInserted, ui->msgTypeTableView, &QTableView::scrollToBottom);
}

const IDmodel &MessageConfig::getIDModel() const
{
    return idModel;
}

const MsgTypeModel &MessageConfig::getMsgTypeModel() const
{
    return msgTypeModel;
}

void MessageConfig::idAddFinished(const MsgIDType id, const QString &name, const QColor &color)
{
    emit sgnlIdAddFinished(id,name,color);
}

void MessageConfig::msgTypeAddFinished(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color)
{
    emit sgnlMsgTypeAddFinished(code, codeName, messageFormat, color);
}

void MessageConfig::filterIDAdded(unsigned int pos)
{
    QModelIndex index = filterIDModel.index(pos);
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
    else
    {
        //ToDO
        // read file content
        idModel.parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
        // parse file
        // populate ui
    }
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
    } else
    {
        //ToDO
        // extract ui content
        // parse content to file format
        // write to file
        jsonSaveFile.write(idModel.parseToJSON()); //ToDO check for error (-1)
    }
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}


void MessageConfig::on_idAddBtn_clicked()
{
    IDAddDialog *idAddDialog = new IDAddDialog(this);
    connect(idAddDialog, &IDAddDialog::commit, this, &MessageConfig::idAddFinished);
    idAddDialog->exec();
}

void MessageConfig::on_idRmvBtn_clicked()
{
    QModelIndexList selection = ui->idTableView->selectionModel()->selectedRows();
//    for(auto &selectedItem : selection)
//    {
//        qDebug() << "Remove row: " << selectedItem.row() << " from IDModel";
//        this->idModel->removeRow(selectedItem.row(), QModelIndex());
//    }
    QItemSelectionModel *selectionModel = ui->idTableView->selectionModel();
    QModelIndexList selectionIndexList = selectionModel->selectedRows();
    if(selectionIndexList.size())
    {
        idModel.removeRows(selectionIndexList.first().row(), selectionIndexList.size());
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
    else
    {
        //ToDO
        // read file content
        msgTypeModel.parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
        // parse file
        // populate ui
    }
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
    else
    {
        //ToDO
        // extract ui content
        // parse content to file format
        // write to file
        jsonSaveFile.write(msgTypeModel.parseToJSON()); //ToDO check for error (-1)
    }
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
//    QModelIndexList selection = ui->msgTypeTableView->selectionModel()->selectedRows();
//    for(auto &selectedItem : selection)
//    {
//        qDebug() << "Remove row: " << selectedItem.row() << " from MsgTypeModel";
//        this->msgTypeModel->removeRow(selectedItem.row(), QModelIndex());
//    }
    QItemSelectionModel *selectionModel = ui->msgTypeTableView->selectionModel();
    QModelIndexList selectionIndexList = selectionModel->selectedRows();
    if(selectionIndexList.size())
    {
        msgTypeModel.removeRows(selectionIndexList.first().row(), selectionIndexList.size());
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
    filterIDModel.addID(0x0);
}

void MessageConfig::on_rmvFilterIDPushButton_clicked()
{
//    QModelIndex selectedIndex = ui->idFilterlistView->selectionModel()->currentIndex();
//    if(selectedIndex.isValid())
//        this->filterIDModel->removeID(selectedIndex);

    QItemSelectionModel *selectionModel = ui->idFilterlistView->selectionModel();
    QModelIndexList selectionIndexList = selectionModel->selectedRows();
    if(selectionIndexList.size())
    {
        filterIDModel.removeRows(selectionIndexList.first().row(), selectionIndexList.size());
    }
}

void MessageConfig::on_enableCodeFilterPushButton_clicked()
{
    codeFilterEnabled = !codeFilterEnabled;
    ui->enableCodeFilterPushButton->setText((codeFilterEnabled) ? QString("Disable") : QString("Enable"));
    emit filterCodestateChange(codeFilterEnabled);
}

void MessageConfig::on_addFilterCodePushButton_clicked()
{
    filterCodeModel.addCode(0x0);
}

void MessageConfig::on_rmvFilterCodePushButton_clicked()
{
    QModelIndex selectedIndex = ui->codeFilterlistView->selectionModel()->currentIndex();
    if(selectedIndex.isValid())
        filterCodeModel.removeCode(selectedIndex);
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
