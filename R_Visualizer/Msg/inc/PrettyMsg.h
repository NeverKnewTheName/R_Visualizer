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
#include "Msg.h"
#include "IMsgDataFormatter.h"

/**
 * @brief The PrettyMsg
 */
class PrettyMsg : public PrettyMsgCloneable<PrettyMsg, Msg>
{
public:
    PrettyMsg();
    PrettyMsg(const Msg &originalMsg);
    PrettyMsg(const PrettyMsg &other);

    virtual ~PrettyMsg();

    QString getMsgIDPlainTextAlias() const;
    void setMsgIDPlainTextAlias(const QString &msgIDAlias);
    QColor getMsgIDColorRepresentation() const;
    void setMsgIDColorRepresentation(const QColor &msgIDColorRepresentation);

    QString getMsgCodePlainTextAlias() const;
    void setMsgCodePlainTextAlias(const QString &msgCodeAlias);
    QColor getMsgCodeColorRepresentation() const;
    void setMsgCodeColorRepresentation(const QColor &msgCodeColorRepresentation);

    QString getParsedMsgDataString() const;
    QColor getParsedMsgDataColor() const;
    void setMsgDataFormatter(const IMsgDataFormatter &msgDataFormatter);

private:
    std::unique_ptr<IMsgDataFormatter> msgDataFormatterUniqPtr;
    QString msgIDPlainTextAlias;
    QString msgCodePlainTextAlias;
    QColor msgIDColorRepresentation;
    QColor msgCodeColorRepresentation;
};

#endif /* PRETTYMSG_H */
