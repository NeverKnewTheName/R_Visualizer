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

    ui->idNameLe->setMsgConfig(msgConfig);
    /* QCompleter *idCompleter = msgConfig->createIDNameCompleter(ui->idNameLe); */
    /* idCompleter->setCaseSensitivity(Qt::CaseInsensitive); */
    /* ui->idNameLe->setCompleter(idCompleter); */
    /* connect(ui->idNameLe, &QLineEdit::textChanged, [=](const QString &text){ */
    /*         QColor color = msgConfig->getColorToIDName(text); */
    /*         QString colorName("white"); */
    /*         if(color.isValid()) */
    /*         { */
    /*            colorName = color.name(); */
    /*         } */
    /*         ui->idNameLe->setStyleSheet(QString("background: %1").arg(colorName)); */
    /*         }); */

    /* connect(idCompleter, static_cast<void(QCompleter::*)(const QString &)>(&QCompleter::activated),[=](const QString &text){ */
    /*         QString colorName = msgConfig->getColorToIDName(text).name(); */
    /*         ui->idNameLe->setStyleSheet(QString("background: %1").arg(colorName)); */
    /*         }); */
    /* connect(idCompleter, static_cast<void(QCompleter::*)(const QString &)>(&QCompleter::highlighted),[=](const QString &text){ */
    /*         QString colorName = msgConfig->getColorToIDName(text).name(); */
    /*         ui->idNameLe->setStyleSheet(QString("background: %1").arg(colorName)); */
    /*         }); */
    connect(this, &FilterIDAddDialog::accepted, this, &FilterIDAddDialog::readyToCommit);
}

FilterIDAddDialog::~FilterIDAddDialog()
{
    delete ui;
}

void FilterIDAddDialog::readyToCommit()
{
    /* const QString &idNameText = ui->idNameLe->text(); */
    /* bool conversionOK; */
    /* MsgIDType retrievedID = idNameText.toInt(&conversionOK, (idNameText.startsWith("0x")) ? 16 : 0); */

    /* /1* If the Conversion failed (e.g. the entered value is neither a base 16 or 10 integer, */
    /*  * the IDModel that is used for completion is queried for the editor content */
    /*  *1/ */
    /* if(!conversionOK) */
    /* { */
    /*     retrievedID = msgConfig->getIDToName(idNameText); */
    /* } */

    const MsgIDType retrievedID = ui->idNameLe->getID();
    emit commit(retrievedID);
}
