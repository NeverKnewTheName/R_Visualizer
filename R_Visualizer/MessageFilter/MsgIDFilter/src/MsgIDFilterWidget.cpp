#include "MsgIDFilterWidget.h"
#include "ui_msgidfilterwidget.h"

#include <QFile>
#include <QFileDialog>

#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>

#include <QDebug>

#include "MsgIDFilter.h"
#include "MsgIDFilterModel.h"
#include "MsgIDFilterAddDialog.h"
#include "IMsgIDMappingManager.h"

#include "csvinparser.h"
#include "csvoutparser.h"
#include "jsoninparser.h"
#include "jsonoutparser.h"

MsgIDFilterWidget::MsgIDFilterWidget(
        MsgIDFilter *msgIDFilter,
        MsgIDFilterModel *msgIDFilterModel,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgIDFilterWidget),
    msgIDFilter(msgIDFilter),
    msgIDFilterModel(msgIDFilterModel),
    msgIDMappingManager(Q_NULLPTR)
{
    init();

    ui->enableIDFilterCheckBox->setChecked(
            msgIDFilter->isFilterEnabled()
            );

    ui->invertIDFilterCheckBox->setChecked(
            msgIDFilter->isFilterInverted()
            );

    connect(
            ui->enableIDFilterCheckBox,
            &QCheckBox::toggled,
            msgIDFilter,
            &MsgIDFilter::slt_enableFilter
            );
    connect(
            ui->invertIDFilterCheckBox,
            &QCheckBox::toggled,
            msgIDFilter,
            &MsgIDFilter::slt_invertFilter
            );
}

MsgIDFilterWidget::~MsgIDFilterWidget()
{
    delete ui;
}

void MsgIDFilterWidget::setMsgIDMappingManager(IMsgIDMappingManager *msgIDMappingManager)
{
    static QMetaObject::Connection mappingManagerUpdateConnection;

    this->msgIDMappingManager = msgIDMappingManager;

    if(mappingManagerUpdateConnection)
    {
        disconnect(mappingManagerUpdateConnection);
    }

    mappingManagerUpdateConnection = connect(
            msgIDMappingManager,
            &IMsgIDMappingManager::sgnl_MsgIDMappingManagerChanged,
            [=](){ ui->idFilterListView->reset(); }
            );
}

void MsgIDFilterWidget::setDelegate(QAbstractItemDelegate *delegate)
{
    ui->idFilterListView->setItemDelegateForColumn(0,delegate);
}

void MsgIDFilterWidget::on_addFilterIDPushButton_clicked()
{
    //qsrand(qrand());
    //MsgIDType randomMsgID(qrand() %100);
//
    //slt_addMsgID(randomMsgID);

    MsgIDFilterAddDialog *msgIDFilterAddDialog = new MsgIDFilterAddDialog(
                msgIDMappingManager,
                this
                );

    connect(
            msgIDFilterAddDialog,
            &MsgIDFilterAddDialog::sgnl_commit,
            this,
            &MsgIDFilterWidget::slt_addMsgID
           );

    msgIDFilterAddDialog->exec();
}

void MsgIDFilterWidget::on_rmvFilterIDPushButton_clicked()
{
    QItemSelectionModel *selectionModel =
       ui->idFilterListView->selectionModel();

    QModelIndexList selectionIndexList = selectionModel->selectedRows();

    if(selectionIndexList.size())
    {
        msgIDFilterModel->removeRows(
                selectionIndexList.first().row(),
                selectionIndexList.size()
                );
    }
}

void MsgIDFilterWidget::on_filterIDSaveBtn_clicked()
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
        msgIDFilter->accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson());
        //ToDO check for error (-1)
    }
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MsgIDFilterWidget::on_filterIDLoadBtn_clicked()
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
        msgIDFilter->clear();
        //ToDO
        // read file content
        JsonInParser jsonInParser;
        jsonInParser.setJsonDocument(
                QJsonDocument::fromJson(jsonOpenFile.readAll())
                );
        msgIDFilter->accept(&jsonInParser);
        /* idModel.ParseFromJson(jsonOpenFile.readAll());
         * //ToDO check for error (-1) */
        // parse file
        // populate ui
    }
    // close file
    jsonOpenFile.close();
}

/* void MsgIDFilterWidget::on_enableIDFilterCheckBox_toggled(bool checked) */
/* { */
/*     msgIDFilter->enableFilter(checked); */
/* } */

/* void MsgIDFilterWidget::on_checkBox_toggled(bool checked) */
/* { */
/*     msgIDFilter->invertFilter(checked); */
/* } */

void MsgIDFilterWidget::slt_addMsgID(const MsgIDType &msgIDToAdd)
{
    msgIDFilter->addMsgIDToFilter(msgIDToAdd);
}

void MsgIDFilterWidget::slt_removeMsgID(const MsgIDType &msgIDToRemove)
{
    msgIDFilter->removeMsgIDFromFilter(msgIDToRemove);
}

void MsgIDFilterWidget::init()
{
    ui->setupUi(this);
    QSortFilterProxyModel *sortFilterProxyModel = new
        QSortFilterProxyModel(this);
    //ToDO... this is not good... maybe inherit from QAbstractItemModel directly in the interface?
    sortFilterProxyModel->setSourceModel(
            dynamic_cast<QAbstractItemModel*>(msgIDFilterModel)
            );
    ui->idFilterListView->setModel(sortFilterProxyModel);
    ui->idFilterListView->setAlternatingRowColors(true);
    ui->idFilterListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->idFilterListView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->idFilterListView->setEditTriggers(QAbstractItemView::DoubleClicked);
    //ToDO
    //ui->idFilterListView->setItemDelegate(new IDEditorDelegate(this));

    //ToDO SCROLL TO BOTTOM
}
