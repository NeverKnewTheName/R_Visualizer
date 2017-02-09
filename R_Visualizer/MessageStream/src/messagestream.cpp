#include "messagestream.h"
#include "ui_messagestream.h"

#include "QHeaderView"

MessageStream::MessageStream(
            const IDModel &msgStreamIDModel, 
            const MsgTypeModel &msgStreamTypeModel,
            const FilterIDStore &msgStreamIDFilterModel,
            const FilterCodeStore &msgStreamCodeFilterModel,
            const FilterTimestampStore &msgStreamTimestampFilterModel,
            QWidget *parent 
            ) :
    QWidget(parent),
    ui(new Ui::MessageStream),
    msgStreamIDModel(msgStreamIDModel),
    msgStreamTypeModel(msgStreamTypeModel),
    msgStreamModel(
            50,
            msgStreamIDFilterModel,
            msgStreamCodeFilterModel,
            msgStreamTimestampFilterModel,
            this
            ),
    idDelegate(msgStreamIDModel, this),
    dataDelegate(msgStreamTypeModel, this)
{
    ui->setupUi(this);

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
    ui->msgStreamTV->setItemDelegateForColumn(MsgStreamModel::COL_ID, idDelegate);
    /* // Set the delegate for the message's Code */
    /* ui->msgStreamTV->setItemDelegateForColumn(MsgStreamModel::COL_CODE, dataDelegate); */
    // Set the delegate for the message's Data
    ui->msgStreamTV->setItemDelegateForColumn(MsgStreamModel::COL_DATA, dataDelegate);
}

MessageStream::~MessageStream()
{
    delete ui;
}

void MessageStream::slt_ReceiveMsg(const Msg &receivedMsg)
{

}
