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
#include <QCompleter>

#include "MsgCodeType.h"

class IMsgCodeMapping;

/**
 * @brief The CodeLineEdit
 */
class CodeLineEdit : public QLineEdit
{
public:
    CodeLineEdit( QWidget *parent = Q_NULLPTR );
    CodeLineEdit(
            const IMsgCodeMapping *msgCodeMapping,
            QCompleter *msgCodeAliasCompleter = Q_NULLPTR,
            QWidget *parent = Q_NULLPTR
            );
    virtual ~CodeLineEdit();

    void setMsgCodeMapping(const IMsgCodeMapping *msgCodeMapping);

    MsgCodeType getMsgCode() const;

private:
    const IMsgCodeMapping *msgCodeMapping;
    QMetaObject::Connection colorizeLineEditConnection;

    void connectMsgCodeMapping();
    virtual MsgCodeType convertTextToMsgCode(const QString &text) const;
    /* void msgConfigChanged(); */
};

#endif /* CODELINEEDIT_H */
