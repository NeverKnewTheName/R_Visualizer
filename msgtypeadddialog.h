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

private slots:
    void colorSelected(const QColor &color);
    void readyToCommit();

    void on_colorPickerPushButton_clicked();

signals:
    void commit(const int code, const QString message, const QColor color);
};

#endif // MSGTYPEADDDIALOG_H
