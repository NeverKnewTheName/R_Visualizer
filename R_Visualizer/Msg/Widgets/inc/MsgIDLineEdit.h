/**
 * @file MsgIDLineEdit.h
 * @author Christian Neuberger
 * @date date
 *
 * @brief A Simple LineEdit widget to insert MsgIDType into
 *
 */
#ifndef MSGIDLINEEDIT_H
#define MSGIDLINEEDIT_H

#include <QWidget>
#include <QCompleter>
#include <QStringList>

#include <tuple>

#include "AbstractMsgFieldLineEdit.h"
#include "MsgIDType.h"

class IMsgIDMappingManager;

namespace Ui {
class MsgIDLineEdit;
}

/**
 * @addtogroup MessageWidgetsGroup
 *
 * @{
 *
 */

/**
 * @brief The MsgIDLineEdit
 */
class MsgIDLineEdit :
        public QWidget,
        public AbstractMsgFieldLineEdit
{
    Q_OBJECT

public:
    explicit MsgIDLineEdit(QWidget *parent = 0);
    ~MsgIDLineEdit();

    int convertStringToNumber(const QString &number) const;

    QString convertNumberToString(
            const int number,
            const int base
            ) const;

    MsgIDType getMsgID() const;
    void setMsgID(const MsgIDType &msgID);

    void setCompleter(QCompleter *completer);
    void setMappingManager(IMsgIDMappingManager *msgIDMappingManager);

private slots:
    void on_idLineEdit_textChanged(const QString &arg1);
    void on_numFormatComboBox_currentIndexChanged(int index);

private:
    Ui::MsgIDLineEdit *ui;
    IMsgIDMappingManager *msgIDMappingManager;
    const QVector<std::tuple<int, QString, QString>> numData;
    QStringList numFormatStringList;
    QStringList numInputMasks;
};

/**
 * @}
 */

#endif // MSGIDLINEEDIT_H
