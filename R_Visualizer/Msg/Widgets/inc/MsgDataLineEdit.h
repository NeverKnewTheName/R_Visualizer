/**
 * @file MsgDataLineEdit.h
 * @author Christian Neuberger
 * @date 2017-04-28
 * 
 * @brief Specialized line edit to enter #MsgDataType values
 */
#ifndef MSGDATALINEEDIT_H
#define MSGDATALINEEDIT_H

#include <QWidget>
#include <QString>

#include <tuple>

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

class IMsgDataMappingManager;

namespace Ui {
class MsgDataLineEdit;
}

/**
 * @addtogroup MessageWidgetsGroup
 *
 * @{
 *
 */

/**
 * @brief The MsgDatLineEdit
 */
class MsgDataLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit MsgDataLineEdit(
            IMsgDataMappingManager *msgDataMappingManager,
            QWidget *parent = Q_NULLPTR
            );
    ~MsgDataLineEdit();

    MsgDataType getMsgData() const;
    void setMsgData(const MsgDataType &msgData);

private:
    QString convertFormat(
            QString &number,
            const int oldFormatIndex,
            const int newFormatIndex
            );

    int convertToNumber(const QString &number) const;

    QStringList extractBytes(
            QString &number,
            int base,
            int width
            );
    QString numberFromBytes(
            QStringList bytes,
            int oldBase,
            int newBase,
            int width
            );

private slots:
    void on_dataLineEdit_textChanged(const QString &arg1);

    void on_numFormatComboBox_currentIndexChanged(int index);

private:
    Ui::MsgDataLineEdit *ui;
    IMsgDataMappingManager *msgDataMappingManager;
    /**
     * @brief Vector contains tuples that contain information about the
     * formatting
     * 
     * Each tuple contains the numerical base, the number's width, the number's
     * prefix, an input mask for the format, and a short name for the number
     * format,
     * 
     * In order:
     * - numerical base
     * - field width
     * - format prefix
     * - input mask
     * - short name
     */
    std::vector<std::tuple<int,int,QString,QString,QString>> formatData;
    int currentFormatIndex;
};

/**
 * @}
 */

#endif // MSGDATALINEEDIT_H
