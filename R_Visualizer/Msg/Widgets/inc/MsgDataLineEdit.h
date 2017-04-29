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
#include <QCompleter>
#include <QEvent>
#include <QLineEdit>

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

class LineEditCursorHelper : public QObject
{
    Q_OBJECT

    bool eventFilter(QObject *watched, QEvent *event)
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(watched);

        if(lineEdit && event->type() == QEvent::FocusIn)
        {
            QMetaObject::invokeMethod(this, "setCursor", Qt::QueuedConnection, Q_ARG(QWidget *, lineEdit));
        }

        return QObject::eventFilter(watched, event);
    }

    Q_INVOKABLE void setCursor(QWidget *widget)
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(widget);
        if(lineEdit)
        {
            const QString &currentText = lineEdit->text().trimmed();
            lineEdit->setCursorPosition(currentText.length()+1);
        }
    }

public:
    LineEditCursorHelper(QObject *parent = Q_NULLPTR) : QObject(parent){}
    void installHelper(QLineEdit *lineEdit){lineEdit->installEventFilter(this);}
};

/**
 * @brief The MsgDatLineEdit
 */
class MsgDataLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit MsgDataLineEdit(
            /* IMsgDataMappingManager *msgDataMappingManager, */
            QWidget *parent = Q_NULLPTR
            );
    ~MsgDataLineEdit();

    MsgDataType getMsgData() const;
    void setMsgData(const MsgDataType &msgData);

    void setCompleter(QCompleter *complter);
    void setMappingManager(IMsgDataMappingManager *msgDataMappingManager);

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
    LineEditCursorHelper *lineEditCursorHelper;
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

    // QWidget interface
protected:
    void focusInEvent(QFocusEvent *event);
};

/**
 * @}
 */

#endif // MSGDATALINEEDIT_H
