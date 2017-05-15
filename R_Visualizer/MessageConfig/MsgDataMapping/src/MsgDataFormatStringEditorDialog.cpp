#include "MsgDataFormatStringEditorDialog.h"
#include "ui_msgdataformatstringeditordialog.h"

#include <QTextDocumentFragment>

MsgDataFormatStringEditorDialog::MsgDataFormatStringEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgDataFormatStringEditorDialog),
    dataFields({"Data0","Data1","Data2","Data3","Data4","Data5","Data6"}),
    operations({"+","-","*","/","%",">>","<<","&","|","^"}),
    numericalConversion({"HEX","OCT","BIN"}),
    tokenDelimiter("#"),
    operationStartTemplateString(tokenDelimiter+"%1"+tokenDelimiter+"("),
    operationEndTemplateString(")"+tokenDelimiter+"/%1"+tokenDelimiter)
{
    ui->setupUi(this);

    connect(
            this,
            &MsgDataFormatStringEditorDialog::accepted,
            this,
            &MsgDataFormatStringEditorDialog::slt_ReadyToCommit
            );

    ui->fieldComboBox->addItems(dataFields);
    ui->operationComboBox->addItems(operations);
    ui->operandFirstComboBox->addItems(dataFields);
    ui->operandFirstComboBox->addItem("Value");
    ui->operandSecondComboBox->addItems(dataFields);
    ui->operandSecondComboBox->addItem("Value");
    ui->numConversionComboBox->addItems(numericalConversion);
}

MsgDataFormatStringEditorDialog::~MsgDataFormatStringEditorDialog()
{
    delete ui;
}

void MsgDataFormatStringEditorDialog::setFormatString(const QString &formatString)
{
    ui->formatStringTextEdit->setPlainText(formatString);
}

QString MsgDataFormatStringEditorDialog::getFormatString() const
{
    return ui->formatStringTextEdit->document()->toPlainText();
}

void MsgDataFormatStringEditorDialog::slt_ReadyToCommit()
{
    const QString &formatString = getFormatString();
    emit sgnl_Commit(formatString);
}

void MsgDataFormatStringEditorDialog::on_addNewLineBtn_clicked()
{
    ui->formatStringTextEdit->textCursor().insertText("\n");
    ui->formatStringTextEdit->setFocus();
}

void MsgDataFormatStringEditorDialog::on_addTabBtn_clicked()
{
    ui->formatStringTextEdit->textCursor().insertText("\t");
    ui->formatStringTextEdit->setFocus();
}

void MsgDataFormatStringEditorDialog::on_addFieldBtn_clicked()
{
    const int index = ui->fieldComboBox->currentIndex();
    QString fieldToAdd;

    if(index >= dataFields.size())
    {
        //Has to be Value
        fieldToAdd = QString("VALUE");
    }
    else
    {
        //Is a data field
        fieldToAdd = dataFields.at(index);
        fieldToAdd.prepend(tokenDelimiter);
        fieldToAdd.append(tokenDelimiter);
    }

    ui->formatStringTextEdit->textCursor().insertText(fieldToAdd);
    ui->formatStringTextEdit->setFocus();
}

void MsgDataFormatStringEditorDialog::on_addOperationBtn_clicked()
{
    const int indexFirstOperand = ui->operandFirstComboBox->currentIndex();
    const int indexOperation = ui->operationComboBox->currentIndex();
    const int indexSecondOperand = ui->operandSecondComboBox->currentIndex();
    const QString operationToken("OP");
    const QString opStart(operationStartTemplateString.arg(operationToken));
    const QString opEnd(operationEndTemplateString.arg(operationToken));

    QString operationString;
    QString firstOperand;
    QString operation;
    QString secondOperand;

    bool valueIncluded = false;

    if(indexFirstOperand >= dataFields.size())
    {
        //Has to be Value
        firstOperand = QString("VALUE");
        valueIncluded = true;
    }
    else
    {
        //Is a data field
        firstOperand = dataFields.at(indexFirstOperand);
        firstOperand.prepend(tokenDelimiter);
        firstOperand.append(tokenDelimiter);
    }

    operation.prepend(tokenDelimiter);
    operation.append(operations.at(indexOperation));
    operation.append(tokenDelimiter);

    if(indexSecondOperand >= dataFields.size())
    {
        //Has to be Value
        secondOperand = QString("VALUE");
        valueIncluded = true;
    }
    else
    {
        //Is a data field
        secondOperand = dataFields.at(indexSecondOperand);
        secondOperand.prepend(tokenDelimiter);
        secondOperand.append(tokenDelimiter);
    }

    operationString.append(opStart);
    operationString.append(firstOperand);
    operationString.append(operation);
    operationString.append(secondOperand);
    operationString.append(opEnd);

    const int curCursorPosition = ui->formatStringTextEdit->textCursor().position();
    ui->formatStringTextEdit->textCursor().insertText(operationString);
    if(valueIncluded)
    {
        QTextCursor cursor(ui->formatStringTextEdit->textCursor());
        cursor.setPosition(ui->formatStringTextEdit->document()->toPlainText().lastIndexOf(QString("VALUE")),QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, QString("VALUE").length());

        ui->formatStringTextEdit->setTextCursor(cursor);
    }
    ui->formatStringTextEdit->setFocus();
}

void MsgDataFormatStringEditorDialog::on_formatStringTextEdit_textChanged()
{
    QString tempFormatString(ui->formatStringTextEdit->document()->toPlainText());

    tempFormatString.replace("\n","\\n");
    tempFormatString.replace("\t","\\t");

    ui->formatStringLineEdit->setText(tempFormatString);
}

void MsgDataFormatStringEditorDialog::on_addNumConversionBtn_clicked()
{
    const int numConversionIndex = ui->numConversionComboBox->currentIndex();
    const QString &convString = numericalConversion.at(numConversionIndex);
    const QString numConvStart(operationStartTemplateString.arg(convString));
    const QString numConvEnd(operationEndTemplateString.arg(convString));

    QString selection(ui->formatStringTextEdit->textCursor().selection().toPlainText());
    if(selection.isEmpty())
    {
        QString expression(ui->formatStringTextEdit->document()->toPlainText());
        expression.prepend(numConvStart);
        expression.append(numConvEnd);
        ui->formatStringTextEdit->document()->setPlainText(expression);
    }
    else
    {
        selection.prepend(numConvStart);
        selection.append(numConvEnd);
        const int selectionStart = ui->formatStringTextEdit->textCursor().selectionStart();
        ui->formatStringTextEdit->textCursor().removeSelectedText();
        ui->formatStringTextEdit->textCursor().insertText(selection);
    }
    ui->formatStringTextEdit->setFocus();
}
