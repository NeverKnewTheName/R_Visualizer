#ifndef MSGIDFILTERADDDIALOG_H
#define MSGIDFILTERADDDIALOG_H

#include <QDialog>

#include "MsgIDType.h"

class IMsgIDMappingManager;

namespace Ui {
class MsgIDFilterAddDialog;
}

class MsgIDFilterAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgIDFilterAddDialog(
            IMsgIDMappingManager *msgIDMappingManager,
            QWidget *parent = Q_NULLPTR
            );
    ~MsgIDFilterAddDialog();

signals:
    void sgnl_commit(const MsgIDType &msgID);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::MsgIDFilterAddDialog *ui;
    IMsgIDMappingManager *msgIDMappingManager;
};

#endif // MSGIDFILTERADDDIALOG_H
