/**
 * @file codelineedit.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief Provides a QLineEdit specific for entering message codes
 */
#ifndef CODELINEEDIT_H
#define CODELINEEDIT_H

#include <QLineEdit>
#include <QMetaObject>

class MessageConfig;

#include "Msg.h"

/**
 * @brief The CodeLineEdit
 */
class CodeLineEdit : public QLineEdit
{
public:
    CodeLineEdit( QWidget *parent = Q_NULLPTR );
    CodeLineEdit( const MessageConfig *msgConfig, QWidget *parent = Q_NULLPTR );
    virtual ~CodeLineEdit();

    void setMsgConfig(const MessageConfig *msgConfig);

    MsgCodeType getCode() const;

private:
    const MessageConfig *msgConfig;
    QMetaObject::Connection colorizeLineEditConnection;

    void msgConfigChanged();
};

#endif /* CODELINEEDIT_H */
