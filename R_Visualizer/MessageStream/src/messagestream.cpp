#include "messagestream.h"
#include "ui_messagestream.h"


#include "messageconfig.h"
#include "messagefilter.h"

#include "idmodel.h"
#include "msgtypemodel.h"
#include "idrep.h"
#include "msgtyperep.h"

#include <QHeaderView>
#include <QScrollBar>

#include <QDebug>

MessageStream::MessageStream(
            const MessageConfig *msgConfig,
            const MessageFilter *msgFilter,
            QWidget *parent
            ) :
    QFrame(parent),
    ui(new Ui::MessageStream),
    msgConfig(msgConfig),
    msgFilter(msgFilter),
    msgStreamModel(
            50,
            this
            )//,
    /* idDelegate(msgStreamIDModel, this), */
    /* dataDelegate(msgStreamMsgTypeModel, this) */
{
    ui->setupUi(this);
    setFrameStyle(QFrame::StyledPanel);

    // set the model of the message stream
    ui->msgStreamTV->setModel(&msgStreamModel);

    // Adjust the horizontal header of the message stream
    QHeaderView *horzHeader = ui->msgStreamTV->horizontalHeader();
    horzHeader->setSectionResizeMode(MsgStreamModel::COL_TIMESTAMP, QHeaderView::Fixed);
    horzHeader->resizeSection(MsgStreamModel::COL_TIMESTAMP, 150);
    horzHeader->setSectionResizeMode(MsgStreamModel::COL_ID, QHeaderView::Interactive);
    horzHeader->setSectionResizeMode(MsgStreamModel::COL_CODE, QHeaderView::Interactive);
    horzHeader->setSectionResizeMode(MsgStreamModel::COL_DATA, QHeaderView::Stretch);

    ui->msgStreamTV->setAlternatingRowColors(true);
    
    // Disable editing of the message stream
    ui->msgStreamTV->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Select whole rows when cells are selected
    ui->msgStreamTV->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Scroll per item so that an item at the bottom/top is always displayed in full
    ui->msgStreamTV->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);

    // Set the delegate for the message's ID
    /* ui->msgStreamTV->setItemDelegateForColumn(MsgStreamModel::COL_ID, idDelegate); */
    /* // Set the delegate for the message's Code */
    /* ui->msgStreamTV->setItemDelegateForColumn(MsgStreamModel::COL_CODE, dataDelegate); */
    // Set the delegate for the message's Data
    /* ui->msgStreamTV->setItemDelegateForColumn(MsgStreamModel::COL_DATA, dataDelegate); */

    //ToDO MessageConfig signal is not emitted...only the signal from the IDModel -> rewire!
    connect(msgConfig, &MessageConfig::sgnl_IDRepAdded, &msgStreamModel, &MsgStreamModel::slt_IDRepAdded);
    connect(msgConfig, &MessageConfig::sgnl_IDRepUpdated, &msgStreamModel, &MsgStreamModel::slt_IDRepUpdated);
    connect(msgConfig, &MessageConfig::sgnl_IDRepRemoved, &msgStreamModel, &MsgStreamModel::slt_IDRepRemoved);

    connect(msgConfig, &MessageConfig::sgnl_MsgTypeRepAdded, &msgStreamModel, &MsgStreamModel::slt_MsgTypeRepAdded);
    connect(msgConfig, &MessageConfig::sgnl_MsgTypeRepUpdated, &msgStreamModel, &MsgStreamModel::slt_MsgTypeRepUpdated);
    connect(msgConfig, &MessageConfig::sgnl_MsgTypeRepRemoved, &msgStreamModel, &MsgStreamModel::slt_MsgTypeRepRemoved);

    /* connect(&msgStreamMsgDataModel, &MsgDataModel::sgnl_MsgDataRepAdded, &msgStreamModel, &MsgStreamModel::slt_MsgDataRepAdded); */
    /* connect(&msgStreamMsgDataModel, &MsgDataModel::sgnl_MsgDataRepUpdated, &msgStreamModel, &MsgStreamModel::slt_MsgDataRepUpdated); */
    /* connect(&msgStreamMsgDataModel, &MsgDataModel::sgnl_MsgDataRepRemoved, &msgStreamModel, &MsgStreamModel::slt_MsgDataRepRemoved); */

    /* connect(msgFilter, &MessageFilter::sgnl_IDFilterEnabled, this, & */


    /*
     * Configure the MessageStreamTV's Scrollbar to trigger fetching of further Msgs if any
     */
    connect(ui->msgStreamTV->verticalScrollBar(), &QScrollBar::valueChanged, this, &MessageStream::slt_MsgStreamViewScrollBarMoved);
}

MessageStream::~MessageStream()
{
    delete ui;
}

void MessageStream::appendMsg(const Msg &msgToAppend)
{
    if(msgFilter->filterMsg(msgToAppend))
    {
        const PrettyMsg &prettyMsgToAppend = msgConfig->prettifyMsg(msgToAppend);
        msgStreamModel.appendMsg(prettyMsgToAppend);
    }
}

void MessageStream::prependMsg(const Msg& msgToPrepend)
{
    if(msgFilter->filterMsg(msgToPrepend))
    {
        const PrettyMsg &prettyMsgToPrepend = msgConfig->prettifyMsg(msgToPrepend);
        msgStreamModel.prependMsg(prettyMsgToPrepend);
    }
}

void MessageStream::slt_ReceiveMsg(const Msg &receivedMsg)
{
    appendMsg(receivedMsg);
}

void MessageStream::slt_IDRepAdded(const IDRep &addedIDRep)
{

}

void MessageStream::slt_IDRepUpdated(const IDRep &changedIDRep)
{

}

void MessageStream::slt_IDRepRemoved(const MsgIDType idWhoseIDRepWasRemoved)
{

}

void MessageStream::slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep)
{

}

void MessageStream::slt_MsgTypeRepUpdated(const MsgTypeRep &changedMsgTypeRep)
{

}

void MessageStream::slt_MsgTypeRepRemoved(const MsgCodeType codeWhoseMsgTypeRepWasRemoved)
{

}

/* void MessageStream::slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep) */
/* { */

/* } */

/* void MessageStream::slt_MsgDataRepUpdated(const MsgDataRep &changedMsgDataRep) */
/* { */

/* } */

/* void MessageStream::slt_MsgDataRepRemoved(const MsgCodeType codeWhoseDataRepWasRemoved) */
/* { */

/* } */

void MessageStream::slt_MsgStreamViewScrollBarMoved(int position)
{
    QScrollBar *viewVertScrollBar = ui->msgStreamTV->verticalScrollBar();

    if(position >= viewVertScrollBar->maximum())
    {
        //Scrollbar is at the end of the view
        qDebug() << "Scrollbar at max";
    }
    else if(position <= viewVertScrollBar->minimum())
    {
        //Scrollbar is at the start of the view
        qDebug() << "Scrollbar at min";
    }
    else
    {
        //Scrollbar is somewhere in the middle
        qDebug() << "Scrollbar somewhere in the middle";
    }
}

void MessageStream::slt_IDFilterEnabled(const bool enabled)
{
}

void MessageStream::slt_IDFilterAdded(const MsgIDType addedID)
{
}

void MessageStream::slt_IDFilterRemoved(const MsgIDType removedID)
{
}

void MessageStream::slt_MsgTypeFilterEnabled(const bool enabled)
{
}

void MessageStream::slt_MsgTypeFilterAdded(const MsgCodeType addedCode)
{
}

void MessageStream::slt_MsgTypeFilterRemoved(const MsgCodeType removedCode)
{
}

void MessageStream::slt_TimestampFromFilterEnabled(const bool enabled)
{
}

void MessageStream::slt_TimestampToFilterEnabled(const bool enabled)
{
}

void MessageStream::slt_TimestampFilterFromChanged(const QDateTime &timestampFrom)
{
}

void MessageStream::slt_TimestampFilterToChanged(const QDateTime &timestampTo)
{
}

