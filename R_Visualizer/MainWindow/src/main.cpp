#include "mainwindow.h"
#include <QApplication>

#include <QObject>
#include <QDebug>

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"
#include "Msg.h"
#include "TimestampedMsg.h"

#include "msgstorage.h"

#include "IInterfaceHandler.h"
#include "CANAnalyserInterfaceHandler.h"

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

#include "IMessageFilter.h"
#include "MessageFilter.h"
#include "MessageFilterWidget.h"
#include "IFilter.h"
#include "IMsgFilter.h"
#include "ITimestampedMsgFilter.h"
#include "MsgIDFilter.h"
#include "IMsgIDFilterStore.h"
#include "MsgIDFilterStore.h"
#include "MsgIDFilterWidget.h"
#include "MsgIDFilterModel.h"
#include "MsgCodeFilter.h"
#include "IMsgCodeFilterStore.h"
#include "MsgCodeFilterStore.h"
#include "MsgCodeFilterWidget.h"
#include "MsgCodeFilterModel.h"
#include "MsgTimespanFilter.h"
#include "MsgTimespanFilterWidget.h"

#include "IMessageStream.h"
#include "MessageStream.h"
#include "MessageStreamWidget.h"
#include "IMsgStreamStore.h"
#include "MsgStreamStore.h"
#include "MsgStreamModel.h"

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
    IInterfaceHandler *interfaceHandler = new CANAnalyserInterfaceHandler(&w);

    IMsgIDMappingStore *msgIDMappingStore = new MsgIDMappingStore();
    IMsgIDMappingManager *msgIDMappingManager = new MsgIDMappingManager(
            msgIDMappingStore
            );
    msgIDMappingStore->setParent(msgIDMappingManager);
    MsgIDMappingModel *msgIDMappingModel = new MsgIDMappingModel(
            msgIDMappingStore
            );

    IMsgCodeMappingStore *msgCodeMappingStore = new MsgCodeMappingStore();
    IMsgCodeMappingManager *msgCodeMappingManager = new MsgCodeMappingManager(
            msgCodeMappingStore
            );
    msgCodeMappingStore->setParent(msgCodeMappingManager);
    MsgCodeMappingModel *msgCodeMappingModel = new MsgCodeMappingModel(
            msgCodeMappingStore
            );

    IMsgDataMappingStore *msgDataMappingStore = new MsgDataMappingStore();
    IMsgDataMappingManager *msgDataMappingManager = new MsgDataMappingManager(
            msgDataMappingStore
            );
    msgDataMappingStore->setParent(msgDataMappingManager);
    MsgDataMappingModel *msgDataMappingModel = new MsgDataMappingModel(
            msgDataMappingStore
            );


    IMessageConfig *messageConfig = new MessageConfig(
            msgIDMappingManager,
            msgCodeMappingManager,
            msgDataMappingManager,
            &a
            );
    
    msgIDMappingManager->setParent(messageConfig);
    msgCodeMappingManager->setParent(messageConfig);
    msgDataMappingManager->setParent(messageConfig);

    MessageConfigWidget *messageConfigWidget = new MessageConfigWidget(
            messageConfig
            );

    //Note: do not set messageConfigWidget as parent, because the actual parent
    //will be the vertical layout of the messageConfigWidget...
    MsgIDMappingWidget *msgIDMappingWidget = new MsgIDMappingWidget(
            msgIDMappingManager,
            msgIDMappingModel
            /* messageConfigWidget */
            );
    //Note: do not set messageConfigWidget as parent, because the actual parent
    //will be the vertical layout of the messageConfigWidget...
    MsgCodeMappingWidget *msgCodeMappingWidget = new MsgCodeMappingWidget(
            msgCodeMappingManager,
            msgCodeMappingModel
            /* messageConfigWidget */
            );
    //Note: do not set messageConfigWidget as parent, because the actual parent
    //will be the vertical layout of the messageConfigWidget...
    MsgDataMappingWidget *msgDataMappingWidget = new MsgDataMappingWidget(
            msgDataMappingManager,
            msgDataMappingModel
            /* messageConfigWidget */
            );


    messageConfigWidget->appendMappingManagerWidget(msgIDMappingWidget);
    messageConfigWidget->appendMappingManagerWidget(msgCodeMappingWidget);
    messageConfigWidget->appendMappingManagerWidget(msgDataMappingWidget);

    w.appendTabMenuWidget(messageConfigWidget, "Message Configuration");
    /* messageConfigWidget->appendMappingWidget(); */

    MessageFilter *messageFilter = new MessageFilter(&a);
    MessageFilterWidget *messageFilterWidget =
        new MessageFilterWidget();


    IMsgIDFilterStore *msgIDFilterStore = new MsgIDFilterStore();
    MsgIDFilter *msgIDFilter = new MsgIDFilter(
            msgIDFilterStore
            );

    msgIDFilterStore->setParent(msgIDFilter);

    messageFilter->addFilter(msgIDFilter);
    MsgIDFilterModel *msgIDFilterModel = new MsgIDFilterModel(
            msgIDFilterStore
            );
    MsgIDFilterWidget *msgIDFilterWidget = new MsgIDFilterWidget(
            msgIDFilter,
            msgIDFilterModel
            );

    IMsgCodeFilterStore *msgCodeFilterStore = new MsgCodeFilterStore();
    MsgCodeFilter *msgCodeFilter = new MsgCodeFilter(
            msgCodeFilterStore
            );

    msgCodeFilterStore->setParent(msgCodeFilter);

    messageFilter->addFilter(msgCodeFilter);
    MsgCodeFilterModel *msgCodeFilterModel = new MsgCodeFilterModel(
            msgCodeFilterStore
            );
    MsgCodeFilterWidget *msgCodeFilterWidget = new MsgCodeFilterWidget(
            msgCodeFilter,
            msgCodeFilterModel
            );

    MsgTimespanFilter *msgTimestampFilter = new MsgTimespanFilter();

    MsgTimespanFilterWidget *msgTimestampFilterWidget =
        new MsgTimespanFilterWidget(msgTimestampFilter);

    messageFilterWidget->addFilterWidget(msgIDFilterWidget);
    messageFilterWidget->addFilterWidget(msgCodeFilterWidget);
    messageFilterWidget->addFilterWidget(msgTimestampFilterWidget);

    w.appendTabMenuWidget(messageFilterWidget, "Message Filter");


    TimestampedMsgStorage timestampedMsgStorage;

    QObject::connect(
            &w,
            &MainWindow::sgnl_AddTestMessage,
            interfaceHandler,
            &IInterfaceHandler::slt_SendMessage
            );

    QObject::connect(
            interfaceHandler,
            &IInterfaceHandler::sgnl_MessageReceived,
            &timestampedMsgStorage,
            &TimestampedMsgStorage::slt_addMsg
            );

    IMsgStreamStore *msgStreamStore = new MsgStreamStore(
            50
            );
    MessageStream *messageStream = new MessageStream(
            messageConfig,
            messageFilter,
            msgStreamStore,
            timestampedMsgStorage,
            &w
            );

    msgStreamStore->setParent(messageStream);

    MsgStreamModel *msgStreamModel = new MsgStreamModel(msgStreamStore);

    MessageStreamWidget *messageStreamWidget = new MessageStreamWidget(
            messageStream,
            msgStreamModel
            );

    w.setMessageStreamWidget(
            messageStreamWidget
            );

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
