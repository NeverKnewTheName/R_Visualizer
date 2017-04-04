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
    public PrettyMsgCloneable<PrettyTimestampedMsg, ITimestampedMsg>
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

    /**
     * @brief For when only the contained #ITimestampedMsg must be cloned
     */
    IMsgUniqPtr cloneMsg() const;

    void setMsgID(const MsgIDType &msgID);
    const MsgIDType getMsgID() const;

    void setMsgCode(const MsgCodeType &msgCode);
    const MsgCodeType getMsgCode() const;

    void setMsgData(const MsgDataType &msgData);
    const MsgDataType getMsgData() const;

    void setTimestamp(const QDateTime &newTimestamp);
    const QDateTime getTimestamp() const;

    /**
     * @brief Short circuit to the #IMsg accept method
     * 
     * PrettyMsg are not to be parsed to files, because they are dynamically
     * created. Therefore treat them as regular IMsg derivates regarding
     * parsing to file and thereof.
     */
    void accept(FileParser *visitor);
private:
    std::unique_ptr<IMsgDataFormatter> msgDataFormatterUniqPtr;
    std::unique_ptr<ITimestampedMsg> originalMsg;
    QString msgIDPlainTextAlias;
    QString msgCodePlainTextAlias;
    QColor msgIDColorRepresentation;
    QColor msgCodeColorRepresentation;
};

#endif /* PRETTYTIMESTAMPEDMSG_H */
