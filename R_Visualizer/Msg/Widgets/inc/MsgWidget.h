#ifndef MSGWIDGET_H
#define MSGWIDGET_H

#include <QWidget>
#include <QCompleter>

#include "Msg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

class IMsgIDMappingManager;
class IMsgCodeMappingManager;

namespace Ui {
class MsgWidget;
}

class MsgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgWidget(QWidget *parent = 0);
    ~MsgWidget();

    MsgIDType getMsgID() const;
    MsgCodeType getMsgCode() const;
    MsgDataType getMsgData() const;

    Msg getMsg() const;
    void setMsg(const IMsg &msgToSet);

    void setMsgIDMapping(IMsgIDMappingManager *msgIDMappingManager);
    void setMsgIDCompleter(QCompleter *msgIDCompleter);
    void setMsgCodeMapping(IMsgCodeMappingManager *msgCodeMappingManager);
    void setMsgCodeCompleter(QCompleter *msgCodeCompleter);

private:
    Ui::MsgWidget *ui;
    IMsgIDMappingManager *msgIDMappingManager;
    IMsgCodeMappingManager *msgCodeMappingManager;
};

#endif // MSGWIDGET_H
