/**
 * \file MsgCodeType.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Typedefs for the Message Code Field
 */
#ifndef MSGCODETYPE_H
#define MSGCODETYPE_H

#include <QMetaType>
#include "MsgFieldType.h"

/**
 * @addtogroup MessageFieldGroup
 * 
 * @{
 */

/**
 * \brief Typedef for the primitive type of a message code
 */
typedef quint16 MsgCodePrimitiveType;
/**
 * \brief Typedef to the actual true typedef class for a message code
 */
/* typedef MsgFieldType<MsgCodePrimitiveType> MsgCodeType; */

CREATE_OPAQUE_MSG_FIELD_TYPE(MsgCodePrimitiveType, MsgCodeType)

Q_DECLARE_METATYPE(MsgCodeType)

/**
 * @}
 */

#endif /* MSGCODETYPE_H */
