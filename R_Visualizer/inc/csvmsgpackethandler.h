/**
 * \file csvmsgpackethandler.h
 * \author Christian Neuberger
 * \date 2017-01-31
 * 
 * \brief Handles #Msg packages that are given as a CSV file
 * 
 */
#ifndef CSVMSGPACKETHANDLER_H
#define CSVMSGPACKETHANDLER_H

#include "hugeqvector.h"
#include "msg.h"
#include <QVector>

//! Takes care of parsing #Msg packages in CSV file format
/**
 * The #CsvMsgPacketHandler is used to read whole packages of #Msgs from a CSV file and
 * to store whole packages of #Msgs to a CSV file.
 * 
 * Even though the standard file format of R_Visualizer is JSON, being able to handle CSV 
 * files comes in handy when dealing with files that were exported by tabular applications
 * such as Excel.
 */
class CsvMsgPacketHandler
{
public:
    /**
     * \brief Constructs a default #CsvMsgPacketHandler object
     */
    CsvMsgPacketHandler();
    ~CsvMsgPacketHandler();

    /**
     * \brief Parses CSV data to a #HugeQVector object containing the #Msgs
     * 
     * \param[in] csvMsgPacketString CSV string that contains the #Msgs
     * 
     * \return #HugeQVector of #Msgs
     */
    HugeQVector<Msg> parseCsvMsgPacket(QString &csvMsgPacketString);

    /**
     * \brief Parses a #HugeQVector of #Msgs to a CSV string
     * 
     * \param[in] msgs #HugeQVector of #Msgs to parse
     * 
     * \return QString that resembles the #Msgs as a CSV string
     */
    QString parseToString(HugeQVector<Msg> msgs);

private:
};

#endif // CSVMSGPACKETHANDLER_H
