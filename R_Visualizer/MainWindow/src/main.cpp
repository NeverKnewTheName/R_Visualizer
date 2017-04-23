#include "mainwindow.h"
#include <QApplication>

#include <QDebug>

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "Msg.h"
#include "TimestampedMsg.h"

/* #include "msgstorage.h" */

/* #include "devicehandler.h" */

#include "UserRoleManager.h"

#include "IMessageConfig.h"
#include "MessageConfig.h"
#include "IMsgIDMappingManager.h"
#include "MsgIDMappingManager.h"
#include "IMsgIDMapping.h"
#include "MsgIDMapping.h"
#include "IMsgIDMappingStore.h"
#include "MsgIDMappingStore.h"
#include "IMsgIDMappingModel.h"
#include "MsgIDMappingModel.h"
#include "MsgIDMappingWidget.h"
#include "IMsgCodeMappingManager.h"
#include "MsgCodeMappingManager.h"
#include "IMsgCodeMapping.h"
#include "MsgCodeMapping.h"
#include "IMsgCodeMappingStore.h"
#include "MsgCodeMappingStore.h"
#include "IMsgCodeMappingModel.h"
#include "MsgCodeMappingModel.h"
#include "MsgCodeMappingWidget.h"
#include "IMsgDataMappingManager.h"
#include "MsgDataMappingManager.h"
#include "IMsgDataMapping.h"
#include "MsgDataMapping.h"
#include "IMsgDataMappingStore.h"
#include "MsgDataMappingStore.h"
#include "IMsgDataMappingModel.h"
#include "MsgDataMappingModel.h"
#include "MsgDataMappingWidget.h"
#include "MessageConfigWidget.h"

/* #include "IMessageFilter.h" */
/* #include "MessageFilter.h" */
/* #include "MessageFilterWidget.h" */
/* #include "IFilter.h" */
/* #include "IMsgFilter.h" */
/* #include "ITimestampedMsgFilter.h" */
/* #include "MsgIDFilter.h" */
/* #include "IMsgIDFilterStore.h" */
/* #include "MsgIDFilterStore.h" */
/* #include "MsgIDFilterWidget.h" */
/* #include "MsgIDFilterModel.h" */
/* #include "MsgCodeFilter.h" */
/* #include "IMsgCodeFilterStore.h" */
/* #include "MsgCodeFilterStore.h" */
/* #include "MsgCodeFilterWidget.h" */
/* #include "MsgCodeFilterModel.h" */
/* #include "MsgTimestampFilter.h" */
/* #include "MsgTimestampFilterWidget.h" */

/* #include "errorlogentry.h" */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* qRegisterMetaType <CAN_PacketPtr>("CAN_PacketPtr"); */
    /* qRegisterMetaType <Data_PacketPtr>("Data_PacketPtr"); */
    /* qRegisterMetaType <Error_PacketPtr>("Error_PacketPtr"); */
    qRegisterMetaType <MsgIDType>("MsgIDType");
    qRegisterMetaType <MsgCodeType>("MsgCodeType");
    qRegisterMetaType <MsgDataByteType>("MsgDataByteType");
    qRegisterMetaType <MsgDataType>("MsgDataType");
    qRegisterMetaType <Msg>("Msg");
    qRegisterMetaType <TimestampedMsg>("TimestampedMsg");
    /* qRegisterMetaType <MsgData>("MsgData"); */
    /* qRegisterMetaType <DataByteVect>("DataByteVect"); */
    /* qRegisterMetaType <ErrorLogEntry>("ErrorLogEntry"); */

    MainWindow w;
    /* DeviceHandler *interfaceHandler = new DeviceHandler(); */
    /* TimestampedMsgStorage timestampedMsgStorage; */

    IMsgIDMappingStore *msgIDMappingStore = new MsgIDMappingStore();
    IMsgIDMappingManager *msgIDMappingManager = new MsgIDMappingManager(
            msgIDMappingStore
            );
    MsgIDMappingModel *msgIDMappingModel = new MsgIDMappingModel(
            msgIDMappingStore
            );

    IMsgCodeMappingStore *msgCodeMappingStore = new MsgCodeMappingStore();
    IMsgCodeMappingManager *msgCodeMappingManager = new MsgCodeMappingManager(
            msgCodeMappingStore
            );
    MsgCodeMappingModel *msgCodeMappingModel = new MsgCodeMappingModel(
            msgCodeMappingStore
            );

    IMsgDataMappingStore *msgDataMappingStore = new MsgDataMappingStore();
    IMsgDataMappingManager *msgDataMappingManager = new MsgDataMappingManager(
            msgDataMappingStore
            );
    MsgDataMappingModel *msgDataMappingModel = new MsgDataMappingModel(
            msgDataMappingStore
            );


    IMessageConfig *messageConfig = new MessageConfig(
            msgIDMappingManager,
            msgCodeMappingManager,
            msgDataMappingManager,
            &a
            );
    MessageConfigWidget *messageConfigWidget = new MessageConfigWidget(
            messageConfig
            );

    //Note: do not set messageConfigWidget as parent, because the actual parent
    //will be the vertical layout of the messageConfigWidget...
    MsgIDMappingWidget *msgIDMappingWidget = new MsgIDMappingWidget(
            msgIDMappingModel
            /* messageConfigWidget */
            );
    //Note: do not set messageConfigWidget as parent, because the actual parent
    //will be the vertical layout of the messageConfigWidget...
    MsgCodeMappingWidget *msgCodeMappingWidget = new MsgCodeMappingWidget(
            msgCodeMappingModel
            /* messageConfigWidget */
            );
    //Note: do not set messageConfigWidget as parent, because the actual parent
    //will be the vertical layout of the messageConfigWidget...
    MsgDataMappingWidget *msgDataMappingWidget = new MsgDataMappingWidget(
            msgDataMappingModel
            /* messageConfigWidget */
            );


    messageConfigWidget->appendMappingManagerWidget(msgIDMappingWidget);
    messageConfigWidget->appendMappingManagerWidget(msgCodeMappingWidget);
    messageConfigWidget->appendMappingManagerWidget(msgDataMappingWidget);

    w.appendTabMenuWidget(messageConfigWidget, "Message Configuration");
    /* messageConfigWidget->appendMappingWidget(); */

    /* MessageFilter *messageFilter = new MessageFilter(&a); */
    /* MessageFilterWidget *messageFilterWidget = new MessageFilterWidget(&w); */
    /* IMsgIDFilterStore *msgIDFilterStore = new MsgIDFilterStore(); */
    /* MsgIDFilter *msgIDFilter = new MsgIDFilter( */
    /*         msgIDFilterStore, */
    /*         messageFilter */
    /*         ); */

    /* messageFilter->addFilter(msgIDFilter); */
    /* MsgIDFilterWidget *msgIDFilterWidget = new MsgIDFilterWidget( */
    /*         messageFilterWidget */
    /*         ); */
    /* MsgIDFilterModel *msgIDFilterModel = new MsgIDFilterModel( */
    /*         msgIDFilterStore, */
    /*         msgIDFilterWidget */
    /*         ); */
    /* messageFilterWidget->addFilterWidget(msgIDFilterWidget); */


    //MessageStream *messageStreamWidget = new MessageStream(
    //        messageConfig,
    //        messageFilter,
    //        timestampedMsgStorage,
    //        &w
    //        );
    /* SendMessages *sendMessagesWidget; */
    //SendMessages *sndMsgsWidget = new SendMessages(
    //        messageConfig
    //        );
    //sysOvrvWidget = new SystemOverview(
    //        messageConfig
    //        );
    //errLogViewDiag = new ErrorLogView(&w);
    /* SystemOverview *SystemOverviewWidget; */

    /* ErrorLogView *errorLogViewDialog; */
    /* UserRoleMngr userRoleManager; */
    /* DeviceHandler interfaceHandler; */

    //connect(
    //        &interfaceHandler,
    //        &DeviceHandler::sigMsgReceived,
    //        &receivedMsgsStore,
    //        &TimestampedMsgStorage::slt_addMsg,
    //        Qt::QueuedConnection
    //        );
    //connect(
    //        &receivedMsgsStore,
    //        &TimestampedMsgStorage::sgnl_MsgAdded,
    //        sysOvrvWidget,
    //        &SystemOverview::slt_newMessage
    //        );

    w.show();

    return a.exec();
}
