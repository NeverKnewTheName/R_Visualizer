/**
 * \file messagestream.h
 * \author Christian Neuberger
 * \date 2017-02-07
 * 
 * \brief The #MessageStream displays the incoming #Msg
 */
#ifndef MESSAGESTREAM_H
#define MESSAGESTREAM_H

#include <QWidget>
#include <QFrame>

#include "msgstreammodel.h"
/* #include "msgiddelegate.h" */
/* #include "msgdatadelegate.h" */

class MainWindow;
class MessageConfig;
class MessageFilter;

namespace Ui {
class MessageStream;
}

class MessageStream : public QFrame
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a new MessageStream object
     * 
     * \param[in] parent                            The parent QWidget
     * 
     * This constructor constructs a new #MessageStream widget. The #IDModel and #MsgTypeModel are used for its delegates
     * to paint #Msg pretty. The various filter models are used to filter the displayed #Msg.
     */
    explicit MessageStream(
            const MessageConfig *msgConfig,
            const MessageFilter *msgFilter,
            QWidget *parent = 0
            );
    /**
     * \brief Deletes and cleans up the #MessageStream when destroyed
     * 
     * \note Does not delete any of the passed models!
     */
    ~MessageStream();

    void appendMsg(const Msg &msgToAppend);

signals:

private slots:
    void slt_ReceiveMsg(const Msg &receivedMsg);
    void slt_IDRepAdded(const IDRep &addedIDRep);
    void slt_IDRepUpdated(const IDRep &changedIDRep);
    void slt_IDRepRemoved(const MsgIDType idWhoseIDRepWasRemoved);
    void slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep);
    void slt_MsgTypeRepUpdated(const MsgTypeRep &changedMsgTypeRep);
    void slt_MsgTypeRepRemoved(const MsgCodeType codeWhoseMsgTypeRepWasRemoved);
    /* void slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep); */
    /* void slt_MsgDataRepUpdated(const MsgDataRep &changedMsgDataRep); */
    /* void slt_MsgDataRepRemoved(const MsgCodeType codeWhoseDataRepWasRemoved); */

    /**
     * \brief This slot is called when the scrollbar of the msgStreamTV changes
     * 
     * When the scrollbar reaches its max or min value further messages are fetched if available
     */
    void slt_MsgStreamViewScrollBarMoved(int position);

private:
    friend class MainWindow;
    Ui::MessageStream *ui;
    const MessageConfig *msgConfig;
    const MessageFilter *msgFilter;
    MsgStreamModel msgStreamModel;
    /* MsgIDDelegate idDelegate; */
    /* MsgDataDelegate dataDelegate; */
};

#endif // MESSAGESTREAM_H
