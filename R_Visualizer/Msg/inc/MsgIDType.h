/**
 * \file MsgIDType.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Typedefs for the Message ID Field
 */
#ifndef MSGIDTYPE_H
#define MSGIDTYPE_H

#include "MsgFieldType.h"

/**
 * \brief Typedef for the primitive type of a message ID
 */
typedef quint16 MsgIDPrimitiveType;
/**
 * \brief Typedef to the actual true typedef class for a message ID
 */
/* typedef MsgFieldType<MsgIDPrimitiveType> MsgIDType; */

CREATE_OPAQUE_MSG_FIELD_TYPE(MsgIDPrimitiveType, MsgIDType)


#endif /* MSGIDTYPE_H */
