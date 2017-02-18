#include "filteridadddialog.h"
#include "ui_filteridadddialog.h"

#include <QString>
#include <QCompleter>

#include "messageconfig.h"

FilterIDAddDialog::FilterIDAddDialog(const MessageConfig *msgConfig, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterIDAddDialog),
    msgConfig(msgConfig)
{
    ui->setupUi(this);

    /*
     * Set up the completer
     */
    QCompleter *idCompleter = msgConfig->createIDNameCompleter(ui->idNameLe);
    idCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->idNameLe->setCompleter(idCompleter);
    connect(this, &FilterIDAddDialog::accepted, this, &FilterIDAddDialog::readyToCommit);
}

FilterIDAddDialog::~FilterIDAddDialog()
{
    delete ui;
}

void FilterIDAddDialog::readyToCommit()
{
    const QString &idNameText = ui->idNameLe->text();
    bool conversionOK;
    MsgIDType retrievedID = idNameText.toInt(&conversionOK, (idNameText.startsWith("0x")) ? 16 : 0);

    /* If the Conversion failed (e.g. the entered value is neither a base 16 or 10 integer,
     * the IDModel that is used for completion is queried for the editor content
     */
    if(!conversionOK)
    {
        retrievedID = msgConfig->getIDToName(idNameText);
    }

    emit commit(retrievedID);
}
