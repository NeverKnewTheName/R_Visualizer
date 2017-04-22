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

class IMsgCodeMappingManager;

/**
 * @brief The CodeLineEdit
 */
class CodeLineEdit : public QLineEdit
{
public:
    CodeLineEdit( QWidget *parent = Q_NULLPTR );
    CodeLineEdit(const IMsgCodeMappingManager *msgCodeMappingManager,
            QCompleter *msgCodeAliasCompleter = Q_NULLPTR,
            QWidget *parent = Q_NULLPTR
            );
    virtual ~CodeLineEdit();

    void setMsgCodeMapping(const IMsgCodeMappingManager *msgCodeMappingManager);

    MsgCodeType getMsgCode() const;

private:
    const IMsgCodeMappingManager *msgCodeMappingManager;
    QMetaObject::Connection colorizeLineEditConnection;

    void connectMsgCodeMapping();
    virtual MsgCodeType convertTextToMsgCode(const QString &text) const;
    /* void msgConfigChanged(); */
};

#endif /* CODELINEEDIT_H */
