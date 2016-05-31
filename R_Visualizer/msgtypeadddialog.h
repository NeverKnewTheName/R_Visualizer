#ifndef MSGTYPEADDDIALOG_H
#define MSGTYPEADDDIALOG_H

#include <QDialog>

namespace Ui {
class MsgTypeAddDialog;
}

class MsgTypeAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgTypeAddDialog(QWidget *parent = 0);
    ~MsgTypeAddDialog();

private:
    Ui::MsgTypeAddDialog *ui;
    QStringList inputMasks;

    int parseToNumber(QString numericalString);
    QString parseToString(int number);

private slots:
    void colorSelected(const QColor &color);
    void formatSelected(const QString &formatString);
    void readyToCommit();

    void on_colorPickerPushButton_clicked();

    void on_formatterPushButton_clicked();

    void on_numericallFormatComboBox_currentIndexChanged(int index);

signals:
    void commit(const int code, const QString codeName, const QString messageFormat, const QColor color);
};

#endif // MSGTYPEADDDIALOG_H
