#include "SendMsgSingleWidget.h"
#include "ui_sendmsgsinglewidget.h"

#include <QFileDialog>

#include "ISendMsgSingle.h"

#include "IMsgIDMappingManager.h"
#include "IMsgCodeMappingManager.h"
#include "IMsgDataMappingManager.h"

#include "Msg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

#include "MsgWidget.h"

#include "jsoninparser.h"
#include "jsonoutparser.h"
#include "csvinparser.h"
#include "csvoutparser.h"

#include <QDebug>

SendMsgSingleWidget::SendMsgSingleWidget(
        ISendMsgSingle *sendMsgSingle,
        QWidget *parent
        ) :
    QWidget(parent),
    ui(new Ui::SendMsgSingleWidget),
    sendMsgSingle(sendMsgSingle)
{
    ui->setupUi(this);

    setTabOrder(ui->msgWidget,ui->sndMsgSendBtn);
    setTabOrder(ui->sndMsgSendBtn,ui->sndMsgAddToPackageBtn);
    setTabOrder(ui->sndMsgAddToPackageBtn,ui->openMsgBtn);
    setTabOrder(ui->openMsgBtn,ui->saveMsgBtn);

    ui->msgWidget->setFocus();
}

SendMsgSingleWidget::~SendMsgSingleWidget()
{
    delete ui;
}

void SendMsgSingleWidget::setMsgIDMapping(
        IMsgIDMappingManager *msgIDMappingManager
        )
{
    ui->msgWidget->setMsgIDMapping(msgIDMappingManager);
}

void SendMsgSingleWidget::setMsgIDCompleter(
        QCompleter *msgIDCompleter
        )
{
    ui->msgWidget->setMsgIDCompleter(msgIDCompleter);
}

void SendMsgSingleWidget::setMsgCodeMapping(
        IMsgCodeMappingManager *msgCodeMappingManager
        )
{
    ui->msgWidget->setMsgCodeMapping(msgCodeMappingManager);
}

void SendMsgSingleWidget::setMsgCodeCompleter(
        QCompleter *msgCodeCompleter
        )
{
    ui->msgWidget->setMsgCodeCompleter(msgCodeCompleter);
}

void SendMsgSingleWidget::setMsgDataMapping(
        IMsgDataMappingManager *msgDataMappingManager
        )
{
    //ui->msgDataWidget->setMappingManager(msgDataMappingManager);
}

void SendMsgSingleWidget::on_sndMsgSendBtn_clicked()
{
    Msg msgToSend(ui->msgWidget->getMsg());

    sendMsgSingle->sendMessage(msgToSend);
}

void SendMsgSingleWidget::on_sndMsgAddToPackageBtn_clicked()
{
    Msg msgToAdd(ui->msgWidget->getMsg());

    emit sgnl_AddToPackage(msgToAdd);
}

void SendMsgSingleWidget::on_openMsgBtn_clicked()
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
        // read file content
        JsonInParser jsonInParser;
        jsonInParser.setJsonDocument(
                QJsonDocument::fromJson(jsonOpenFile.readAll())
                );
        Msg msgToSet;
        msgToSet.accept(&jsonInParser);
        ui->msgWidget->setMsg(msgToSet);
    }
    // close file
    jsonOpenFile.close();
}

void SendMsgSingleWidget::on_saveMsgBtn_clicked()
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
        JsonOutParser jsonOutParser;
        ui->msgWidget->getMsg().accept(&jsonOutParser);
        jsonSaveFile.write(jsonOutParser.getJsonDocument().toJson());
    }
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();

}
