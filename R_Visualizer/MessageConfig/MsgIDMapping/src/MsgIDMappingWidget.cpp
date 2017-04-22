#include "MsgIDMappingWidget.h"
#include "ui_msgidmappingwidget.h"

#include <QFile>
#include <QFileDialog>

#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>

#include <QDebug>

#include "idadddialog.h"
#include "ideditordelegate.h"

#include "fileparser.h"
#include "csvinparser.h"
#include "csvoutparser.h"
#include "jsoninparser.h"
#include "jsonoutparser.h"

MsgIDMappingWidget::MsgIDMappingWidget(
        MsgIDMappingModel *model,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgIDMappingWidget),
    msgIDMappingModel(model)
{
    init();
    connectModel();

}

MsgIDMappingWidget::~MsgIDMappingWidget()
{
    delete ui;
}

void MsgIDMappingWidget::setModel(MsgIDMappingModel *model)
{
    this->msgIDMappingModel = model;
}

void MsgIDMappingWidget::on_idStoreBtn_clicked()
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
        msgIDMappingModel->accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson()); //ToDO check for error (-1)
    }
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MsgIDMappingWidget::on_idLoadBtn_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"),
            QString(), "JSON File (*.json)");
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
        jsonInParser.setJsonDocument(
                QJsonDocument::fromJson(jsonOpenFile.readAll())
                );
        msgIDMappingModel->accept(&jsonInParser);
        /* idModel.ParseFromJson(jsonOpenFile.readAll()); //ToDO check for error (-1) */
        // parse file
        // populate ui
    }
    // close file
    jsonOpenFile.close();
}

void MsgIDMappingWidget::on_idRmvBtn_clicked()
{
    QItemSelectionModel *selectionModel = ui->idTableView->selectionModel();

    QModelIndexList selectionIndexList = selectionModel->selectedRows();

    if(selectionIndexList.size())
    {
        msgIDMappingModel->removeRows(
                selectionIndexList.first().row(),
                selectionIndexList.size()
                );
    }

}

#include "MsgIDMapping.h"
void MsgIDMappingWidget::on_idAddBtn_clicked()
{
    qsrand(qrand());
    MsgIDMapping testMapping(MsgIDType(qrand() % 100), QString("TEST"), QColor(Qt::blue));
    emit sgnl_AddMsgIDMapping(testMapping.getID(), testMapping);
    //msgIDMappingModel->appendMsgIDMapping(testMapping);
}

void MsgIDMappingWidget::slt_clear()
{
    msgIDMappingModel->clear();
}

void MsgIDMappingWidget::slt_MsgIDMappingAddFinished(const IMsgIDMapping &addedMsgIDMapping)
{
    //ToDO
}

void MsgIDMappingWidget::init()
{
    ui->setupUi(this);
    QSortFilterProxyModel *sortFilterProxyModel = new
        QSortFilterProxyModel(this);
    //ToDO... this is not good... maybe inherit from QAbstractItemModel directly in the interface?
    sortFilterProxyModel->setSourceModel(dynamic_cast<QAbstractItemModel*>(msgIDMappingModel));
    ui->idTableView->setSortingEnabled(true);
    ui->idTableView->setModel(sortFilterProxyModel);
    ui->idTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->idTableView->verticalHeader()->hide();
    ui->idTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    //ToDO
    //ui->idTableView->setItemDelegate(new IDEditorDelegate(this));

    //ToDO SCROLL TO BOTTOM
}

void MsgIDMappingWidget::connectModel()
{
    connect(
            this,
            &MsgIDMappingWidget::sgnl_AddMsgIDMapping,
            msgIDMappingModel,
            &MsgIDMappingModel::sgnl_AddMapping
           );

    connect(
            this,
            &MsgIDMappingWidget::sgnl_RemoveMsgIDMapping,
            msgIDMappingModel,
            &MsgIDMappingModel::sgnl_RemoveMapping
           );
}
