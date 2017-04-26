/**
 * \file MsgIDType.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Typedefs for the Message ID Field
 */
#ifndef MSGIDTYPE_H
#define MSGIDTYPE_H

#include <QMetaType>
#include "MsgFieldType.h"

/**
 * @addtogroup MessageFieldGroup
 * 
 * @{
 */

/**
 * \brief Typedef for the primitive type of a message ID
 */
typedef quint16 MsgIDPrimitiveType;

CREATE_OPAQUE_MSG_FIELD_TYPE(MsgIDPrimitiveType, MsgIDType)

Q_DECLARE_METATYPE(MsgIDType)

/**
 * @}
 */

#endif /* MSGIDTYPE_H */
