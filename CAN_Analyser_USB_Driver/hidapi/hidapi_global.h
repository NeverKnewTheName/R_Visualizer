#ifndef HIDAPI_GLOBAL_H
#define HIDAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HIDAPI_LIBRARY)
#   define HID_API_EXPORT Q_DECL_EXPORT
#   define HID_API_CALL
#else
#   define HID_API_EXPORT Q_DECL_IMPORT
#   define HID_API_CALL
#endif

#define HID_API_EXPORT_CALL HID_API_EXPORT HID_API_CALL /**< API export and call macro*/

#endif // HIDAPI_GLOBAL_H
