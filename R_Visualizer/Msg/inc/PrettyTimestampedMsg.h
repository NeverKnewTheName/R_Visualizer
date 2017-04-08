#ifndef PRETTYTIMESTAMPEDMSG_H
#define PRETTYTIMESTAMPEDMSG_H

#include <QString>
#include <QColor>
#include <QDateTime>
#include <memory>

#include "IPrettyMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "ITimestampedMsg.h"
#include "IMsgDataFormatter.h"

class PrettyTimestampedMsg :
    public IPrettyMsg,
    public AbstractTimestampedMsgCRTPHelper<PrettyTimestampedMsg>
{
public:
    /**
     * @brief Default Constructor for use with QVector..
     */
    PrettyTimestampedMsg();
    PrettyTimestampedMsg(const ITimestampedMsg &originalMsg);
    PrettyTimestampedMsg(const PrettyTimestampedMsg &other);

    virtual ~PrettyTimestampedMsg();

    PrettyTimestampedMsg &operator =(const PrettyTimestampedMsg &other);

    QString getMsgIDPlainTextAlias() const;
    void setMsgIDPlainTextAlias(const QString &msgIDAlias);
    QColor getMsgIDColorRepresentation() const;
    void setMsgIDColorRepresentation(const QColor &msgIDColorRepresentation);

    QString getMsgCodePlainTextAlias() const;
    void setMsgCodePlainTextAlias(const QString &msgCodePlainTextAlias);
    QColor getMsgCodeColorRepresentation() const;
    void setMsgCodeColorRepresentation(const QColor &msgCodeColorRepresentation);

    QString getParsedMsgDataString() const;
    QColor getParsedMsgDataColor() const;
    void setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter);

    void setMsgID(const MsgIDType &msgID);
    const MsgIDType getMsgID() const;

    void setMsgCode(const MsgCodeType &msgCode);
    const MsgCodeType getMsgCode() const;

    void setMsgData(const MsgDataType &msgData);
    const MsgDataType getMsgData() const;

    void setTimestamp(const QDateTime &newTimestamp);
    const QDateTime getTimestamp() const;

private:
    std::unique_ptr<ITimestampedMsg> originalMsg;
    std::unique_ptr<IMsgDataFormatter> msgDataFormatterUniqPtr;
    QString msgIDPlainTextAlias;
    QString msgCodePlainTextAlias;
    QColor msgIDColorRepresentation;
    QColor msgCodeColorRepresentation;
};

#endif /* PRETTYTIMESTAMPEDMSG_H */
