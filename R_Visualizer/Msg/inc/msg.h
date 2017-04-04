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

class FileParser;

#include "IFileParsable.h"

typedef QVector<quint8> DataByteVect, *PDataByteVect;
Q_DECLARE_METATYPE(DataByteVect)

struct MsgData
{
    MsgData() : DataSizeInBytes(0){}
    MsgData(const MsgData &other) : DataBytes(other.DataBytes), DataSizeInBytes(other.DataSizeInBytes){}
    MsgData(const DataByteVect &dataBytes) : DataBytes(dataBytes), DataSizeInBytes(dataBytes.size()) {}
    ~MsgData(){}

    DataByteVect DataBytes;
    unsigned int DataSizeInBytes;
};

Q_DECLARE_METATYPE(MsgData);

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
class Msg : public IFileParsable
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

    MsgData getData() const;
    QByteArray getDataAsByteArray() const;
    void setData(const DataByteVect &dataBytes);
    void setDataByte(const quint8 index, const quint8 dataByte);

    QString getMessageAsString() const;
    QString getDataAsString() const;

    void parseIN(QJsonObject jsonMsg);
    QJsonObject parseOUT() const;

    MsgData getMsgData() const;

   /////////// IMsgStorable INTERFACE //////////////
   virtual QJsonObject ParseToJson() const;
   virtual void ParseFromJson(const QJsonObject &jsonObj);

    void accept(FileParser *visitor);

private:
    QDateTime msgTimestamp; //!< Timestamp of when the message was received
    MsgIDType msgID; //!< The ID that clearly identifies the sender of a message
    MsgCodeType msgCode; //!< The Code that clearly identifies the purpose of the message
    MsgData msgData; //!< Optional data accompaying the message
};

//Q_DECLARE_METATYPE(Msg);

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
