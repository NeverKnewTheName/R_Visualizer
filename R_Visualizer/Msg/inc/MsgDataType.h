/**
 * \file MsgDataType.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Typedefs for the Message Data Field
 */
#ifndef MSGDATATYPE_H
#define MSGDATATYPE_H

#include <QMetaType>
#include <QVector>

#include "MsgFieldType.h"

/**
 * @addtogroup MessageFieldGroup
 * 
 * @{
 */

/**
 * \brief Typedef for the primitive type of a single data byte of a message's
 * data field
 */
typedef quint8 MsgDataBytePrimitiveType;

CREATE_OPAQUE_MSG_FIELD_TYPE(MsgDataBytePrimitiveType, MsgDataByteType)

Q_DECLARE_METATYPE(MsgDataByteType)

/**
 * \brief Typedef for a message's data
 * 
 * \note This groups the indiviual data bytes of the data field
 */
typedef QVector<MsgDataByteType> MsgDataType;

Q_DECLARE_METATYPE(MsgDataType)

/**
 * @}
 */

#endif /* MSGDATATYPE_H */
