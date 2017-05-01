#include "SendMsgPackageAddDialog.h"
#include "ui_sendmsgpackageadddialog.h"

#include "IMsgIDMappingManager.h"
#include "MsgIDMappingModel.h"

#include "IMsgCodeMappingManager.h"
#include "MsgCodeMappingModel.h"

#include <QCompleter>

SendMsgPackageAddDialog::SendMsgPackageAddDialog(
        IMsgIDMappingManager *msgIDMappingManager,
        IMsgCodeMappingManager *msgCodeMappingManager,
        QWidget *parent
        ) :
    QDialog(parent),
    ui(new Ui::SendMsgPackageAddDialog)
{
    ui->setupUi(this);

    if(msgIDMappingManager != Q_NULLPTR)
    {
        ui->msgWidget->setMsgIDMapping(msgIDMappingManager);

        MsgIDMappingModel *msgIDMappingModel = new MsgIDMappingModel(
                msgIDMappingManager->getStore(),
                qobject_cast<QObject*>(ui->msgWidget)
                );

        QCompleter *idAliasCompleter = new QCompleter(qobject_cast<QObject*>(ui->msgWidget));

        idAliasCompleter->setModel(msgIDMappingModel);
        idAliasCompleter->setCompletionColumn(MsgIDMappingModel::COL_Alias);
        idAliasCompleter->setCompletionRole(Qt::DisplayRole);
        idAliasCompleter->setModelSorting(
                QCompleter::CaseInsensitivelySortedModel
                );
        idAliasCompleter->setCaseSensitivity(Qt::CaseInsensitive);

        ui->msgWidget->setMsgIDCompleter(idAliasCompleter);
    }

    if(msgCodeMappingManager != Q_NULLPTR)
    {
        ui->msgWidget->setMsgCodeMapping(msgCodeMappingManager);

        MsgCodeMappingModel *msgCodeMappingModel = new MsgCodeMappingModel(
                msgCodeMappingManager->getStore(),
                qobject_cast<QObject*>(ui->msgWidget)
                );

        QCompleter *codeAliasCompleter = new QCompleter(qobject_cast<QObject*>(ui->msgWidget));

        codeAliasCompleter->setModel(msgCodeMappingModel);
        codeAliasCompleter->setCompletionColumn(MsgCodeMappingModel::COL_Alias);
        codeAliasCompleter->setCompletionRole(Qt::DisplayRole);
        codeAliasCompleter->setModelSorting(
                QCompleter::CaseInsensitivelySortedModel
                );
        codeAliasCompleter->setCaseSensitivity(Qt::CaseInsensitive);

        ui->msgWidget->setMsgCodeCompleter(codeAliasCompleter);
    }
}

SendMsgPackageAddDialog::~SendMsgPackageAddDialog()
{
    delete ui;
}

void SendMsgPackageAddDialog::on_buttonBox_accepted()
{
    emit sgnl_commit(ui->msgWidget->getMsg());
}
