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

MessageConfig::MessageConfig(IDModel *idModel, MsgTypeModel *msgTypeModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageConfig),
    idModel(idModel),
    msgTypeModel(msgTypeModel)
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
    ui->idTableView->setModel(idModel);
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
    ui->msgTypeTableView->setModel(msgTypeModel);
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

void MessageConfig::idAddFinished(const int id, const QString name, const QColor color)
{
    emit sgnlIdAddFinished(id,name,color);
}

void MessageConfig::msgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color)
{
    emit sgnlMsgTypeAddFinished(code, codeName, messageFormat, color);
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
        ui->msgTypeSoreBtn->setVisible(false);
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
        ui->msgTypeSoreBtn->setVisible(true);
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
