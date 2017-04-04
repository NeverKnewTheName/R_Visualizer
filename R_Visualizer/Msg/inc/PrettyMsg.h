/**
 * @file PrettyMsg.h
 * @author Christian Neuberger
 * @date 2017-03-26
 * 
 * @brief A PrettyMsg
 */
#ifndef PRETTYMSG_H
#define PRETTYMSG_H

#include <QString>
#include <QColor>
#include <memory>

#include "IPrettyMsg.h"
#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "IMsg.h"
#include "IMsgDataFormatter.h"

class FileParser;

/**
 * @brief The PrettyMsg
 */
class PrettyMsg : public PrettyMsgCloneable<PrettyMsg, IMsg>
{
public:
    /**
     * @brief Default Constructor for use with QVector..
     */
    PrettyMsg();
    PrettyMsg(const IMsg &originalMsg);
    PrettyMsg(const PrettyMsg &other);

    virtual ~PrettyMsg();

    PrettyMsg &operator =(const PrettyMsg &other);

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
     * @brief For when only the contained #IMsg must be cloned
     */
    IMsgUniqPtr cloneMsg() const;

    void setMsgID(const MsgIDType &msgID);
    const MsgIDType getMsgID() const;

    void setMsgCode(const MsgCodeType &msgCode);
    const MsgCodeType getMsgCode() const;

    void setMsgData(const MsgDataType &msgData);
    const MsgDataType getMsgData() const;

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
    std::unique_ptr<IMsg> originalMsg;
    QString msgIDPlainTextAlias;
    QString msgCodePlainTextAlias;
    QColor msgIDColorRepresentation;
    QColor msgCodeColorRepresentation;
};

#endif /* PRETTYMSG_H */
