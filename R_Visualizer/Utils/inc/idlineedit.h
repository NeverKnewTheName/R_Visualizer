#ifndef IDLINEEDIT_H
#define IDLINEEDIT_H

#include <QLineEdit>
#include <QMetaObject>

class MessageConfig;

#include "msg.h"

class IDLineEdit : public QLineEdit
{
public:
    IDLineEdit( QWidget *parent = Q_NULLPTR);
    IDLineEdit( const MessageConfig *msgConfig, QWidget *parent = Q_NULLPTR );
    virtual ~IDLineEdit();

    void setMsgConfig(const MessageConfig *msgConfig);

    MsgIDType getID() const;

private:
    const MessageConfig *msgConfig;
    QMetaObject::Connection colorizeLineEditConnection;

    void msgConfigChanged();

};

#endif /* IDLINEEDIT_H */
