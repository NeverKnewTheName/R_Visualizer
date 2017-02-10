/**
 * \file msg.h
 * \author Christian Neuberger
 * \date 2017-02-02
 * 
 * \brief Msg class to represent a message in the system
 * 
 */
#ifndef MSG_H
#define MSG_H

#include <QDateTime>

#include <QMetaType>
#include <QVector>

#include <QSize>

#include "msgstorable.h"

typedef QVector<quint8> DataByteVect, *PDataByteVect;
Q_DECLARE_METATYPE(DataByteVect)

typedef struct _MsgData
{
    DataByteVect DataBytes;
    unsigned int DataSizeInBytes;
}MsgDataStruc, *PMsgDataStruc;

Q_DECLARE_METATYPE(MsgDataStruc)

typedef quint16 MsgIDType;

typedef quint16 MsgCodeType;

/**
 * \brief The Msg class represents one single message in the system
 * 
 * A message is the medium of exchange in the Message-Oriented Design of an R_Sys.
 * Therefore, all information and data are exchanged via Messages
 * 
 * Messages contain:
 * - A Timestamp of when the message was received
 * - A MessageID
 * - A MessageCode
 * - Optional Message Data
 *  
 * The MessageID clearly identifies the sender of the message
 * The MessageCode clearly identifies the purpose of the message
 * The optional data is additional information that is used for the purpose of the message
 * 
 */
class Msg : public IMsgStorable
{
public:
    /**
     * \brief Constructs a generic Msg
     *
     * \warning should not actually be used
     */
    Msg();
    /**
     * \brief Constructs a Msg by copying from another Msg
     */
    Msg(const Msg &other);
    /**
     * \brief Constructs a Msg according to a QJsonObject that contains the Msg's data
     */
    Msg(const QJsonObject &jsonObj);
    /**
     * \brief constructs a regular Msg
     */
    Msg(const QDateTime &timestamp, const MsgIDType id, const MsgCodeType code, DataByteVect dataBytes);
    virtual ~Msg();

    QDateTime getTimestamp() const;
    void setTimestamp(const QDateTime &value);

    MsgIDType getId() const;
    void setId(const MsgIDType value);

    MsgCodeType getCode() const;
    void setCode(const MsgCodeType value);

    PMsgDataStruc getData();
    QByteArray getDataAsByteArray() const;
    void setData(const DataByteVect dataBytes);
    void setDataByte(const quint8 index, const quint8 dataByte);

    QString getMessageAsString() const;
    QString getDataAsString() const;

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT() const;

    MsgDataStruc getMsgData() const;

    QSize getMsgSizeHint() const;

    void setMsgSizeHint(const QSize &value);


   /////////// IMsgStorable INTERFACE //////////////
   virtual QJsonObject ParseToJson() const;
   virtual void ParseFromJson(const QJsonObject &jsonObj);

private:
    QDateTime MsgTimestamp; //!< Timestamp of when the message was received
    MsgIDType MsgID; //!< The ID that clearly identifies the sender of a message
    MsgCodeType MsgCode; //!< The Code that clearly identifies the purpose of the message
    MsgDataStruc MsgData; //!< Optional data accompaying the message
    QSize msgSizeHint; //Size hint for painting... subject to removal -> OPTIMIZE //ToTHINK!
};

Q_DECLARE_METATYPE(Msg)

/**
 * \brief Class for received messages
 * 
 * IncomingMsg extends #Msg to include a timestamp that contains the time the message was received.
 */
class IncomingMsg
{
public:
   IncomingMsg (const QDateTime &timestamp, const MsgIDType &id, const MsgCodeType &code, const DataByteVect &dataBytes);
   virtual ~IncomingMsg ();

   const QDateTime &GetMsgTimeStamp() const;

   QJsonObject ParseToJson() const;
   void ParseFromJson(const QJsonObject &jsonObj);

private:
   const QDateTime MsgTimestamp; //!< Timestamp of when the message was received
};

/**
 * \brief Class for messages to send
 * 
 * OutgoingMsg extends #Msg to create a special class for messages that are to be sent.
 */
class OutgoingMsg
{
public:
    OutgoingMsg (const MsgIDType &id, const MsgCodeType &code, const DataByteVect &dataBytes );
    virtual ~OutgoingMsg ();

   QJsonObject ParseToJson() const;
   void ParseFromJson(const QJsonObject &jsonObj);
private:
    
};
#endif // MSG_H
