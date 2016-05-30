#include "msgtypeformatterdialog.h"
#include "ui_msgtypeformatterdialog.h"

MsgTypeFormatterDialog::MsgTypeFormatterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgTypeFormatterDialog)
{
    ui->setupUi(this);
    connect(this, &MsgTypeFormatterDialog::accepted, this, &MsgTypeFormatterDialog::readyToCommit);

    dataFields = QStringList() << "Data0"
                               << "Data1"
                               << "Data2"
                               << "Data3"
                               << "Data4"
                               << "Data5"
                               << "Data6"
                               << "Value";

    operations = QStringList() << "+"
                               << "-"
                               << "*"
                               << "/"
                               << "%"
                               << ">>"
                               << "<<"
                               << "&"
                               << "|"
                               << "^";

    ui->fieldComboBox->addItems(dataFields);
    ui->operand1_ComboBox->addItems(dataFields);
    ui->operand2_ComboBox->addItems(dataFields);
    ui->operationComboBox->addItems(operations);
}

MsgTypeFormatterDialog::~MsgTypeFormatterDialog()
{
    delete ui;
}

void MsgTypeFormatterDialog::setFormatString(QString format)
{
    ui->formatPlainTextEdit->clear();
    ui->formatPlainTextEdit->textCursor().insertText(format);
    ui->formatPlainTextEdit->setFocus();
}

QString MsgTypeFormatterDialog::getFormatString() const
{
    return ui->formatPlainTextEdit->document()->toPlainText();
}

void MsgTypeFormatterDialog::readyToCommit()
{
    emit commit(ui->formatPlainTextEdit->document()->toPlainText());
}

void MsgTypeFormatterDialog::on_formatPlainTextEdit_textChanged()
{
    QString textToSet = ui->formatPlainTextEdit->document()->toPlainText();
    textToSet.replace("\n","\\n");
    textToSet.replace("\t","\\t");
    ui->formatStringLineEdit->setText(textToSet);
}

void MsgTypeFormatterDialog::on_AddNewLinepushButton_clicked()
{
    ui->formatPlainTextEdit->textCursor().insertText("\n");
    ui->formatPlainTextEdit->setFocus();
    //ui->formatPlainTextEdit->appendPlainText("\n");
}

void MsgTypeFormatterDialog::on_addTabPushButton_clicked()
{
    ui->formatPlainTextEdit->textCursor().insertText("\t");
    ui->formatPlainTextEdit->setFocus();
    //ui->formatPlainTextEdit->appendPlainText("\t");
}

void MsgTypeFormatterDialog::on_addFieldPushButton_clicked()
{
    ui->formatPlainTextEdit->textCursor().insertText(
                QString("#%1#").arg(this->dataFields.at(ui->fieldComboBox->currentIndex()))
                );
}

void MsgTypeFormatterDialog::on_addOperationPushButton_clicked()
{
    QString operationString = QString("#OP#(#%1##%2##%3#)#/OP#")
            .arg(this->dataFields.at(ui->operand1_ComboBox->currentIndex()))
            .arg(this->operations.at(ui->operationComboBox->currentIndex()))

            .arg(this->dataFields.at(ui->operand2_ComboBox->currentIndex()));

    ui->formatPlainTextEdit->textCursor().insertText(
                operationString
                );
}
