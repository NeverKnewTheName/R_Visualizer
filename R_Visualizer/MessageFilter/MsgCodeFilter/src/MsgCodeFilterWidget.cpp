#include "MsgCodeFilterWidget.h"
#include "ui_msgcodefilterwidget.h"

#include <QFile>
#include <QFileDialog>

#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>

#include <QDebug>

#include "MsgCodeFilter.h"
#include "MsgCodeFilterModel.h"
#include "MsgCodeFilterAddDialog.h"
#include "IMsgCodeMappingManager.h"

#include "csvinparser.h"
#include "csvoutparser.h"
#include "jsoninparser.h"
#include "jsonoutparser.h"

MsgCodeFilterWidget::MsgCodeFilterWidget(
        MsgCodeFilter *msgCodeFilter,
        MsgCodeFilterModel *msgCodeFilterModel,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::MsgCodeFilterWidget),
    msgCodeFilter(msgCodeFilter),
    msgCodeFilterModel(msgCodeFilterModel),
    msgCodeMappingManager(Q_NULLPTR)
{
    init();
    ui->enableCodeFilterCheckBox->setChecked(
            msgCodeFilter->isFilterEnabled()
            );

    ui->invertCodeFilterCheckBox->setChecked(
            msgCodeFilter->isFilterInverted()
            );

    connect(
            ui->enableCodeFilterCheckBox,
            &QCheckBox::toggled,
            msgCodeFilter,
            &MsgCodeFilter::slt_enableFilter
            );
    connect(
            ui->invertCodeFilterCheckBox,
            &QCheckBox::toggled,
            msgCodeFilter,
            &MsgCodeFilter::slt_invertFilter
            );
}

MsgCodeFilterWidget::~MsgCodeFilterWidget()
{
    delete ui;
}

void MsgCodeFilterWidget::addMsgCode(
        const MsgCodeType &msgCodeToAdd
        )
{
    msgCodeFilter->addMsgCodeToFilter(msgCodeToAdd);
}

void MsgCodeFilterWidget::removeMsgCode(
        const MsgCodeType &msgCodeToRemove
        )
{
    msgCodeFilter->removeMsgCodeFromFilter(msgCodeToRemove);
}

void MsgCodeFilterWidget::setMsgCodeMappingManager(IMsgCodeMappingManager *msgCodeMappingManager)
{
    static QMetaObject::Connection mappingManagerUpdateConnection;

    this->msgCodeMappingManager = msgCodeMappingManager;

    if(mappingManagerUpdateConnection)
    {
        disconnect(mappingManagerUpdateConnection);
    }

    mappingManagerUpdateConnection = connect(
            msgCodeMappingManager,
            &IMsgCodeMappingManager::sgnl_MsgCodeMappingManagerChanged,
            [=](){ ui->codeFilterListView->reset(); }
            );
}

void MsgCodeFilterWidget::setDelegate(QAbstractItemDelegate *delegate)
{
    ui->codeFilterListView->setItemDelegateForColumn(0,delegate);
}

void MsgCodeFilterWidget::on_filterCodeLoadBtn_clicked()
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
        msgCodeFilter->clear();
        //ToDO
        // read file content
        JsonInParser jsonInParser;
        jsonInParser.setJsonDocument(
                QJsonDocument::fromJson(jsonOpenFile.readAll())
                );
        msgCodeFilter->accept(&jsonInParser);
        /* idModel.ParseFromJson(jsonOpenFile.readAll());
         * //ToDO check for error (-1) */
        // parse file
        // populate ui
    }
    // close file
    jsonOpenFile.close();
}

void MsgCodeFilterWidget::on_filterCodeStoreBtn_clicked()
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
        msgCodeFilter->accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson());
        //ToDO check for error (-1)
    }
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MsgCodeFilterWidget::on_addFilterCodePushButton_clicked()
{
    //qsrand(qrand());
    //MsgCodeType randomMsgCode(qrand() %100);

    //slt_addMsgCode(randomMsgCode);

    MsgCodeFilterAddDialog *msgCodeFilterAddDialog = new MsgCodeFilterAddDialog(
                msgCodeMappingManager,
                this
                );

    connect(
            msgCodeFilterAddDialog,
            &MsgCodeFilterAddDialog::sgnl_commit,
            this,
            &MsgCodeFilterWidget::slt_addMsgCode
           );

    msgCodeFilterAddDialog->setAttribute(Qt::WA_DeleteOnClose);
    msgCodeFilterAddDialog->exec();
}

void MsgCodeFilterWidget::on_rmvFilterCodePushButton_clicked()
{
    QItemSelectionModel *selectionModel =
       ui->codeFilterListView->selectionModel();

    QModelIndexList selectionIndexList = selectionModel->selectedRows();

    if(selectionIndexList.size())
    {
        msgCodeFilterModel->removeRows(
                selectionIndexList.first().row(),
                selectionIndexList.size()
                );
    }
}

/* void MsgCodeFilterWidget::on_enableCodeFilterCheckBox_toggled(bool checked) */
/* { */

/* } */

/* void MsgCodeFilterWidget::on_invertCodeFilterCheckBox_toggled(bool checked) */
/* { */

/* } */

void MsgCodeFilterWidget::slt_addMsgCode(
        const MsgCodeType &msgCodeToAdd
        )
{
    addMsgCode(msgCodeToAdd);
}

void MsgCodeFilterWidget::slt_removeMsgCode(
        const MsgCodeType &msgCodeToRemove
        )
{
    removeMsgCode(msgCodeToRemove);
}

void MsgCodeFilterWidget::init()
{
    ui->setupUi(this);
    QSortFilterProxyModel *sortFilterProxyModel = new
        QSortFilterProxyModel(this);
    //ToDO... this is not good... maybe inherit from QAbstractItemModel directly in the interface?
    sortFilterProxyModel->setSourceModel(
            dynamic_cast<QAbstractItemModel*>(msgCodeFilterModel)
            );
    ui->codeFilterListView->setModel(sortFilterProxyModel);
    ui->codeFilterListView->setAlternatingRowColors(true);
    ui->codeFilterListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->codeFilterListView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->codeFilterListView->setEditTriggers(QAbstractItemView::DoubleClicked);
    //ToDO
    //ui->codeFilterListView->setItemDelegate(new CodeEditorDelegate(this));

    //ToDO SCROLL TO BOTTOM
}
