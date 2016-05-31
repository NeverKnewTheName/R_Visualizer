/**
 * @file	usb_driver_global.h
 * @author	Frank Ehard
 *
 * @copyright Copyright (C) 2015, Frank Ehard. All rights reserved.
 *
 * @license
 *   - This project is a free software and there is NO WARRANTY.
 *   - No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 *   - Redistributions of source code must retain the above copyright notice.
 */

#ifndef USB_DRIVER_H
#define USB_DRIVER_H

#include <QtCore/qglobal.h>

#if defined(USB_DRIVER_LIBRARY)
#   define USB_DRIVER_EXPORT Q_DECL_EXPORT
#else
#   define USB_DRIVER_EXPORT Q_DECL_IMPORT
#endif

#endif // USB_DRIVER_H
