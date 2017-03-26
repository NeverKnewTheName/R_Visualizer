/* #include "mainwindow.h" */
#include <QApplication>

/* #include "can_packet.h" */
/* #include "msg.h" */
/* #include "errorlogentry.h" */

// // // DEBUG // // //
#include <QDebug>
#include <QElapsedTimer>
#include <QThread>
/* #include "msgparser.h" */
/* #include "msgdatawidget.h" */
/* #include "datastorage.h" */
// // // DEBUG // // //

#include "IMsgIDMapping.h"
#include "MsgIDMapping.h"
#include "IMsgCodeMapping.h"
#include "MsgCodeMapping.h"
#include "IMsgDataMapping.h"
#include "MsgDataMapping.h"
#include "IMessageConfig.h"
#include "MessageConfig.h"
#include "IMsgIDMappingModel.h"
#include "IMsgIDMappingStore.h"

#include "MessageConfigWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* qRegisterMetaType <CAN_PacketPtr>("CAN_PacketPtr"); */
    /* qRegisterMetaType <Data_PacketPtr>("Data_PacketPtr"); */
    /* qRegisterMetaType <Error_PacketPtr>("Error_PacketPtr"); */
    /* qRegisterMetaType <Msg>("Msg"); */
    /* qRegisterMetaType <MsgData>("MsgData"); */
    /* qRegisterMetaType <DataByteVect>("DataByteVect"); */
    /* qRegisterMetaType <ErrorLogEntry>("ErrorLogEntry"); */

    /* MainWindow w; */

    IMsgIDMapping *msgIDMapping = new MsgIDMapping();
    IMsgCodeMapping *msgCodeMapping = new MsgCodeMapping();
    IMsgDataMapping *msgDataMapping = new MsgDataMapping();


    IMessageConfig *messageConfig = new MessageConfig(
            msgIDMapping,
            msgCodeMapping,
            msgDataMapping,
            &a
            );
    MessageConfigWidget *messageConfigWidget = new MessageConfigWidget(
            messageConfig
            );
    IMsgIDMappingStore *msgIDMappingStore = new MsgIDMappingStore();
    IMsgIDMappingModel *msgIDMappingModel = new MsgIDMappingModel(
            msgIDMappingStore
            );
    MsgIDMappingWidget msgIDMappingWidget = new MsgIDMappingWidget(
            msgIDMappingModel,
            messageConfigWidget
            );
    messageConfigWidget->appendMappingWidget();

    /* MessageFilter *messageFilterWidget = new MessageFilter(); */
    /* MessageStream *messageStreamWidget; */
    /* SendMessages *sendMessagesWidget; */
    /* SystemOverview *SystemOverviewWidget; */

    /* ErrorLogView *errorLogViewDialog; */
    /* UserRoleMngr userRoleManager; */
    /* DeviceHandler interfaceHandler; */


    /* w.show(); */

    return a.exec();
}
