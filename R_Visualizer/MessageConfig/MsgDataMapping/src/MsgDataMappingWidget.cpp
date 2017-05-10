#include "MsgDataMappingWidget.h"
#include "ui_msgdatamappingwidget.h"

#include "IMsgDataMappingManager.h"
#include "MsgDataMappingModel.h"

#include "MsgDataMappingAddDialog.h"
#include "MsgDataMappingEditorDelegate.h"

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

MsgDataMappingWidget::MsgDataMappingWidget(
        IMsgDataMappingManager *msgDataMappingManager,
        MsgDataMappingModel *msgDataMappingModel,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgDataMappingWidget),
    msgDataMappingManager(msgDataMappingManager),
    msgDataMappingModel(msgDataMappingModel)
{
    init();
    connectModel();
}

MsgDataMappingWidget::~MsgDataMappingWidget()
{
    delete ui;
}

void MsgDataMappingWidget::setModel(MsgDataMappingModel *model)
{
    msgDataMappingModel = model;
}

void MsgDataMappingWidget::on_msgDataStoreBtn_clicked()
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
        msgDataMappingModel->accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson());
        //ToDO check for error (-1)
    }
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MsgDataMappingWidget::on_msgDataLoadBtn_clicked()
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
        msgDataMappingModel->clear();
        //ToDO
        // read file content
        JsonInParser jsonInParser;
        jsonInParser.setJsonDocument(
                QJsonDocument::fromJson(jsonOpenFile.readAll())
                );
        msgDataMappingModel->accept(&jsonInParser);
        // parse file
        // populate ui
    }
    // close file
    jsonOpenFile.close();
}

void MsgDataMappingWidget::on_msgDataRemoveBtn_clicked()
{
    QItemSelectionModel *selectionModel =
        ui->msgDataTableView->selectionModel();

    QModelIndexList selectionIndexList = selectionModel->selectedRows();

    if(selectionIndexList.size())
    {
        msgDataMappingModel->removeRows(
                selectionIndexList.first().row(),
                selectionIndexList.size()
                );
    }
}

#include "MsgDataMapping.h"
#include "MsgDataFormatter.h"
void MsgDataMappingWidget::on_msgDataAddBtn_clicked()
{
    MsgDataMappingAddDialog *msgDataMappingAddDialog =
        new MsgDataMappingAddDialog(this);

    connect(
            msgDataMappingAddDialog,
            &MsgDataMappingAddDialog::sgnl_Commit,
            this,
            &MsgDataMappingWidget::slt_MsgDataMappingAddFinished
           );

    msgDataMappingAddDialog->exec();
    /* qsrand(qrand()); */
    /* MsgIDType msgID(qrand() %100); */
    /* MsgCodeType msgCode(qrand() %100); */

    /* MsgDataMapping msgDataMapping( */
    /*         msgID, */
    /*         msgCode, */
    /*         new MsgDataFormatter(QString("Testing!")) */
    /*         ); */

    /* emit sgnl_AddMsgDataMapping( */
    /*         msgDataMapping */
    /*         ); */
}

void MsgDataMappingWidget::slt_clear()
{
    msgDataMappingModel->clear();
}

void MsgDataMappingWidget::slt_MsgDataMappingAddFinished(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode,
        const QString &formatString,
        const QColor &defaultColor
        )
{
    MsgDataMapping tempMsgDataMapping(
            msgID,
            msgCode,
            MsgDataFormatter(
                formatString,
                defaultColor
                )
            );

    emit sgnl_AddMsgDataMapping(tempMsgDataMapping);

}

void MsgDataMappingWidget::init()
{
    ui->setupUi(this);
    QSortFilterProxyModel *sortFilterProxyModel = new
        QSortFilterProxyModel(this);
    //ToDO... this is not good... maybe inherit from QAbstractItemModel directly in the interface?
    sortFilterProxyModel->setSourceModel(
            dynamic_cast<QAbstractItemModel*>(msgDataMappingModel)
            );
    ui->msgDataTableView->setSortingEnabled(true);
    ui->msgDataTableView->setModel(sortFilterProxyModel);
    ui->msgDataTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->msgDataTableView->verticalHeader()->hide();
    ui->msgDataTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->msgDataTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    ui->msgDataTableView->setItemDelegate(new MsgDataMappingEditorDelegate(ui->msgDataTableView));
}

void MsgDataMappingWidget::connectModel()
{
    connect(
            this,
            &MsgDataMappingWidget::sgnl_AddMsgDataMapping,
            msgDataMappingManager,
            &IMsgDataMappingManager::slt_AddMsgDataMapping
           );

    connect(
            this,
            &MsgDataMappingWidget::sgnl_RemoveMsgDataMapping,
            msgDataMappingManager,
            &IMsgDataMappingManager::slt_RemoveMsgDataMapping
           );
}
