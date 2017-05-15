#ifndef MSGDATAFORMATSTRINGEDITORDIALOG_H
#define MSGDATAFORMATSTRINGEDITORDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class MsgDataFormatStringEditorDialog;
}

class MsgDataFormatStringEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgDataFormatStringEditorDialog(QWidget *parent = 0);
    ~MsgDataFormatStringEditorDialog();

    void setFormatString(const QString &formatString);
    QString getFormatString() const;

signals:
    void sgnl_Commit(const QString &formatString);

private slots:
    void slt_ReadyToCommit();

    void on_addNewLineBtn_clicked();
    void on_addTabBtn_clicked();
    void on_addFieldBtn_clicked();
    void on_addOperationBtn_clicked();
    void on_formatStringTextEdit_textChanged();

    void on_addNumConversionBtn_clicked();

private:
    Ui::MsgDataFormatStringEditorDialog *ui;
    const QStringList dataFields;
    const QStringList operations;
    const QStringList numericalConversion;
    const QString tokenDelimiter;
    const QString operationStartTemplateString;
    const QString operationEndTemplateString;
};

#endif // MSGDATAFORMATSTRINGEDITORDIALOG_H
