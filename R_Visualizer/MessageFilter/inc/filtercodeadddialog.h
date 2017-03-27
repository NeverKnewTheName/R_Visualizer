/**
 * \file filtercodeadddialog.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * @brief A Dialog for inputting message codes as filter criteria
 */
#ifndef FILTERCODEADDDIALOG_H
#define FILTERCODEADDDIALOG_H

#include <QDialog>

class MessageConfig;

#include "Msg.h"

namespace Ui {
class FilterCodeAddDialog;
}

/**
 * @brief The FilterCodeAddDialog
 */
class FilterCodeAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterCodeAddDialog( const MessageConfig *msgConfig, QWidget *parent = 0);
    ~FilterCodeAddDialog();

private:
    Ui::FilterCodeAddDialog *ui;
    const MessageConfig *msgConfig;

signals:
    void commit(const MsgCodeType codeToCommit);

private slots:
    void readyToCommit();
};

#endif // FILTERCODEADDDIALOG_H
