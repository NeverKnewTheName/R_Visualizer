#ifndef MSGTYPEFORMATTERDIALOG_H
#define MSGTYPEFORMATTERDIALOG_H

#include <QDialog>

namespace Ui {
class MsgTypeFormatterDialog;
}

class MsgTypeFormatterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgTypeFormatterDialog(QWidget *parent = 0);
    ~MsgTypeFormatterDialog();

    void setFormatString(QString format);
    QString getFormatString() const;

    enum
    {
        Data0,
        Data1,
        Data2,
        Data3,
        Data4,
        Data5,
        Data6,
        Value,
        NR_OF_FIELDS
    }dataFieldEnum;

    enum
    {
        Plus,
        Minus,
        Mult,
        Div,
        Mod,
        RShift,
        LShift,
        And,
        Or,
        XOr,
        NR_OF_OPERATIONS
    }operationEnum;

private:
    Ui::MsgTypeFormatterDialog *ui;
    QStringList dataFields;
    QStringList operations;

private slots:
    void readyToCommit();

    void on_formatPlainTextEdit_textChanged();

    void on_AddNewLinepushButton_clicked();

    void on_addTabPushButton_clicked();

    void on_addFieldPushButton_clicked();

    void on_addOperationPushButton_clicked();

signals:
    void commit(QString formatString);
};

#endif // MSGTYPEFORMATTERDIALOG_H
