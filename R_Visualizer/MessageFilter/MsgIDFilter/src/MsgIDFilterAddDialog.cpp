#include "MsgIDFilterAddDialog.h"
#include "ui_msgidfilteradddialog.h"

#include "IMsgIDMappingManager.h"
#include "MsgIDMappingModel.h"

#include <QCompleter>

MsgIDFilterAddDialog::MsgIDFilterAddDialog(
        IMsgIDMappingManager *msgIDMappingManager,
        QWidget *parent
        ) :
    QDialog(parent),
    ui(new Ui::MsgIDFilterAddDialog),
    msgIDMappingManager(msgIDMappingManager)
{
    ui->setupUi(this);

    if(msgIDMappingManager != Q_NULLPTR)
    {
        ui->idLineEdit->setMappingManager(msgIDMappingManager);

        MsgIDMappingModel *msgIDMappingModel = new MsgIDMappingModel(
                msgIDMappingManager->getStore(),
                qobject_cast<QObject*>(ui->idLineEdit)
                );

        QCompleter *idAliasCompleter =
                new QCompleter(qobject_cast<QObject*>(ui->idLineEdit));

        idAliasCompleter->setModel(msgIDMappingModel);
        idAliasCompleter->setCompletionColumn(MsgIDMappingModel::COL_Alias);
        idAliasCompleter->setCompletionRole(Qt::DisplayRole);
        idAliasCompleter->setModelSorting(
                QCompleter::CaseInsensitivelySortedModel
                );
        idAliasCompleter->setCaseSensitivity(Qt::CaseInsensitive);

        ui->idLineEdit->setCompleter(idAliasCompleter);
    }
}

MsgIDFilterAddDialog::~MsgIDFilterAddDialog()
{
    delete ui;
}

void MsgIDFilterAddDialog::on_buttonBox_accepted()
{
    emit sgnl_commit(ui->idLineEdit->getMsgID());
}
