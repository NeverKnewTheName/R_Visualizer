#include "MsgCodeMappingWidget.h"
#include "ui_msgcodemappingwidget.h"

#include "IMsgCodeMappingManager.h"
#include "MsgCodeMappingModel.h"

#include "MsgCodeMappingAddDialog.h"

#include "MsgCodeMapping.h"

#include <QFile>
#include <QFileDialog>

#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>

#include <QDebug>

#include "fileparser.h"
#include "csvinparser.h"
#include "csvoutparser.h"
#include "jsoninparser.h"
#include "jsonoutparser.h"


MsgCodeMappingWidget::MsgCodeMappingWidget(
        IMsgCodeMappingManager *msgCodeMappingManager,
        MsgCodeMappingModel *msgCodeMappingModel,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgCodeMappingWidget),
    msgCodeMappingManager(msgCodeMappingManager),
    msgCodeMappingModel(msgCodeMappingModel)
{
    init();
    connectModel();
}

MsgCodeMappingWidget::~MsgCodeMappingWidget()
{
    delete ui;
}

void MsgCodeMappingWidget::setModel(
        MsgCodeMappingModel *model
        )
{
    msgCodeMappingModel = model;
}

void MsgCodeMappingWidget::on_msgCodeStoreBtn_clicked()
{
    QString saveLoc = QFileDialog::getSaveFileName(
            this,
            QString("Save as"),
            QString(),
            "JSON File (*.json)"
            );
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
        msgCodeMappingModel->accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson());
        //ToDO check for error (-1)
    }
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();

}

void MsgCodeMappingWidget::on_msgCodeLoadBtn_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(
            this,
            QString("Open"),
            QString(),
            "JSON File (*.json)"
            );
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
        msgCodeMappingModel->accept(&jsonInParser);
        /* idModel.ParseFromJson(jsonOpenFile.readAll()); 
         * //ToDO check for error (-1) */
        // parse file
        // populate ui
    }
    // close file
    jsonOpenFile.close();

}

void MsgCodeMappingWidget::on_msgCodeRemoveBtn_clicked()
{
    QItemSelectionModel *selectionModel = ui->codeTableView->selectionModel();

    QModelIndexList selectionIndexList = selectionModel->selectedRows();

    if(selectionIndexList.size())
    {
        msgCodeMappingModel->removeRows(
                selectionIndexList.first().row(),
                selectionIndexList.size()
                );
    }
}


void MsgCodeMappingWidget::on_msgCodeAddBtn_clicked()
{
    MsgCodeMappingAddDialog *msgCodeMappingAddDialog =
        new MsgCodeMappingAddDialog(this);

    connect(
            msgCodeMappingAddDialog,
            &MsgCodeMappingAddDialog::commit,
            this,
            &MsgCodeMappingWidget::slt_MsgCodeMappingAddFinished
           );

    msgCodeMappingAddDialog->exec();
}

void MsgCodeMappingWidget::slt_clear()
{
    msgCodeMappingModel->clear();
}

void MsgCodeMappingWidget::slt_MsgCodeMappingAddFinished(
            const MsgCodeType &msgCode,
            const QString &alias,
            const QColor &colorRepresentation
        )
{
    MsgCodeMapping tempMsgCodeMapping(
            msgCode,
            alias,
            colorRepresentation
            );

    emit sgnl_AddMsgCodeMapping(tempMsgCodeMapping);
}

void MsgCodeMappingWidget::init()
{
    ui->setupUi(this);
    QSortFilterProxyModel *sortFilterProxyModel = new
        QSortFilterProxyModel(this);
    //ToDO... this is not good... maybe inherit from QAbstractItemModel directly in the interface?
    sortFilterProxyModel->setSourceModel(
            dynamic_cast<QAbstractItemModel*>(msgCodeMappingModel)
            );
    ui->codeTableView->setSortingEnabled(true);
    ui->codeTableView->setModel(sortFilterProxyModel);
    ui->codeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->codeTableView->verticalHeader()->hide();
    ui->codeTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->codeTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    //ToDO
    //ui->codeTableView->setItemDelegate(new CodeEditorDelegate(this));

    //ToDO SCROLL TO BOTTOM
}

void MsgCodeMappingWidget::connectModel()
{
    connect(
            this,
            &MsgCodeMappingWidget::sgnl_AddMsgCodeMapping,
            msgCodeMappingManager,
            &IMsgCodeMappingManager::slt_addMsgCodeMapping
           );

    connect(
            this,
            &MsgCodeMappingWidget::sgnl_RemoveMsgCodeMapping,
            msgCodeMappingManager,
            &IMsgCodeMappingManager::slt_removeMsgCodeMapping
           );
}
