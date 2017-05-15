/**
 * @file MsgDataMappingAddDialog.h
 * @author Christian Neuberger
 * @date 2017-04-28
 *
 * @brief Dialog to add/edit #MsgDataMapping
 */
#ifndef MSGDATAMAPPINGADDDIALOG_H
#define MSGDATAMAPPINGADDDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QString>
#include <QColor>

#include "MsgIDType.h"
#include "MsgCodeType.h"

class IMsgIDMappingManager;
class IMsgCodeMappingManager;

namespace Ui {
class MsgDataMappingAddDialog;
}

/**
 * @addtogroup MsgDataMappingGroup
 * 
 * @{
 */

/**
 * @brief The MsgDataMappingAddDialog
 */
class MsgDataMappingAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgDataMappingAddDialog(QWidget *parent = 0);
    ~MsgDataMappingAddDialog();

    void setMsgIDMappingManager(
            IMsgIDMappingManager *msgIDMappingManager
                                );
    void setMsgCodeMappingManager(
            IMsgCodeMappingManager *msgCodeMappingManager
                                );

private:

signals:
    void sgnl_Commit(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const QString &msgFormatString,
            const QColor &defaultColor
            );

private slots:
    void slt_ColorSelected(const QColor &color);
    void slt_ReadyToCommit();

    void on_formatterPushButton_clicked();
    void on_colorPickerPushButton_clicked();

private:
    Ui::MsgDataMappingAddDialog *ui;
    QStringList numericalFormatStringList;
};

/**
 * @}
 */
#endif // MSGDATAMAPPINGADDDIALOG_H
