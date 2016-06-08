#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "msgdelegate.h"
#include "msgproxymodel.h"
#include "msgfilterproxymodel.h"
#include "MessageConfig/filteridstore.h"

#include "csvmsgpackethandler.h"

#include "devicehandler.h"

#include <QFile>
#include <QFileDialog>

#include <QDateTime>
#include <QMessageBox>
#include <QScrollBar>

#define __DEBUG__

#ifdef __DEBUG__
#include <QDebug>
#endif //__DEBUG__

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->currentFileName = "";

    /*
     * INIT MODELS
     */

    msgTypeModel = new MsgTypeModel(this);
    //connect(msgTypeModel, &MsgTypeModel::internalModelChanged, ui->msgTableView, &QTableView::reset);
    connect(msgTypeModel, &MsgTypeModel::internalModelChanged, ui->msgTableView, &QTableView::resizeRowsToContents);

    idModel = new IDModel(this);
    //connect(idModel, &IDModel::internalModelChanged, ui->msgTableView, &QTableView::reset);
    connect(idModel, &IDModel::internalModelChanged, ui->msgTableView, &QTableView::resizeRowsToContents);

    this->sysOvrvwWidget = new SystemOverview(this);
    ui->tabWidget->addTab(this->sysOvrvwWidget, QString("System Overview"));

    this->sndMsgsWidget = new SendMessages(this->idModel, this->msgTypeModel, this);
    ui->tabWidget->addTab(this->sndMsgsWidget, QString("Send Messages"));

    this->msgConfigWidget = new MessageConfig(this->idModel, this->msgTypeModel, this);
    ui->tabWidget->addTab(this->msgConfigWidget, QString("Message Configuration"));

    connect(this->msgConfigWidget, &MessageConfig::sgnlIdAddFinished, this, &MainWindow::idAddFinished);
    connect(this->msgConfigWidget, &MessageConfig::sgnlMsgTypeAddFinished, this, &MainWindow::msgTypeAddFinished);


    this->initMsgsTableView();
    //    this->msgModel->setIDModel(this->idModel);
    //    this->msgModel->setMsgTypeModel(this->msgTypeModel);
    //this->initVisualizerGraphicsView();

    this->userRoleMngr = new UserRoleMngr(this);
    ui->actionSwitch_User_Role->setIcon(QIcon(":/GUI/Icons/Icons/UserAdmin-32.png"));
    ui->actionSwitch_User_Role->setToolTip(QString("Switch to Admin Role"));
    ui->actionSwitch_User_Role->setText(QString("Switch to Admin Role"));
    connect(this, &MainWindow::switchUserRoles, this->userRoleMngr, &UserRoleMngr::switchRoles);
    connect(this, &MainWindow::switchUserRoles, this->sysOvrvwWidget, &SystemOverview::applyRole);
    connect(this, &MainWindow::switchUserRoles, this->sndMsgsWidget, &SendMessages::applyRole);
    connect(this, &MainWindow::switchUserRoles, this->msgConfigWidget, &MessageConfig::applyRole);
    connect(this, &MainWindow::switchUserRoles, this, &MainWindow::applyRole);

    emit switchUserRoles(UserRoleMngr::NormalUserRole);

    m_deviceHandler = new DeviceHandler();
    connect(this->sndMsgsWidget, &SendMessages::sigSendCANPacket, m_deviceHandler, &DeviceHandler::sltSendPacket/*, Qt::QueuedConnection*/);
    connect(m_deviceHandler, &DeviceHandler::sigPacketReceived, this->msgModel, &MsgModel::messageReceived, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_deviceHandler;
}


void MainWindow::on_actionNew_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__
    //TESTING ONLY
    static int cntr = 0;
    ++cntr;
    MsgDataT msgData = { 0x2, cntr, 0x0,cntr*2,0x0,cntr,0x4*cntr,cntr};
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xF0,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xF0,msgData));
    msgData = { 0x3, cntr, 0x0,cntr*2,0x0,cntr,0x4*cntr,cntr};
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xF0,msgData));
    msgModel->addMsg(new Msg(QDateTime::fromMSecsSinceEpoch(cntr),0xFF,msgData));
}

void MainWindow::on_actionOpen_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    QString openLoc = QFileDialog::getOpenFileName(this, QString("Open"), QString(), "JSON File (*.json)");
    qDebug() << openLoc;
    currentFileName = openLoc;
    QFile jsonOpenFile(openLoc);
    if(!jsonOpenFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error opening: " << jsonOpenFile.fileName();
    }
    //ToDO
    // read file content
    msgModel->parseFromJSON(jsonOpenFile.readAll()); //ToDO check for error (-1)
    // parse file
    // populate ui
    // close file
    jsonOpenFile.close();
}

void MainWindow::on_actionSave_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

    if(currentFileName.isEmpty())
    {
        QString saveLoc = QFileDialog::getSaveFileName(this, QString("Save as"), QString(), "JSON File (*.json)");
        qDebug() << saveLoc;
        currentFileName = saveLoc;
    }
    QFile jsonSaveFile(currentFileName);
    if(!jsonSaveFile.open(QIODevice::WriteOnly)) {
        qDebug() << "error open file to save: " << jsonSaveFile.fileName();
    }
    //ToDO
    // extract ui content
    // parse content to file format
    // write to file
    jsonSaveFile.write(this->msgModel->parseToJSON()); //ToDO check for error (-1)
    // close file
    jsonSaveFile.flush(); //always flush after write!
    jsonSaveFile.close();
}

void MainWindow::on_actionConnect_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__
    if (m_deviceHandler->devices().isEmpty())
    {
        QMessageBox::information(this, tr("Kein Gerät gefunden"), tr("Bitte schließen Sie ein Gerät an!"), QMessageBox::Cancel);
        return;
    }

    HID_Device device = m_deviceHandler->devices()[0];
    if (m_deviceHandler->connectTo(device))
    {
        qDebug() << "COnnected";
        m_deviceHandler->sltStartCapture();
        //m_state = Connected;
        //updateActionStates();
        //ui->statusBar->showMessage(tr("Eine Verbindung zu dem Gerät %1 wurde hergestellt. Die Analyse kann nun gestartet werden.").arg(device.product));
    }
    else
    {
        qDebug() << "Connection failed";
        //ui->statusBar->showMessage(tr("Eine Verbindung zu dem Gerät %1 konnte nicht hergestellt werden. Das Gerät ist nicht betriebsbereit.").arg(device.product));
    }
}

void MainWindow::on_actionStart_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

}

void MainWindow::on_actionStop_triggered()
{
#ifdef __DEBUG__
    qDebug() << __PRETTY_FUNCTION__ << " - Triggered";
#endif //__DEBUG__

}

#define FILTER_PROXY_VIEW
void MainWindow::initMsgsTableView()
{
    QScrollBar *vertScrollBar = ui->msgTableView->verticalScrollBar();
    this->msgModel = new MsgModel(this);
//    connect(MsgModel, &MsgModel::rowAppended, ui->msgTableView, &QTableView::resizeRowToContents);

    FilterIDStore *filterIDModel = this->msgConfigWidget->getFilterIDModel();
    FilterCodeStore *filterCodeModel = this->msgConfigWidget->getFilterCodeModel();
    FilterTimestampStore *filterTimestampModel = this->msgConfigWidget->getFilterTimestampModel();
    ui->msgTableView->setFilterIDModel(filterIDModel);
    ui->msgTableView->setFilterCodeModel(filterCodeModel);
    ui->msgTableView->setFilterTimestampModel(filterTimestampModel);

    connect(this->msgConfigWidget, &MessageConfig::filterIDstateChange, ui->msgTableView, &MsgTableView::changeIDFilterEnabled);
    connect(this->msgConfigWidget, &MessageConfig::filterCodestateChange, ui->msgTableView, &MsgTableView::changeCodeFilterEnabled);
    connect(this->msgConfigWidget, &MessageConfig::filterTimestampFromStateChange, ui->msgTableView, &MsgTableView::changeTimestampFromFilterEnabled);
    connect(this->msgConfigWidget, &MessageConfig::filterTimestampToStateChange, ui->msgTableView, &MsgTableView::changeTimestampToFilterEnabled);

    connect(filterIDModel, &FilterIDStore::internalModelChanged, ui->msgTableView, &MsgTableView::filterChanged);
    connect(filterCodeModel, &FilterCodeStore::internalModelChanged, ui->msgTableView, &MsgTableView::filterChanged);
    connect(filterTimestampModel, &FilterTimestampStore::internalModelChanged, ui->msgTableView, &MsgTableView::filterChanged);

    //connect(this, &MainWindow::queryFetchRow, ui->msgTableView, &MsgTableView::scrollFetchRows);
    //connect(ui->msgTableView, &MsgTableView::scrollRowsFetched, this, &MainWindow::updateSlider);
    //connect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);

    connect(ui->msgTableView, &MsgTableView::invisibleRows, this, &MainWindow::scrollToGetMoreContent);
//    MsgFilterProxyModel *msgFilterProxy = new MsgFilterProxyModel(filterIDModel, filterCodeModel, this);
//    connect(this->msgConfigWidget, &MessageConfig::filterIDstateChange, msgFilterProxy, &MsgFilterProxyModel::changeIDFilterEnabled);
//    connect(filterIDModel, &FilterIDStore::rowAdded, msgFilterProxy, &MsgFilterProxyModel::invalidate);
//    connect(this->msgConfigWidget, &MessageConfig::filterCodestateChange, msgFilterProxy, &MsgFilterProxyModel::changeCodeFilterEnabled);
//    connect(filterCodeModel, &FilterCodeStore::rowAdded, msgFilterProxy, &MsgFilterProxyModel::invalidate);

//    msgProxyModel = new MsgProxyModel(this);
//#ifdef FILTER_PROXY_VIEW
//    msgFilterProxy->setSourceModel(this->msgModel);
////    msgProxyModel->setSourceModel(msgFilterProxy);
////    ui->msgTableView->setModel(msgProxyModel);
//#else
//    msgProxyModel->setSourceModel(this->msgModel);
//    msgFilterProxy->setSourceModel(msgProxyModel);
////    ui->msgTableView->setModel(msgFilterProxy);
//#endif
    connect(this->msgModel, &MsgModel::rowAppended, /*msgFilterProxy, &MsgFilterProxyModel::slt_RowsAdded);
    connect(msgFilterProxy, &MsgFilterProxyModel::sgnl_RowsAdded,*/ ui->msgTableView, &MsgTableView::rowAdded);
    //connect(this->msgModel, &MsgModel::rowsRemoved, ui->msgTableView, &MsgTableView::customRowCountChanged);
    ui->msgTableView->setModel(this->msgModel);
//    connect(this->msgModel, &MsgModel::rowAppended, msgProxyModel, &MsgProxyModel::newEntryAppendedInSourceModel);
//    connect(this, &MainWindow::changedDataAcquisitionMode, msgProxyModel, &MsgProxyModel::continuousChange);
//    connect(this, &MainWindow::queryFetchRow, msgProxyModel, &MsgProxyModel::fetchRowsFromSource);
//    connect(msgProxyModel, &MsgProxyModel::rowFetched, this, &MainWindow::updateSlider);
//    connect(msgFilterProxy, &MsgFilterProxyModel::dataChanged, msgProxyModel, &MsgProxyModel::resetInternalData);

    ui->msgTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->msgTableView->verticalHeader()->hide();
    ui->msgTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->msgTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //TOO HEAVY ON PERFORMANCE...NEEDS A WORKAROUND
    //ui->msgTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->msgTableView->setItemDelegate( new MsgDelegate(this->msgTypeModel, this->idModel, ui->msgTableView));

    //connect(vertScrollBar, &QScrollBar::sliderMoved, this, &MainWindow::scrollBarMsgTableViewMoved);

    // scroll to the bottom as soon as a new row is inserted by
    // since the rowsInserted signal might be fired before the view actually inserted the new rows,
    // set up a timer to instantly fire an event which triggers the scrollToBottom
    // with this approach it is guaranteed that all events in the meantime are carried out and thus the row is already inserted
    //connect(msgModel, &MsgModel::rowsInserted, this, &MainWindow::autoScroll);
//    connect(msgProxyModel, &MsgProxyModel::rowAppended, this, &MainWindow::autoScroll);
}


void MainWindow::idAddFinished(const int id, const QString name, const QColor color)
{
    idModel->add(id, new IDRep( name, color));
}


void MainWindow::msgTypeAddFinished(const int code, const QString codeName, const QString messageFormat, const QColor color)
{
    msgTypeModel->add(code, new MsgTypeRep(code, codeName, messageFormat, color));
}

void MainWindow::applyRole(UserRoleMngr::UserRole roleToSwitchTo)
{
    if(roleToSwitchTo == UserRoleMngr::NormalUserRole)
    {


    }
    else if(roleToSwitchTo == UserRoleMngr::AdminRole)
    {


    }
}


void MainWindow::on_actionSwitch_User_Role_triggered()
{
    UserRoleMngr::UserRole role = this->userRoleMngr->getCurrentRole();
    if( role == UserRoleMngr::NormalUserRole )
    {
        role = UserRoleMngr::AdminRole;
        ui->actionSwitch_User_Role->setIcon(QIcon(":/GUI/Icons/Icons/UserNormal-32.png"));
        ui->actionSwitch_User_Role->setToolTip(QString("Switch to User Role"));
        ui->actionSwitch_User_Role->setText(QString("Switch to User Role"));
    }
    else if( role == UserRoleMngr::AdminRole )
    {
        role = UserRoleMngr::NormalUserRole;
        ui->actionSwitch_User_Role->setIcon(QIcon(":/GUI/Icons/Icons/UserAdmin-32.png"));
        ui->actionSwitch_User_Role->setToolTip(QString("Switch to Admin Role"));
        ui->actionSwitch_User_Role->setText(QString("Switch to Admin Role"));
    }

    emit this->switchUserRoles(role);
}

void MainWindow::scrollBarMsgTableViewMoved(int position)
{
    static bool scrollToBottomConnected = false;
    QScrollBar *vertScrollBar = ui->msgTableView->verticalScrollBar();
    qDebug() << "Scrollbar moved to position:" << position;

    if((position >= (vertScrollBar->maximum())) && (!ui->msgTableView->isAtTopEnd()))
    {
        qDebug() << "Scrollbar is at max pos";
        if(!scrollToBottomConnected)
        {
            qDebug() << "ScrollToBottom Connect!";
            //connect(msgModel, &MsgModel::rowsInserted, this, &MainWindow::autoScroll);
            scrollToBottomConnected = true;
            emit changedDataAcquisitionMode(true);
        }
        disconnect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
        ui->msgTableView->scrollFetchRows(+1);
        if(!ui->msgTableView->isAtTopEnd())
            vertScrollBar->setSliderPosition(vertScrollBar->sliderPosition()-2);
        connect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
        qDebug() << "Scrollbar moved to position:" << position;
    }
    else
    {
        if( (position <= (vertScrollBar->minimum())) && (!ui->msgTableView->isAtBottomEnd()) )
        {
            disconnect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
//            emit queryFetchRow(-1);
            qDebug() << "Scrollbar moved to position:" << position;
            ui->msgTableView->scrollFetchRows(-1);
            if(!ui->msgTableView->isAtBottomEnd())
                vertScrollBar->setSliderPosition(vertScrollBar->sliderPosition()+2);
            connect(vertScrollBar, &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
            qDebug() << "Scrollbar is at min pos";
        }
        else
            qDebug() << "Scrollbar is in the middle somewhere";
        if(scrollToBottomConnected)
        {
            qDebug() << "ScrollToBottom Disconnect!";
            //disconnect(msgModel, &MsgModel::rowsInserted, this, &MainWindow::autoScroll);
            scrollToBottomConnected = false;
            emit changedDataAcquisitionMode(false);
        }
        //ToDO reload older model indices
    }
}

void MainWindow::autoScroll()
{
    QTimer::singleShot(0,ui->msgTableView, &QTableView::scrollToBottom);
}

void MainWindow::updateSlider(int direction)
{
    qDebug() << __PRETTY_FUNCTION__;
    QScrollBar *vertScrollBar = ui->msgTableView->verticalScrollBar();
    vertScrollBar->setSliderPosition(vertScrollBar->sliderPosition()+direction);

}

void MainWindow::scrollToGetMoreContent(bool enabled)
{
    if(enabled)
        connect(ui->msgTableView->verticalScrollBar(), &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
    else
        disconnect(ui->msgTableView->verticalScrollBar(), &QScrollBar::valueChanged, this, &MainWindow::scrollBarMsgTableViewMoved);
}
