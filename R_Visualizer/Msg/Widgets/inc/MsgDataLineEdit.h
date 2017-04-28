#ifndef MSGDATALINEEDIT_H
#define MSGDATALINEEDIT_H

#include <QWidget>

namespace Ui {
class MsgDataLineEdit;
}

/**
 * @addtogroup MessageWidgetsGroup
 *
 * @{
 *
 */

class MsgDataLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit MsgDataLineEdit(QWidget *parent = 0);
    ~MsgDataLineEdit();

private slots:
    void on_dataLineEdit_textChanged(const QString &arg1);

    void on_numFormatComboBox_currentIndexChanged(int index);

private:
    Ui::MsgDataLineEdit *ui;
};

/**
 * @}
 */

#endif // MSGDATALINEEDIT_H
