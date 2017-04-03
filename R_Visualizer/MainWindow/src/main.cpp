/* #include "mainwindow.h" */
#include <QApplication>

/* #include "can_packet.h" */
/* #include "Msg.h" */
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
#include "MsgIDMappingModel.h"
#include "IMsgIDMappingStore.h"
#include "MsgIDMappingStore.h"
#include "MsgIDMappingWidget.h"
#include "IMsgCodeMappingStore.h"
#include "MsgCodeMappingStore.h"
#include "MsgCodeMappingWidget.h"

#include "MessageConfigWidget.h"

#include "Msg.h"
#include "TimestampedMsg.h"
#include "errorlogentry.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* qRegisterMetaType <CAN_PacketPtr>("CAN_PacketPtr"); */
    /* qRegisterMetaType <Data_PacketPtr>("Data_PacketPtr"); */
    /* qRegisterMetaType <Error_PacketPtr>("Error_PacketPtr"); */
    qRegisterMetaType <Msg>("Msg");
    qRegisterMetaType <TimestampedMsg>("TimestampedMsg");
    /* qRegisterMetaType <MsgData>("MsgData"); */
    /* qRegisterMetaType <DataByteVect>("DataByteVect"); */
    qRegisterMetaType <ErrorLogEntry>("ErrorLogEntry");

    /* MainWindow w; */

    IMsgIDMappingStore *msgIDMappingStore = new MsgIDMappingStore();
    IMsgIDMapping *msgIDMapping = new MsgIDMapping(msgIDMappingStore);
    IMsgIDMappingModel *msgIDMappingModel = new MsgIDMappingModel(
            msgIDMappingStore
            );
    IMsgCodeMappingStore *msgCodeMappingStore = new MsgCodeMappingStore();
    IMsgCodeMapping *msgCodeMapping = new MsgCodeMapping(msgCodeMappingStore);
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
    MsgIDMappingWidget *msgIDMappingWidget = new MsgIDMappingWidget(
            msgIDMappingModel,
            messageConfigWidget
            );
    messageConfigWidget->appendMappingWidget(msgIDMappingWidget);
    /* messageConfigWidget->appendMappingWidget(); */

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
