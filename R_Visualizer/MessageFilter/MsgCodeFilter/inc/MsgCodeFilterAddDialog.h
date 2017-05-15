#ifndef MSGCODEFILTERADDDIALOG_H
#define MSGCODEFILTERADDDIALOG_H

#include <QDialog>

#include "MsgCodeType.h"

class IMsgCodeMappingManager;

namespace Ui {
class MsgCodeFilterAddDialog;
}

class MsgCodeFilterAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgCodeFilterAddDialog(
            IMsgCodeMappingManager *msgCodeMappingManager,
            QWidget *parent = Q_NULLPTR
            );
    ~MsgCodeFilterAddDialog();

signals:
    void sgnl_commit(const MsgCodeType &msgCode);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::MsgCodeFilterAddDialog *ui;
    IMsgCodeMappingManager *msgCodeMappingManager;
};

#endif // MSGCODEFILTERADDDIALOG_H
