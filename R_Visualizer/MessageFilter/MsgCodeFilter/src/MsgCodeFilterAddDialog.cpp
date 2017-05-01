#include "MsgCodeFilterAddDialog.h"
#include "ui_msgcodefilteradddialog.h"

#include "IMsgCodeMappingManager.h"
#include "MsgCodeMappingModel.h"

#include <QCompleter>

MsgCodeFilterAddDialog::MsgCodeFilterAddDialog(
        IMsgCodeMappingManager *msgCodeMappingManager,
        QWidget *parent
        ) :
    QDialog(parent),
    ui(new Ui::MsgCodeFilterAddDialog),
    msgCodeMappingManager(msgCodeMappingManager)
{
    ui->setupUi(this);

    if(msgCodeMappingManager != Q_NULLPTR)
    {
        ui->codeLineEdit->setMappingManager(msgCodeMappingManager);

        MsgCodeMappingModel *msgCodeMappingModel = new MsgCodeMappingModel(
                msgCodeMappingManager->getStore(),
                qobject_cast<QObject*>(ui->codeLineEdit)
                );

        QCompleter *codeAliasCompleter = new QCompleter(qobject_cast<QObject*>(ui->codeLineEdit));

        codeAliasCompleter->setModel(msgCodeMappingModel);
        codeAliasCompleter->setCompletionColumn(MsgCodeMappingModel::COL_Alias);
        codeAliasCompleter->setCompletionRole(Qt::DisplayRole);
        codeAliasCompleter->setModelSorting(
                QCompleter::CaseInsensitivelySortedModel
                );
        codeAliasCompleter->setCaseSensitivity(Qt::CaseInsensitive);

        ui->codeLineEdit->setCompleter(codeAliasCompleter);
    }
}

MsgCodeFilterAddDialog::~MsgCodeFilterAddDialog()
{
    delete ui;
}

void MsgCodeFilterAddDialog::on_buttonBox_accepted()
{
    emit sgnl_commit(ui->codeLineEdit->getMsgCode());
}
