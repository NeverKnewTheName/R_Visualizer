#include "messagestream.h"
#include "ui_messagestream.h"

#include "idmodel.h"
#include "msgtypemodel.h"
#include "idrep.h"
#include "msgtyperep.h"

#include <QHeaderView>

MessageStream::MessageStream(
            const IDModel &msgStreamIDModel,
            const MsgTypeModel &msgStreamMsgTypeModel,
            const FilterIDStore &msgStreamIDFilterModel,
            const FilterCodeStore &msgStreamCodeFilterModel,
            const FilterTimestampStore &msgStreamTimestampFilterModel,
            QWidget *parent
            ) :
    QFrame(parent),
    ui(new Ui::MessageStream),
    msgStreamIDModel(msgStreamIDModel),
    msgStreamMsgTypeModel(msgStreamMsgTypeModel),
    msgStreamModel(
            50,
            msgStreamIDFilterModel,
            msgStreamCodeFilterModel,
            msgStreamTimestampFilterModel,
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

    connect(&msgStreamIDModel, &IDModel::sgnl_IDRepAdded, &msgStreamModel, &MsgStreamModel::slt_IDRepAdded);
    connect(&msgStreamIDModel, &IDModel::sgnl_IDRepUpdated, &msgStreamModel, &MsgStreamModel::slt_IDRepUpdated);
    connect(&msgStreamIDModel, &IDModel::sgnl_IDRepRemoved, &msgStreamModel, &MsgStreamModel::slt_IDRepRemoved);

    connect(&msgStreamMsgTypeModel, &MsgTypeModel::sgnl_MsgTypeRepAdded, &msgStreamModel, &MsgStreamModel::slt_MsgTypeRepAdded);
    connect(&msgStreamMsgTypeModel, &MsgTypeModel::sgnl_MsgTypeRepUpdated, &msgStreamModel, &MsgStreamModel::slt_MsgTypeRepUpdated);
    connect(&msgStreamMsgTypeModel, &MsgTypeModel::sgnl_MsgTypeRepRemoved, &msgStreamModel, &MsgStreamModel::slt_MsgTypeRepRemoved);

    /* connect(&msgStreamMsgDataModel, &MsgDataModel::sgnl_MsgDataRepAdded, &msgStreamModel, &MsgStreamModel::slt_MsgDataRepAdded); */
    /* connect(&msgStreamMsgDataModel, &MsgDataModel::sgnl_MsgDataRepUpdated, &msgStreamModel, &MsgStreamModel::slt_MsgDataRepUpdated); */
    /* connect(&msgStreamMsgDataModel, &MsgDataModel::sgnl_MsgDataRepRemoved, &msgStreamModel, &MsgStreamModel::slt_MsgDataRepRemoved); */
}

MessageStream::~MessageStream()
{
    delete ui;
}

void MessageStream::appendMsg(const Msg &msgToAppend)
{
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
