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

#include "fileparser.h"
#include "csvinparser.h"
#include "csvoutparser.h"
#include "jsoninparser.h"
#include "jsonoutparser.h"

MessageConfig::MessageConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageConfig)
{
    ui->setupUi(this);

    this->initIDTableView();
    this->initMsgTypeTableView();

    connect(&idModel, &IDModel::sgnl_IDRepAdded, this, &MessageConfig::sgnl_IDRepAdded);
    connect(&idModel, &IDModel::sgnl_IDRepUpdated, this, &MessageConfig::sgnl_IDRepUpdated);
    connect(&idModel, &IDModel::sgnl_IDRepRemoved, this, &MessageConfig::sgnl_IDRepRemoved);

    connect(&msgTypeModel, &MsgTypeModel::sgnl_MsgTypeRepAdded, this, &MessageConfig::sgnl_MsgTypeRepAdded);
    connect(&msgTypeModel, &MsgTypeModel::sgnl_MsgTypeRepUpdated, this, &MessageConfig::sgnl_MsgTypeRepUpdated);
    connect(&msgTypeModel, &MsgTypeModel::sgnl_MsgTypeRepRemoved, this, &MessageConfig::sgnl_MsgTypeRepRemoved);
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

PrettyMsg MessageConfig::prettifyMsg(const Msg &msg) const
{
    PrettyMsg prettifiedMsg(
            msg,
            idModel.getIDRepToID(msg.getId()),
            msgTypeModel.getMsgTypeRepToCode(msg.getCode())
            );
   return prettifiedMsg;
}

MsgIDType MessageConfig::getIDToName(const QString &name) const
{
    return idModel.getIDToName(name);
}

QString MessageConfig::getNameToID(const MsgIDType id) const
{
    return idModel.getNameToID(id);
}

QColor MessageConfig::getColorToID(const MsgIDType id) const
{
    return idModel.getColorToID(id);
}

QColor MessageConfig::getColorToIDName(const QString &name) const
{
    return idModel.getColorToID(idModel.getIDToName(name));
}

MsgCodeType MessageConfig::getCodeToName(const QString &name) const
{
    return msgTypeModel.getCodeToName(name);
}

QString MessageConfig::getNameToCode(const MsgCodeType code) const
{
    return msgTypeModel.getNameToCode(code);
}

QColor MessageConfig::getColorToCode(const MsgCodeType code) const
{
    return msgTypeModel.getColorToCode(code);
}

QColor MessageConfig::getColorToCodeName(const QString &name) const
{
    return msgTypeModel.getColorToCode(msgTypeModel.getCodeToName(name));
}

QCompleter *MessageConfig::createIDNameCompleter(QObject *parent) const
{
    return idModel.createIDCompleter(parent);
}

QCompleter *MessageConfig::createCodeNameCompleter(QObject *parent) const
{
    return msgTypeModel.createMsgTypeCompleter(parent);
}

const IDModel &MessageConfig::getIDModel() const
{
    return idModel;
}

const MsgTypeModel &MessageConfig::getMsgTypeModel() const
{
    return msgTypeModel;
}

void MessageConfig::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

void MessageConfig::idAddFinished(const MsgIDType id, const QString &name, const QColor &color)
{
    idModel.add(IDRep(id, name, color));
    /* emit sgnlIdAddFinished(id,name,color); */
}

void MessageConfig::msgTypeAddFinished(const MsgCodeType code, const QString &codeName, const QString &messageFormat, const QColor &color)
{
    msgTypeModel.add(MsgTypeRep(code, codeName, messageFormat, color));
    /* emit sgnlMsgTypeAddFinished(code, codeName, messageFormat, color); */
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
        JsonInParser jsonInParser;
        jsonInParser.setJsonDocument(QJsonDocument::fromJson(jsonOpenFile.readAll()));
        idModel.accept(&jsonInParser);
        /* idModel.ParseFromJson(jsonOpenFile.readAll()); //ToDO check for error (-1) */
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
        JsonOutParser jsonOutParser;
        idModel.accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson()); //ToDO check for error (-1)
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
        JsonInParser jsonInParser;
        jsonInParser.setJsonDocument(QJsonDocument::fromJson(jsonOpenFile.readAll()));
        msgTypeModel.accept(&jsonInParser);
        /* msgTypeModel.ParseFromJson(jsonOpenFile.readAll()); //ToDO check for error (-1) */
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
        JsonOutParser jsonOutParser;
        msgTypeModel.accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson()); //ToDO check for error (-1)
        /* jsonSaveFile.write(msgTypeModel.ParseToJson()); //ToDO check for error (-1) */
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

void MessageConfig::slt_IDRepAdded(const IDRep &newIDRep)
{
    emit sgnl_IDRepAdded(newIDRep);
}

void MessageConfig::slt_IDRepUpdated(const IDRep &updatedIDRep)
{
    emit sgnl_IDRepUpdated(updatedIDRep);
}

void MessageConfig::slt_IDRepRemoved(const MsgIDType relatedID)
{
    emit sgnl_IDRepRemoved(relatedID);
}

void MessageConfig::slt_MsgTypeRepAdded(const MsgTypeRep &newMsgTypeRep)
{
    emit sgnl_MsgTypeRepAdded(newMsgTypeRep);
}

void MessageConfig::slt_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep)
{
    emit sgnl_MsgTypeRepUpdated(updatedMsgTypeRep);
}

void MessageConfig::slt_MsgTypeRepRemoved(const MsgCodeType relatedCode)
{
    emit sgnl_MsgTypeRepRemoved(relatedCode);
}

/* void MessageConfig::slt_MsgDataRepAdded(const MsgDataRep &newMsgDataRep) */
/* { */
/*     emit sgnl_MsgDataRepAdded(newMsgDataRep); */
/* } */

/* void MessageConfig::slt_MsgDataRepUpdated(const MsgDataRep &updatedMsgDataRep) */
/* { */
/*     emit sgnl_MsgDataRepUpdated(updatedMsgDataRep); */
/* } */

/* void MessageConfig::slt_MsgDataRepRemoved(const MsgCodeType relatedCode) */
/* { */
/*     emit sgnl_MsgDataRepRemoved(relatedCode); */
/* } */


void MessageConfig::slt_ApplyRole(UserRoleMngr::UserRole roleToApply)
{
}