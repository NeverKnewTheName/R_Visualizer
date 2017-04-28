/**
 * @file MsgCodeLineEdit.h
 * @author Christian Neuberger
 * @date date
 *
 * @brief A Simple LineEdit widget to insert #MsgCodeType into
 *
 */
#ifndef MSGCODELINEEDIT_H
#define MSGCODELINEEDIT_H

#include <QWidget>

namespace Ui {
class MsgCodeLineEdit;
}

/**
 * @addtogroup MessageWidgetsGroup
 *
 * @{
 *
 */

/**
 * @brief The MsgCodeLineEdit
 */
class MsgCodeLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit MsgCodeLineEdit(QWidget *parent = 0);
    ~MsgCodeLineEdit();

private slots:
    void on_codeLineEdit_textChanged(const QString &arg1);

    void on_numFormatComboBox_currentIndexChanged(int index);

private:
    Ui::MsgCodeLineEdit *ui;
};

/**
 * @}
 */

#endif // MSGCODELINEEDIT_H
