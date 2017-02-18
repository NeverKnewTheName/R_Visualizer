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
#include "fileparsable.h"

class MainWindow;
class MessageConfig;
class MessageFilter;
class MsgStorage;

class FileParser;

namespace Ui {
class MessageStream;
}

class MessageStream : public QFrame, public FileParsable
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a new MessageStream object
     * 
     * \param[in] msgConfig     Used for mapping #Msg to #PrettyMsg
     * \param[in] msgFilter     Used for filtering #Msg to display
     * \param[in] msgStorage    The #MsgStorage that to display the #Msg from
     * \param[in] parent        The parent QWidget
     * 
     * This constructor constructs a new #MessageStream widget. The #IDModel and #MsgTypeModel are used for its delegates
     * to paint #Msg pretty. The various filter models are used to filter the displayed #Msg.
     */
    explicit MessageStream(
            const MessageConfig *msgConfig,
            const MessageFilter *msgFilter,
            MsgStorage &msgStorage,
            QWidget *parent = 0
            );
    /**
     * \brief Deletes and cleans up the #MessageStream when destroyed
     * 
     * \note Does not delete any of the passed models!
     */
    ~MessageStream();

    /**
     * \brief Appends the given #Msg to the MessageStream if it matches the current MessageFilter criteria
     * 
     * \param[in] msgToAppend #Msg that is matched against the MessageFilter criteria, parsed to a #PrettyMsg, and appended to the MessageStream
     * 
     * \return whether the #Msg was appended
     * \returns true #Msg was appended
     * \returns false #Msg was not appended
     */
    bool appendMsg(const Msg &msgToAppend);
    /**
     * \brief Prepends the given #Msg to the MessageStream if it matches the current MessageFilter criteria
     * 
     * \param[in] msgToPrepend #Msg that is matched against the MessageFilter criteria, parsed to a #PrettyMsg, and prepended to the MessageStream
     * 
     * \return whether the #Msg was prepended
     * \returns true #Msg was prepended
     * \returns false #Msg was not prepended
     */
    bool prependMsg(const Msg &msgToPrepend);

    void accept(FileParser *visitor);

private:
    void fetchMsgForward();
    void fetchMsgBackward();

    void filterHelper();

signals:

private slots:
    void slt_ReceiveMsg(const Msg &receivedMsg);
    void slt_MsgStorageCleared();

    void slt_IDRepAdded(const IDRep &addedIDRep);
    void slt_IDRepUpdated(const IDRep &updatedIDRep);
    void slt_IDRepRemoved(const MsgIDType relatedID);
    void slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep);
    void slt_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep);
    void slt_MsgTypeRepRemoved(const MsgCodeType relatedCode);
    /* void slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep); */
    /* void slt_MsgDataRepUpdated(const MsgDataRep &changedMsgDataRep); */
    /* void slt_MsgDataRepRemoved(const MsgCodeType codeWhoseDataRepWasRemoved); */

    void slt_IDFilterEnabled(const bool enabled);
    void slt_IDFilterAdded();
    void slt_IDFilterRemoved();

    void slt_MsgTypeFilterEnabled(const bool enabled);
    void slt_MsgTypeFilterAdded();
    void slt_MsgTypeFilterRemoved();

    void slt_TimestampFromFilterEnabled(const bool enabled);
    void slt_TimestampToFilterEnabled(const bool enabled);
    void slt_TimestampFilterFromChanged();
    void slt_TimestampFilterToChanged();

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
    MsgStorage &msgStorage;
    MsgStreamModel msgStreamModel;
    bool continousMsgStream;
};

#endif // MESSAGESTREAM_H
