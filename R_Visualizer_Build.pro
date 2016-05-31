TEMPLATE = subdirs

SUBDIRS +=  R_Visualizer \
            hidapi\
            libusb_driver \

hidapi.file = CAN_Analyser_USB_Driver/hidapi/hidapi.pro

libusb_driver.file = CAN_Analyser_USB_Driver/libusb_driver.pro
libusb_driver.depends = hidapi

R_Visualizer.file = R_Visualizer/R_Visualizer.pro
R_Visualizer.depends = libusb_driver
