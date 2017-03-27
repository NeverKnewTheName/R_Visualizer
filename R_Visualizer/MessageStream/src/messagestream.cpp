#include "messagestream.h"
#include "ui_messagestream.h"

#include <QHeaderView>
#include <QScrollBar>

#include "MessageConfig.h"
#include "messagefilter.h"
#include "msgstorage.h"

#include "idmodel.h"
#include "msgtypemodel.h"
#include "idrep.h"
#include "msgtyperep.h"

#include "fileparser.h"


#include <QDebug>

MessageStream::MessageStream(
            const MessageConfig *msgConfig,
            const MessageFilter *msgFilter,
            MsgStorage &msgStorage,
            QWidget *parent
            ) :
    QFrame(parent),
    ui(new Ui::MessageStream),
    msgConfig(msgConfig),
    msgFilter(msgFilter),
    msgStorage(msgStorage),
    msgStreamModel(
            50,
            this
            )
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
    connect(msgConfig, &MessageConfig::sgnl_IDRepAdded, this, &MessageStream::slt_IDRepAdded);
    connect(msgConfig, &MessageConfig::sgnl_IDRepUpdated, this, &MessageStream::slt_IDRepUpdated);
    connect(msgConfig, &MessageConfig::sgnl_IDRepRemoved, this, &MessageStream::slt_IDRepRemoved);

    connect(msgConfig, &MessageConfig::sgnl_MsgTypeRepAdded, this, &MessageStream::slt_MsgTypeRepAdded);
    connect(msgConfig, &MessageConfig::sgnl_MsgTypeRepUpdated, this, &MessageStream::slt_MsgTypeRepUpdated);
    connect(msgConfig, &MessageConfig::sgnl_MsgTypeRepRemoved, this, &MessageStream::slt_MsgTypeRepRemoved);

    /* connect(&msgStreamMsgDataModel, &MsgDataModel::sgnl_MsgDataRepAdded, &msgStreamModel, &MsgStreamModel::slt_MsgDataRepAdded); */
    /* connect(&msgStreamMsgDataModel, &MsgDataModel::sgnl_MsgDataRepUpdated, &msgStreamModel, &MsgStreamModel::slt_MsgDataRepUpdated); */
    /* connect(&msgStreamMsgDataModel, &MsgDataModel::sgnl_MsgDataRepRemoved, &msgStreamModel, &MsgStreamModel::slt_MsgDataRepRemoved); */

    connect(msgFilter, &MessageFilter::sgnl_IDFilterEnabled, this, &MessageStream::slt_IDFilterEnabled);
    connect(msgFilter, &MessageFilter::sgnl_IDAddedToFilter, this, &MessageStream::slt_IDFilterAdded);
    connect(msgFilter, &MessageFilter::sgnl_IDRemovedFromFilter, this, &MessageStream::slt_IDFilterRemoved);
    
    connect(msgFilter, &MessageFilter::sgnl_CodeFilterEnabled, this, &MessageStream::slt_MsgTypeFilterEnabled);
    connect(msgFilter, &MessageFilter::sgnl_CodeAddedToFilter, this, &MessageStream::slt_MsgTypeFilterAdded);
    connect(msgFilter, &MessageFilter::sgnl_CodeRemovedFromFilter, this, &MessageStream::slt_MsgTypeFilterRemoved);

    connect(msgFilter, &MessageFilter::sgnl_TimestampFilterFromEnabled, this, &MessageStream::slt_TimestampFromFilterEnabled);
    connect(msgFilter, &MessageFilter::sgnl_TimestampFromChanged, this, &MessageStream::slt_TimestampFilterFromChanged);
    connect(msgFilter, &MessageFilter::sgnl_TimestampFilterToEnabled, this, &MessageStream::slt_TimestampToFilterEnabled);
    connect(msgFilter, &MessageFilter::sgnl_TimestampToChanged, this, &MessageStream::slt_TimestampFilterToChanged);


    /*
     * Configure the MessageStreamTV's Scrollbar to trigger fetching of further Msgs if any
     */
    connect(ui->msgStreamTV->verticalScrollBar(), &QScrollBar::valueChanged, this, &MessageStream::slt_MsgStreamViewScrollBarMoved);


    connect(&msgStorage, &MsgStorage::sgnl_MsgAdded, this, &MessageStream::slt_ReceiveMsg);
    connect(&msgStorage, &MsgStorage::sgnl_StoreCleared, this, &MessageStream::slt_MsgStorageCleared);
}

MessageStream::~MessageStream()
{
    delete ui;
}

bool MessageStream::appendMsg(const Msg &msgToAppend)
{
    if(msgFilter->filterMsg(msgToAppend))
    {
        const PrettyMsg &prettyMsgToAppend = msgConfig->prettifyMsg(msgToAppend);
        msgStreamModel.appendMsg(prettyMsgToAppend);
        return true;
    }
    return false;
}

bool MessageStream::prependMsg(const Msg& msgToPrepend)
{
    if(msgFilter->filterMsg(msgToPrepend))
    {
        const PrettyMsg &prettyMsgToPrepend = msgConfig->prettifyMsg(msgToPrepend);
        msgStreamModel.prependMsg(prettyMsgToPrepend);
        return true;
    }
    return false;
}

void MessageStream::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

void MessageStream::fetchMsgForward()
{
}

void MessageStream::fetchMsgBackward()
{
}

void MessageStream::filterHelper()
{
    const int curMsgStreamModelSize = msgStreamModel.size();
    int curMsgStorageSize = msgStorage.size();

    msgStreamModel.clear();

    if(curMsgStorageSize)
    {
        while(curMsgStorageSize)
        {
            curMsgStorageSize--;
            if(msgStreamModel.size() == 50)
            {
                break;
            }
            const Msg &msg = msgStorage.at(curMsgStorageSize);
            prependMsg(msg);
        }
    }
}

void MessageStream::slt_ReceiveMsg(const Msg &receivedMsg)
{
    appendMsg(receivedMsg);
}

void MessageStream::slt_MsgStorageCleared()
{
    msgStreamModel.clear();
}

void MessageStream::slt_IDRepAdded(const IDRep &addedIDRep)
{
    msgStreamModel.setIDRepForID(addedIDRep.getId(), addedIDRep);
}

void MessageStream::slt_IDRepUpdated(const IDRep &updatedIDRep)
{
    msgStreamModel.setIDRepForID(updatedIDRep.getId(), updatedIDRep);

}

void MessageStream::slt_IDRepRemoved(const MsgIDType relatedID)
{
    msgStreamModel.setIDRepForID(relatedID, IDRep(relatedID));

}

void MessageStream::slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep)
{
    msgStreamModel.setMsgTypeRepForCode(addedMsgTypeRep.getCode(), addedMsgTypeRep);
}

void MessageStream::slt_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep)
{
    msgStreamModel.setMsgTypeRepForCode(updatedMsgTypeRep.getCode(), updatedMsgTypeRep);
}

void MessageStream::slt_MsgTypeRepRemoved(const MsgCodeType relatedCode)
{
    msgStreamModel.setMsgTypeRepForCode(relatedCode, MsgTypeRep(relatedCode));
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

/* void MessageStream::filterIDHelper() */
/* { */
/*     const int msgStreamModelSize = msgStreamModel.size(); */
/*     int filteredOutMsgs = 0; */
/*     for(int i = 0; i < msgStreamModelSize; ++i) */
/*     { */
/*         const bool msgNeedsToBeFiltered = !msgFilter->filterMsg(msgStreamModel.at(i)); */
/*         if(msgNeedsToBeFiltered) */
/*         { */
/*             msgStreamModel.removeRow(i); */
/*             filteredOutMsgs++; */
/*         } */
/*     } */
/*     while(filteredOutMsgs) */
/*     { */
/*         filteredOutMsgs--; */
/*         fetchMsgFromStorage(); */
/*     } */
/* } */

void MessageStream::slt_IDFilterEnabled(const bool enabled)
{
    filterHelper();
}

void MessageStream::slt_IDFilterAdded()
{
    filterHelper();
}

void MessageStream::slt_IDFilterRemoved()
{
    filterHelper();
}

void MessageStream::slt_MsgTypeFilterEnabled(const bool enabled)
{
    filterHelper();
}

void MessageStream::slt_MsgTypeFilterAdded()
{
    filterHelper();
}

void MessageStream::slt_MsgTypeFilterRemoved()
{
    filterHelper();
}

void MessageStream::slt_TimestampFromFilterEnabled(const bool enabled)
{
    filterHelper();
}

void MessageStream::slt_TimestampToFilterEnabled(const bool enabled)
{
    filterHelper();
}

void MessageStream::slt_TimestampFilterFromChanged()
{
    filterHelper();
}

void MessageStream::slt_TimestampFilterToChanged()
{
    filterHelper();
}

