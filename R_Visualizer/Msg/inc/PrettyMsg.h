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
 * 
 * The PrettyMsg class unifies the #IPrettyMsg and the #IMsg interface. This
 * way a PrettyMsg can either be used as an #IPrettyMsg or directly as an #IMsg.
 * The composition approach was chosen to trim down the inheritance hierarchy.
 * 
 * The IMsgCRTPHelper class is used to provide a default implementation of the
 * cloneMsg method.
 */
class PrettyMsg :
    public IPrettyMsg,
    public AbstractMsgCRTPHelper<PrettyMsg>
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

    void setMsgID(const MsgIDType &msgID);
    const MsgIDType getMsgID() const;

    void setMsgCode(const MsgCodeType &msgCode);
    const MsgCodeType getMsgCode() const;

    void setMsgData(const MsgDataType &msgData);
    const MsgDataType getMsgData() const;

private:
    std::unique_ptr<IMsg> originalMsg;
    std::unique_ptr<IMsgDataFormatter> msgDataFormatterUniqPtr;
    QString msgIDPlainTextAlias;
    QString msgCodePlainTextAlias;
    QColor msgIDColorRepresentation;
    QColor msgCodeColorRepresentation;
};

#endif /* PRETTYMSG_H */
