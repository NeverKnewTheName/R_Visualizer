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
    explicit MsgIDLineEdit(
            IMsgIDMappingManager *msgIDMappingManager,
            QWidget *parent = Q_NULLPTR
            );
    ~MsgIDLineEdit();

    int convertStringToNumber(const QString &number) const;

    MsgIDType getMsgID() const;
    void setMsgID(const MsgIDType &msgID);

    void setCompleter(QCompleter *completer);
    void setMappingManager(IMsgIDMappingManager *msgIDMappingManager);

private slots:
    void on_idLineEdit_textChanged(const QString &arg1);

private:
    Ui::MsgIDLineEdit *ui;
    IMsgIDMappingManager *msgIDMappingManager;
};

/**
 * @}
 */

#endif // MSGIDLINEEDIT_H
