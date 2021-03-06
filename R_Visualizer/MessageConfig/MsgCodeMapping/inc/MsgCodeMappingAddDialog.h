/**
 * \file MsgCodeMappingAddDialog.h
 * @author Christian Neuberger
 * @date 2017-03-23
 */
#ifndef MSGTYPEADDDIALOG_H
#define MSGTYPEADDDIALOG_H

#include <QDialog>

#include "MsgCodeType.h"

namespace Ui {
class MsgCodeMappingAddDialog;
}

/**
 * @addtogroup MsgCodeMappingGroup
 * 
 * @{
 */

/**
 * @brief The MsgCodeMappingAddDialog
 */
class MsgCodeMappingAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgCodeMappingAddDialog(QWidget *parent = 0);
    ~MsgCodeMappingAddDialog();

private:
    Ui::MsgCodeMappingAddDialog *ui;

private slots:
    void colorSelected(const QColor &color);
    void readyToCommit();

    void on_colorPickerPushButton_clicked();

signals:
    void commit(
            const MsgCodeType &code,
            const QString &alias,
            const QColor &colorRepresentation
            );
};

/**
 * @}
 */
#endif // MSGTYPEADDDIALOG_H
