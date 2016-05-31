#############################################################################
# Makefile for building: R_Visualizer_Build
# Generated by qmake (3.0) (Qt 5.6.0)
# Project:  R_Visualizer_Build.pro
# Template: subdirs
# Command: C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\qmake.exe -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile R_Visualizer_Build.pro
#############################################################################

MAKEFILE      = Makefile

first: make_first
QMAKE         = C:\Qt\Qt5.6.0\5.6\mingw49_32\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = copy /y
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = copy /y
INSTALL_PROGRAM = copy /y
INSTALL_DIR   = xcopy /s /q /y /i
DEL_FILE      = del
SYMLINK       = $(QMAKE) -install ln -f -s
DEL_DIR       = rmdir
MOVE          = move
SUBTARGETS    =  \
		sub-R_Visualizer-R_Visualizer-pro \
		sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro \
		sub-CAN_Analyser_USB_Driver-libusb_driver-pro


sub-R_Visualizer-R_Visualizer-pro-qmake_all: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-qmake_all FORCE
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile
	cd R_Visualizer\ && $(MAKE) -f Makefile qmake_all
sub-R_Visualizer-R_Visualizer-pro: sub-CAN_Analyser_USB_Driver-libusb_driver-pro FORCE
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile
sub-R_Visualizer-R_Visualizer-pro-make_first: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-make_first FORCE
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile 
sub-R_Visualizer-R_Visualizer-pro-all: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-all FORCE
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile all
sub-R_Visualizer-R_Visualizer-pro-clean: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-clean FORCE
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile clean
sub-R_Visualizer-R_Visualizer-pro-distclean: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-distclean FORCE
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile distclean
sub-R_Visualizer-R_Visualizer-pro-install_subtargets: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-install_subtargets FORCE
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile install
sub-R_Visualizer-R_Visualizer-pro-uninstall_subtargets: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-uninstall_subtargets FORCE
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile uninstall
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-qmake_all:  FORCE
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile
	cd CAN_Analyser_USB_Driver\hidapi\ && $(MAKE) -f Makefile qmake_all
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro: FORCE
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-make_first: FORCE
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile 
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-all: FORCE
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile all
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-clean: FORCE
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile clean
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-distclean: FORCE
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile distclean
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-install_subtargets: FORCE
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile install
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-uninstall_subtargets: FORCE
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile uninstall
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-qmake_all: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-qmake_all FORCE
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver
	cd CAN_Analyser_USB_Driver\ && $(MAKE) -f Makefile.libusb_driver qmake_all
sub-CAN_Analyser_USB_Driver-libusb_driver-pro: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro FORCE
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-make_first: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-make_first FORCE
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver 
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-all: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-all FORCE
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver all
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-clean: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-clean FORCE
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver clean
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-distclean: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-distclean FORCE
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver distclean
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-install_subtargets: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-install_subtargets FORCE
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver install
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-uninstall_subtargets: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-uninstall_subtargets FORCE
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver uninstall

Makefile: R_Visualizer_Build.pro C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/win32-g++/qmake.conf C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/spec_pre.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/qdevice.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/device_config.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/common/angle.conf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/qconfig.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dcore.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dcore_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dinput.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dinput_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dlogic.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dlogic_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquick.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquick_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquickinput.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquickinput_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquickrender.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquickrender_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3drender.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3drender_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axbase.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axbase_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axcontainer.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axcontainer_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axserver.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axserver_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_bluetooth.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_bluetooth_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_bootstrap_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_clucene_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_concurrent.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_concurrent_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_core.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_core_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_dbus.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_dbus_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_designer.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_designer_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_designercomponents_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_gui.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_gui_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_help.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_help_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_labscontrols_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_labstemplates_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_location.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_location_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_multimedia.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_multimedia_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_multimediawidgets.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_network.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_network_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_nfc.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_nfc_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_opengl.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_opengl_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_openglextensions.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_openglextensions_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_platformsupport_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_positioning.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_positioning_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_printsupport.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_printsupport_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qml.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qml_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qmltest.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qmltest_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quick.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quick_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quickparticles_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quickwidgets.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_script.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_script_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_scripttools.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_scripttools_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_sensors.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_sensors_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_serialbus.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_serialbus_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_serialport.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_serialport_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_sql.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_sql_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_svg.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_svg_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_testlib.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_testlib_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_uiplugin.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_uitools.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_uitools_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_webchannel.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_webchannel_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_websockets.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_websockets_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_widgets.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_widgets_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_winextras.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_winextras_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_xml.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_xml_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_xmlpatterns.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/qt_functions.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/qt_config.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/win32/qt_config.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/win32-g++/qmake.conf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/spec_post.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/exclusive_builds.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/default_pre.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/win32/default_pre.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/resolve_config.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/exclusive_builds_post.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/default_post.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/qml_debug.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/win32/rtti.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/precompile_header.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/warn_on.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/win32/windows.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/testcase_targets.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/exceptions.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/yacc.prf \
		C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/lex.prf \
		R_Visualizer_Build.pro
	$(QMAKE) -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile R_Visualizer_Build.pro
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/spec_pre.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/qdevice.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/device_config.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/common/angle.conf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/qconfig.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dcore.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dcore_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dinput.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dinput_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dlogic.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dlogic_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquick.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquick_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquickinput.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquickinput_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquickrender.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3dquickrender_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3drender.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_3drender_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axbase.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axbase_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axcontainer.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axcontainer_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axserver.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_axserver_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_bluetooth.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_bluetooth_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_bootstrap_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_clucene_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_concurrent.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_concurrent_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_core.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_core_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_dbus.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_dbus_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_designer.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_designer_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_designercomponents_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_gui.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_gui_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_help.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_help_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_labscontrols_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_labstemplates_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_location.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_location_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_multimedia.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_multimedia_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_multimediawidgets.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_network.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_network_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_nfc.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_nfc_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_opengl.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_opengl_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_openglextensions.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_openglextensions_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_platformsupport_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_positioning.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_positioning_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_printsupport.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_printsupport_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qml.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qml_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qmldevtools_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qmltest.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qmltest_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quick.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quick_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quickparticles_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quickwidgets.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_quickwidgets_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_script.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_script_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_scripttools.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_scripttools_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_sensors.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_sensors_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_serialbus.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_serialbus_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_serialport.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_serialport_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_sql.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_sql_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_svg.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_svg_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_testlib.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_testlib_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_uiplugin.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_uitools.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_uitools_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_webchannel.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_webchannel_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_websockets.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_websockets_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_widgets.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_widgets_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_winextras.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_winextras_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_xml.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_xml_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_xmlpatterns.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/qt_functions.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/qt_config.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/win32/qt_config.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/win32-g++/qmake.conf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/spec_post.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/exclusive_builds.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/default_pre.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/win32/default_pre.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/resolve_config.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/exclusive_builds_post.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/default_post.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/qml_debug.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/win32/rtti.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/precompile_header.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/warn_on.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/win32/windows.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/testcase_targets.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/exceptions.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/yacc.prf:
C:/Qt/Qt5.6.0/5.6/mingw49_32/mkspecs/features/lex.prf:
R_Visualizer_Build.pro:
qmake: FORCE
	@$(QMAKE) -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile R_Visualizer_Build.pro

qmake_all: sub-R_Visualizer-R_Visualizer-pro-qmake_all sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-qmake_all sub-CAN_Analyser_USB_Driver-libusb_driver-pro-qmake_all FORCE

make_first: sub-R_Visualizer-R_Visualizer-pro-make_first sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-make_first sub-CAN_Analyser_USB_Driver-libusb_driver-pro-make_first  FORCE
all: sub-R_Visualizer-R_Visualizer-pro-all sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-all sub-CAN_Analyser_USB_Driver-libusb_driver-pro-all  FORCE
clean: sub-R_Visualizer-R_Visualizer-pro-clean sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-clean sub-CAN_Analyser_USB_Driver-libusb_driver-pro-clean  FORCE
distclean: sub-R_Visualizer-R_Visualizer-pro-distclean sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-distclean sub-CAN_Analyser_USB_Driver-libusb_driver-pro-distclean  FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-R_Visualizer-R_Visualizer-pro-install_subtargets sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-install_subtargets sub-CAN_Analyser_USB_Driver-libusb_driver-pro-install_subtargets FORCE
uninstall_subtargets: sub-R_Visualizer-R_Visualizer-pro-uninstall_subtargets sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-uninstall_subtargets sub-CAN_Analyser_USB_Driver-libusb_driver-pro-uninstall_subtargets FORCE

sub-R_Visualizer-R_Visualizer-pro-debug: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-debug
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile debug
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-debug:
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile debug
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-debug: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-debug
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver debug
debug: sub-R_Visualizer-R_Visualizer-pro-debug sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-debug sub-CAN_Analyser_USB_Driver-libusb_driver-pro-debug

sub-R_Visualizer-R_Visualizer-pro-release: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-release
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile release
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-release:
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile release
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-release: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-release
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver release
release: sub-R_Visualizer-R_Visualizer-pro-release sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-release sub-CAN_Analyser_USB_Driver-libusb_driver-pro-release

sub-R_Visualizer-R_Visualizer-pro-check: sub-CAN_Analyser_USB_Driver-libusb_driver-pro-check
	@if not exist R_Visualizer\ mkdir R_Visualizer\ & if not exist R_Visualizer\ exit 1
	cd R_Visualizer\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\R_Visualizer\R_Visualizer.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile check
sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-check:
	@if not exist CAN_Analyser_USB_Driver\hidapi\ mkdir CAN_Analyser_USB_Driver\hidapi\ & if not exist CAN_Analyser_USB_Driver\hidapi\ exit 1
	cd CAN_Analyser_USB_Driver\hidapi\ && ( if not exist Makefile $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\hidapi\hidapi.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile ) && $(MAKE) -f Makefile check
sub-CAN_Analyser_USB_Driver-libusb_driver-pro-check: sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-check
	@if not exist CAN_Analyser_USB_Driver\ mkdir CAN_Analyser_USB_Driver\ & if not exist CAN_Analyser_USB_Driver\ exit 1
	cd CAN_Analyser_USB_Driver\ && ( if not exist Makefile.libusb_driver $(QMAKE) C:\Users\Christian\Documents\OHM\MAPR\Projekt\QTWrkSpc\R_Visualizer_Build\CAN_Analyser_USB_Driver\libusb_driver.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug" -o Makefile.libusb_driver ) && $(MAKE) -f Makefile.libusb_driver check
check: sub-R_Visualizer-R_Visualizer-pro-check sub-CAN_Analyser_USB_Driver-hidapi-hidapi-pro-check sub-CAN_Analyser_USB_Driver-libusb_driver-pro-check
install:install_subtargets  FORCE

uninstall: uninstall_subtargets FORCE

FORCE:

