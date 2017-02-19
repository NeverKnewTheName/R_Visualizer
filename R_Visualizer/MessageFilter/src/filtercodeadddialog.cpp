#include "filtercodeadddialog.h"
#include "ui_filtercodeadddialog.h"

#include <QString>
#include <QCompleter>

#include "messageconfig.h"

#include <QDebug>

FilterCodeAddDialog::FilterCodeAddDialog( const MessageConfig *msgConfig, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterCodeAddDialog),
    msgConfig(msgConfig)
{
    ui->setupUi(this);

    ui->codeTypeLe->setMsgConfig(msgConfig);
    /* QCompleter *codeCompleter = msgConfig->createCodeNameCompleter(ui->codeTypeLe); */
    /* codeCompleter->setCaseSensitivity(Qt::CaseInsensitive); */
    /* ui->codeTypeLe->setCompleter(codeCompleter); */

    /* connect(codeCompleter, static_cast<void(QCompleter::*)(const QString &)>(&QCompleter::activated),[=](const QString &text){ */
    /*         QString colorName = msgConfig->getColorToCodeName(text).name(); */
    /*         ui->codeTypeLe->setStyleSheet(QString("background: %1").arg(colorName)); */
    /*         }); */
    /* connect(codeCompleter, static_cast<void(QCompleter::*)(const QString &)>(&QCompleter::highlighted),[=](const QString &text){ */
    /*         QString colorName = msgConfig->getColorToCodeName(text).name(); */
    /*         ui->codeTypeLe->setStyleSheet(QString("background: %1").arg(colorName)); */
    /*         }); */
    connect(this, &FilterCodeAddDialog::accepted, this, &FilterCodeAddDialog::readyToCommit);
}

FilterCodeAddDialog::~FilterCodeAddDialog()
{
    delete ui;
}

void FilterCodeAddDialog::readyToCommit()
{
    /* const QString &codeTypeText = ui->codeTypeLe->text(); */
    /* bool conversionOK; */
    /* MsgCodeType retrievedCode = codeTypeText.toInt(&conversionOK, (codeTypeText.startsWith("0x")) ? 16 : 0); */

    /* if(!conversionOK) */
    /* { */
    /*     retrievedCode = msgConfig->getCodeToName(codeTypeText); */
    /* } */

    const MsgCodeType retrievedCode = ui->codeTypeLe->getCode();
    emit commit(retrievedCode);
}
