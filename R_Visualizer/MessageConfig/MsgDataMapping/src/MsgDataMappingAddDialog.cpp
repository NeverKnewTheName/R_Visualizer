#include "MsgDataMappingAddDialog.h"
#include "ui_msgdatamappingadddialog.h"

#include <QDebug>
#include <QCompleter>
#include <QColorDialog>

#include "IMsgIDMappingManager.h"
#include "MsgIDLineEdit.h"
#include "MsgIDMappingModel.h"

#include "IMsgCodeMappingManager.h"
#include "MsgCodeLineEdit.h"
#include "MsgCodeMappingModel.h"

#include "MsgDataFormatStringEditorDialog.h"

MsgDataMappingAddDialog::MsgDataMappingAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgDataMappingAddDialog)
{
    ui->setupUi(this);

    connect(
            this,
            &MsgDataMappingAddDialog::accepted,
            this,
            &MsgDataMappingAddDialog::slt_ReadyToCommit
           );
    setTabOrder(ui->msgIDLineEdit,ui->msgCodeLineEdit);
    setTabOrder(ui->msgCodeLineEdit,ui->formatterPlainTextEdit);
    setTabOrder(ui->formatterPlainTextEdit,ui->formatterPushButton);
    setTabOrder(ui->formatterPushButton,ui->buttonBox);

    ui->msgIDLineEdit->setFocus();
}

MsgDataMappingAddDialog::~MsgDataMappingAddDialog()
{
    delete ui;
}

void MsgDataMappingAddDialog::setMsgIDMappingManager(IMsgIDMappingManager *msgIDMappingManager)
{
    ui->msgIDLineEdit->setMappingManager(msgIDMappingManager);
    QCompleter *idAliasCompleter = new QCompleter(ui->msgIDLineEdit);

    MsgIDMappingModel *msgIDMappingModel = new MsgIDMappingModel(
            msgIDMappingManager->getStore(),
            ui->msgIDLineEdit
            );

    idAliasCompleter->setModel(msgIDMappingModel);
    idAliasCompleter->setCompletionColumn(MsgIDMappingModel::COL_Alias);
    idAliasCompleter->setCompletionRole(Qt::DisplayRole);
    //idAliasCompleter->setModelSorting(
            //QCompleter::CaseInsensitivelySortedModel
            //);
    idAliasCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    ui->msgIDLineEdit->setCompleter(idAliasCompleter);
}

void MsgDataMappingAddDialog::setMsgCodeMappingManager(IMsgCodeMappingManager *msgCodeMappingManager)
{
    ui->msgCodeLineEdit->setMappingManager(msgCodeMappingManager);
    QCompleter *codeAliasCompleter = new QCompleter(ui->msgCodeLineEdit);

    MsgCodeMappingModel *msgCodeMappingModel = new MsgCodeMappingModel(
            msgCodeMappingManager->getStore(),
            ui->msgCodeLineEdit
            );

    codeAliasCompleter->setModel(msgCodeMappingModel);
    codeAliasCompleter->setCompletionColumn(MsgCodeMappingModel::COL_Alias);
    codeAliasCompleter->setCompletionRole(Qt::DisplayRole);
    //codeAliasCompleter->setModelSorting(
            //QCompleter::CaseInsensitivelySortedModel
            //);
    codeAliasCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    ui->msgCodeLineEdit->setCompleter(codeAliasCompleter);
}

void MsgDataMappingAddDialog::slt_ColorSelected(
        const QColor &color
        )
{
    ui->colorLineEdit->setStyleSheet(
            QString("QLineEdit { background: %1; }").arg(color.name())
            );
    ui->colorLineEdit->setText(color.name());
}

void MsgDataMappingAddDialog::slt_ReadyToCommit()
{
    emit sgnl_Commit(
            ui->msgIDLineEdit->getMsgID(),
            ui->msgCodeLineEdit->getMsgCode(),
            ui->formatterPlainTextEdit->toPlainText(),
            QColor(ui->colorLineEdit->text())
            );
}

void MsgDataMappingAddDialog::on_formatterPushButton_clicked()
{
    MsgDataFormatStringEditorDialog *msgDataFormatStringEditor =
            new MsgDataFormatStringEditorDialog(this);

    connect(
            msgDataFormatStringEditor,
            &MsgDataFormatStringEditorDialog::sgnl_Commit,
            [=](const QString &formatString){
                ui->formatterPlainTextEdit->setPlainText(formatString);
                }
            );

    msgDataFormatStringEditor->setFormatString(
                ui->formatterPlainTextEdit->document()->toPlainText()
                );

    msgDataFormatStringEditor->exec();
}

void MsgDataMappingAddDialog::on_colorPickerPushButton_clicked()
{
    QColorDialog *colorPicker = new QColorDialog(this);
    connect(
            colorPicker,
            &QColorDialog::colorSelected,
            this,
            &MsgDataMappingAddDialog::slt_ColorSelected
            );
    colorPicker->exec();
}
