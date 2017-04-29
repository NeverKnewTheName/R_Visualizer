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
#include <QCompleter>

#include <QMetaObject>

#include <AbstractMsgFieldLineEdit.h>
#include "MsgCodeType.h"

class IMsgCodeMappingManager;

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
class MsgCodeLineEdit :
    public QWidget,
    public AbstractMsgFieldLineEdit
{
    Q_OBJECT

public:
    explicit MsgCodeLineEdit(
            /* IMsgCodeMappingManager *msgCodeMappingManager, */
            QWidget *parent = 0
            );
    ~MsgCodeLineEdit();

    int convertStringToNumber(const QString &number) const;

    MsgCodeType getMsgCode() const;
    void setMsgCode(const MsgCodeType &msgCode);

    void setCompleter(QCompleter *completer);
    void setMappingManager(IMsgCodeMappingManager *msgCodeMappingManager);

private slots:
    void codeLineEditTextChanged(const QString &arg1);

private:
    Ui::MsgCodeLineEdit *ui;
    IMsgCodeMappingManager *msgCodeMappingManager;
    QMetaObject::Connection backGroundColorChangerConnection;
};

/**
 * @}
 */

#endif // MSGCODELINEEDIT_H
