#include "MsgIDMappingWidget.h"
#include "ui_msgidmappingwidget.h"

#include <QFile>
#include <QFileDialog>

#include <QJsonDocument>

#include <QSortFilterProxyModel>

#include <QDebug>

#include "idadddialog.h"
#include "ideditordelegate.h"

#include "fileparser.h"
#include "csvinparser.h"
#include "csvoutparser.h"
#include "jsoninparser.h"
#include "jsonoutparser.h"

MsgIDMappingWidget::MsgIDMappingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MsgIDMappingWidget),
    msgIDMappingModel(new MsgIDMappingModel())
{
    init();
}

MsgIDMappingWidget::MsgIDMappingWidget(
        IMsgIDMappingModel *model,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgIDMappingWidget),
    msgIDMappingModel(model)
{
    init();
}

MsgIDMappingWidget::~MsgIDMappingWidget()
{
    delete ui;
}

void MsgIDMappingWidget::setModel(IMsgIDMappingModel *model)
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

}

void MsgIDMappingWidget::on_idAddBtn_clicked()
{
    MsgIDRep testRep(10, QString("TEST"), QColor(Qt::blue));
    msgIDMappingModel->appendMsgIDMapping(testRep);
}

void MsgIDMappingWidget::init()
{
    ui->setupUi(this);
    QSortFilterProxyModel *sortFilterProxyModel = new
        QSortFilterProxyModel(this);
    proxy->setSourceModel(msgIDMappingModel);
    ui->idTableView->setSortingEnabled(true);
    ui->idTableView->setModel(proxy);
    ui->idTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->idTableView->verticalHeader()->hide();
    ui->idTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->idTableView->setItemDelegate(new IDEditorDelegate(this));

    //ToDO SCROLL TO BOTTOM
}
