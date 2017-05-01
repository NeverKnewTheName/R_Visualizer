#include "SendMsgPackageWidget.h"
#include "ui_sendmsgpackagewidget.h"

#include <QHeaderView>

#include "ISendMsgPackage.h"
#include "ISendMsgPackageStore.h"

#include "SendMsgPackageAddDialog.h"

#include "IMsgIDMappingManager.h"
#include "IMsgCodeMappingManager.h"
#include "IMsgDataMappingManager.h"


SendMsgPackageWidget::SendMsgPackageWidget(
        ISendMsgPackage *sendMsgPackage,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SendMsgPackageWidget),
    sendMsgPackage(sendMsgPackage),
    sendMsgPackageModel(sendMsgPackage->getStore(),this),
    msgIDMappingManager(Q_NULLPTR),
    msgCodeMappingManager(Q_NULLPTR),
    msgDataMappingManager(Q_NULLPTR)
{
    ui->setupUi(this);
    init();
}

SendMsgPackageWidget::~SendMsgPackageWidget()
{
    delete ui;
}

#include "Msg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

void SendMsgPackageWidget::on_sndPcktAddBtn_clicked()
{
    //qsrand(qrand());
    //MsgDataType testMsgData;
//
    //testMsgData.append(MsgDataByteType(qrand() &0xffu));
    //testMsgData.append(MsgDataByteType(qrand() &0xffu));
    //testMsgData.append(MsgDataByteType(qrand() &0xffu));
    //testMsgData.append(MsgDataByteType(qrand() &0xffu));
//
    //Msg testMsg(MsgIDType(qrand()&0xFFFF),MsgCodeType(qrand()&0xFF),testMsgData);

    SendMsgPackageAddDialog *sendMsgPackageAddDialog =
            new SendMsgPackageAddDialog(
                msgIDMappingManager,
                msgCodeMappingManager,
                this
                );

    //connect(
            //sendMsgPackageAddDialog,
            //&SendMsgPackageAddDialog::sgnl_commit,
            //sendMsgPackage,
            //&ISendMsgPackage::slt_appendMsg
            //);

    connect(
                sendMsgPackageAddDialog,
                &SendMsgPackageAddDialog::sgnl_commit,
                [=](const IMsg &msg){
                    QItemSelectionModel *selectionModel =
                       ui->sndPckgTableView->selectionModel();

                    QModelIndexList selectionIndexList = selectionModel->selectedRows();

                    if(selectionIndexList.size())
                    {
                        const int row = selectionIndexList.last().row() + 1;
                        sendMsgPackage->insertMsg(row,msg);
                    }
                    else
                    {
                        sendMsgPackage->appendMsg(msg);
                    }
                }
            );

    sendMsgPackageAddDialog->exec();
}

void SendMsgPackageWidget::on_sndPcktRmvBtn_clicked()
{
    QItemSelectionModel *selectionModel =
       ui->sndPckgTableView->selectionModel();

    QModelIndexList selectionIndexList = selectionModel->selectedRows();

    sendMsgPackage->removeMsgs(
            selectionIndexList.first().row(),
            selectionIndexList.size()
            );
}

void SendMsgPackageWidget::on_sndPcktLoadBtn_clicked()
{

}

void SendMsgPackageWidget::on_sndPcktStoreBtn_clicked()
{

}

void SendMsgPackageWidget::on_sndPcktSendBtn_clicked()
{
    sendMsgPackage->sendMessages();
}

void SendMsgPackageWidget::on_sndPcktClrBtn_clicked()
{
    sendMsgPackage->getStore()->clear();
}

void SendMsgPackageWidget::init()
{
    ui->sndPckgTableView->setModel(&sendMsgPackageModel);
    ui->sndPckgTableView->setAlternatingRowColors(true);
    ui->sndPckgTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->sndPckgTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->sndPckgTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    //ToDO
    //ui->codeFilterListView->setItemDelegate(new CodeEditorDelegate(this));

    QHeaderView *horzHeader = ui->sndPckgTableView->horizontalHeader();

    const int sectionCount = horzHeader->count() - 1;
    const int sectionLength = horzHeader->length() / horzHeader->count();

    for(int i = 0; i < sectionCount; ++i)
    {
        horzHeader->setSectionResizeMode(i,QHeaderView::Interactive);
    }

    horzHeader->setDefaultSectionSize(sectionLength);

    horzHeader->setStretchLastSection(true);
}
