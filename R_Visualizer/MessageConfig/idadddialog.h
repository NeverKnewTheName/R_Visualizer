#ifndef IDADDDIALOG_H
#define IDADDDIALOG_H

#include <QDialog>

namespace Ui {
class IDAddDialog;
}

class IDAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IDAddDialog(QWidget *parent = 0);
    ~IDAddDialog();

private:
    Ui::IDAddDialog *ui;
    QStringList inputMasks;

    int parseToNumber(QString numericalString);
    QString parseToString(int number);

private slots:
    void colorSelected(const QColor &color);
    void on_pushButton_clicked();
    void readyToCommit();

    void on_numericallFormatComboBox_currentIndexChanged(int index);

signals:
    void commit(const int id, const QString name, const QColor color);
};

#endif // IDADDDIALOG_H