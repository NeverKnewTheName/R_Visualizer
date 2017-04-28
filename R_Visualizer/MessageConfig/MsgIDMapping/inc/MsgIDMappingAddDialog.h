/**
 * @file MsgIDMappingAddDialog.h
 * @author Christian Neuberger
 * @date 2017-04-27
 * 
 * @brief Dialog to add/edit #MsgIDMapping
 */
#ifndef IDADDDIALOG_H
#define IDADDDIALOG_H

#include <QDialog>

#include "MsgIDType.h"

namespace Ui {
class MsgIDMappingAddDialog;
}

/**
 * @addtogroup MsgIDMappingGroup
 * 
 * @{
 */

/**
 * @brief The MsgIDMappingAddDialog
 */
class MsgIDMappingAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgIDMappingAddDialog(QWidget *parent = 0);
    ~MsgIDMappingAddDialog();

private:
    Ui::MsgIDMappingAddDialog *ui;
    QStringList inputMasks;

    int parseToNumber(QString numericalString);
    QString parseToString(const int number);

private slots:
    void colorSelected(const QColor &color);
    void on_pushButton_clicked();
    void readyToCommit();

    void on_numericallFormatComboBox_currentIndexChanged(int index);

signals:
    void sgnl_commit(
            const MsgIDType &id,
            const QString &alias,
            const QColor &colorRepresentation
            );
};

/**
 * @}
 */
#endif // IDADDDIALOG_H
