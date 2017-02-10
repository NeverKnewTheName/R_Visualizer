#include "filtercodeadddialog.h"
#include "ui_filtercodeadddialog.h"

#include <QString>
#include <QCompleter>

#include "msgtypemodel.h"

FilterCodeAddDialog::FilterCodeAddDialog( const MsgTypeModel &msgTypeModelForCompletion, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterCodeAddDialog),
    msgTypeModelForCompletion(msgTypeModelForCompletion)
{
    ui->setupUi(this);

    QCompleter *codeCompleter = msgTypeModelForCompletion.createMsgTypeCompleter(ui->codeTypeLe);
    codeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->codeTypeLe->setCompleter(codeCompleter);
    connect(this, &FilterCodeAddDialog::accepted, this, &FilterCodeAddDialog::readyToCommit);
}

FilterCodeAddDialog::~FilterCodeAddDialog()
{
    delete ui;
}

void FilterCodeAddDialog::readyToCommit()
{
    const QString &codeTypeText = ui->codeTypeLe->text();
    bool conversionOK;
    MsgCodeType retrievedCode = codeTypeText.toInt(&conversionOK, (codeTypeText.startsWith("0x")) ? 16 : 0);

    if(!conversionOK)
    {
        retrievedCode = msgTypeModelForCompletion.getCodeToName(codeTypeText);
    }

    emit commit(retrievedCode);
}
