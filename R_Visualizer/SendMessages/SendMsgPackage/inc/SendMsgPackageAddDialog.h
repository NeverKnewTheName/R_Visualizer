#ifndef SENDMSGPACKAGEADDDIALOG_H
#define SENDMSGPACKAGEADDDIALOG_H

#include <QDialog>

class IMsg;
class IMsgIDMappingManager;
class IMsgCodeMappingManager;

namespace Ui {
class SendMsgPackageAddDialog;
}

class SendMsgPackageAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendMsgPackageAddDialog(
            IMsgIDMappingManager *msgIDMappingManager,
            IMsgCodeMappingManager *msgCodeMappingManager,
            QWidget *parent = Q_NULLPTR
            );
    ~SendMsgPackageAddDialog();

signals:
    void sgnl_commit(const IMsg &msg);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SendMsgPackageAddDialog *ui;
};

#endif // SENDMSGPACKAGEADDDIALOG_H
