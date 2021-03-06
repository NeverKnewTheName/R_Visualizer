#include "SendMsgPackageWidget.h"
#include "ui_sendmsgpackagewidget.h"

#include <QTableView>
#include <QHeaderView>
#include <QTimer>
#include <QDebug>

#include "ISendMsgPackage.h"
#include "ISendMsgPackageStore.h"

#include "SendMsgPackageAddDialog.h"

#include "IMsgIDMappingManager.h"
#include "IMsgCodeMappingManager.h"
#include "IMsgDataMappingManager.h"

#include "MsgIDDelegate.h"
#include "MsgCodeDelegate.h"
#include "MsgDataDelegate.h"

#include <QFileDialog>

#include "csvmsgpackethandler.h"

#include "csvinparser.h"
#include "csvoutparser.h"
#include "jsoninparser.h"
#include "jsonoutparser.h"

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

    connect(
            sendMsgPackage,
            &ISendMsgPackage::sgnl_SendingStarted,
            [=](){
                ui->sndPcktSendBtn->setDisabled(true);
            }
           );
    connect(
            sendMsgPackage,
            &ISendMsgPackage::sgnl_SendingFinished,
            [=](){
                ui->sndPcktSendBtn->setEnabled(true);
            }
           );
}

SendMsgPackageWidget::~SendMsgPackageWidget()
{
    delete ui;
}

void SendMsgPackageWidget::setMsgIDMappingManager(
        IMsgIDMappingManager *msgIDMappingManager
        )
{
    this->msgIDMappingManager = msgIDMappingManager;
    if(msgIDMappingManager != Q_NULLPTR)
    {
        MsgIDDelegate *msgIDDelegate =
            new MsgIDDelegate(msgIDMappingManager,ui->sndPckgTableView);
        ui->sndPckgTableView->setItemDelegateForColumn(0,msgIDDelegate);
    }
}

void SendMsgPackageWidget::setMsgCodeMappingManager(
        IMsgCodeMappingManager *msgCodeMappingManager
        )
{
    this->msgCodeMappingManager = msgCodeMappingManager;

    if(msgCodeMappingManager != Q_NULLPTR)
    {
        MsgCodeDelegate *msgCodeDelegate =
            new MsgCodeDelegate(msgCodeMappingManager,ui->sndPckgTableView);
        ui->sndPckgTableView->setItemDelegateForColumn(1,msgCodeDelegate);
    }
}

void SendMsgPackageWidget::setMsgDataMappingManager(
        IMsgDataMappingManager *msgDataMappingManager
        )
{
    this->msgDataMappingManager = msgDataMappingManager;

    if(msgDataMappingManager != Q_NULLPTR)
    {
        MsgDataDelegate *msgDataDelegate =
            new MsgDataDelegate(msgDataMappingManager,ui->sndPckgTableView);
        ui->sndPckgTableView->setItemDelegateForColumn(2,msgDataDelegate);
    }
}

void SendMsgPackageWidget::on_sndPcktAddBtn_clicked()
{
    SendMsgPackageAddDialog *sendMsgPackageAddDialog =
            new SendMsgPackageAddDialog(
                msgIDMappingManager,
                msgCodeMappingManager,
                this
                );
    connect(
                sendMsgPackageAddDialog,
                &SendMsgPackageAddDialog::sgnl_commit,
                [=](const IMsg &msg){
                    QItemSelectionModel *selectionModel =
                       ui->sndPckgTableView->selectionModel();

                    QModelIndexList selectionIndexList =
                    selectionModel->selectedRows();

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

    sendMsgPackageAddDialog->setAttribute(Qt::WA_DeleteOnClose);
    sendMsgPackageAddDialog->exec();
}

void SendMsgPackageWidget::on_sndPcktRmvBtn_clicked()
{
    QItemSelectionModel *selectionModel =
       ui->sndPckgTableView->selectionModel();

    QModelIndexList selectionIndexList = selectionModel->selectedRows();

    if(selectionIndexList.size())
    {
        sendMsgPackage->removeMsgs(
                selectionIndexList.first().row(),
                selectionIndexList.size()
                );
    }
}

void SendMsgPackageWidget::on_sndPcktLoadBtn_clicked()
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
        sendMsgPackage->getStore()->clear();
        //ToDO
        // read file content
        JsonInParser jsonInParser;
        jsonInParser.setJsonDocument(
                QJsonDocument::fromJson(jsonOpenFile.readAll())
                );
        sendMsgPackage->getStore()->accept(&jsonInParser);
        /* idModel.ParseFromJson(jsonOpenFile.readAll());
         * //ToDO check for error (-1) */
        // parse file
        // populate ui
    }
    // close file
    jsonOpenFile.close();
}

void SendMsgPackageWidget::on_sndPcktStoreBtn_clicked()
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
        sendMsgPackage->getStore()->accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson());
        //ToDO check for error (-1)
    }
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
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
    ui->sendDelaySpinBox->setValue(sendMsgPackage->getSendDelay());

    ui->sndPckgTableView->setModel(&sendMsgPackageModel);
    ui->sndPckgTableView->setAlternatingRowColors(true);
    ui->sndPckgTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->sndPckgTableView->setSelectionMode(
            QAbstractItemView::ContiguousSelection
            );
    ui->sndPckgTableView->setEditTriggers(QAbstractItemView::DoubleClicked);

    QHeaderView *horzHeader = ui->sndPckgTableView->horizontalHeader();

    ui->sndPckgTableView->verticalHeader()
            ->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(
            ui->sndPckgTableView->horizontalHeader(),
            &QHeaderView::sectionResized,
                [=](){
                    QTimer::singleShot(50,
                        [=](){
                            ui->sndPckgTableView->verticalHeader()
                            ->resizeSections(QHeaderView::ResizeToContents);
                            //qDebug() << "sendPckgTableView resized!";
                        }
                    );
                }
            );

    const int sectionCount = horzHeader->count() - 1;
    const int sectionLength = horzHeader->length() / horzHeader->count();

    for(int i = 0; i < sectionCount; ++i)
    {
        horzHeader->setSectionResizeMode(i,QHeaderView::Interactive);
    }

    horzHeader->setDefaultSectionSize(sectionLength);

    horzHeader->setStretchLastSection(true);
}

void SendMsgPackageWidget::on_pushButton_clicked()
{
    QString openLoc = QFileDialog::getOpenFileName(
            this,
            QString("Open"),
            QString(),
            "CSV File (*.csv)"
            );
    qDebug() << openLoc;
    QFile csvMatrixFile(openLoc);
    if(!csvMatrixFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << csvMatrixFile.fileName();
    }
    else
    {
        sendMsgPackage->getStore()->clear();

        CsvMsgPacketHandler csvMatrixHandler;

        QString csvMatrixString(csvMatrixFile.readAll());

        QVector<Msg> messages =
            csvMatrixHandler.parseCsvMsgPacket(csvMatrixString);

        for(const Msg &msg : messages)
        {
            sendMsgPackage->appendMsg(msg);
        }
    }
    // close file
    csvMatrixFile.close();
}

void SendMsgPackageWidget::on_sendDelaySpinBox_valueChanged(int arg1)
{
    sendMsgPackage->setSendDelay(arg1);
}
