/**
 * \file MessageCodeType.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Typedefs for the Message Code Field
 */
#ifndef MSGCODETYPE_H
#define MSGCODETYPE_H

#include "MsgFieldType.h"

/**
 * \brief Typedef for the primitive type of a message code
 */
typedef quint16 MsgCodePrimitiveType;
/**
 * \brief Typedef to the actual true typedef class for a message code
 */
typedef MsgFieldType<MsgCodePrimitiveType> MsgCodeType;

#endif /* MSGCODETYPE_H */
