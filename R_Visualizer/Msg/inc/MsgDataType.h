/**
 * \file MsgDataType.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Typedefs for the Message Data Field
 */
#ifndef MSGDATATYPE_H
#define MSGDATATYPE_H

#include <QVector>

#include "MsgFieldType.h"

/**
 * \brief Typedef for the primitive type of a single data byte of a message's
 * data field
 */
typedef quint8 MsgDataBytePrimitiveType;
/**
 * \brief Typedef to the actual true typedef class for a single data byte of a
 * message's data field
 */
/* typedef MsgFieldType<MsgDataBytePrimitiveType> MsgDataByteType; */

CREATE_OPAQUE_MSG_FIELD_TYPE(MsgDataBytePrimitiveType, MsgDataByteType)

/**
 * \brief Typedef for a message's data
 * 
 * \note This groups the indiviual data bytes of the data field
 */
typedef QVector<MsgDataByte> MsgDataType;

#endif /* MSGDATATYPE_H */
