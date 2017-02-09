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

#include "msgstreammodel.h"
#include "msgiddelegate.h"
#include "msgdatadelegate.h"

class IDModel;
class MsgTypeModel;

namespace Ui {
class MessageStream;
}

class MessageStream : public QWidget
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a new MessageStream object
     * 
     * \param[in] msgStreamIDModel                  The #IDModel to use for the #MessageStream's #MsgIDDelegate
     * \param[in] msgStreamTypeModel                The #MsgTypeModel to use for the #MessageStream's #MsgDataDelegate
     * \param[in] msgStreamIDFilterModel            The #FilterIDStore to use for filtering #MsgIDType in the #MessageStream
     * \param[in] msgStreamCodeFilterModel          The #FilterCodeStore to use for filtering #MsgCodeType in the #MessageStream
     * \param[in] msgStreamTimestampFilterModel     The #FilterTimestampStore to use for filtering #Msg according to timestamps in the #MessageStream
     * \param[in] parent                            The parent QWidget
     * 
     * This constructor constructs a new #MessageStream widget. The #IDModel and #MsgTypeModel are used for its delegates
     * to paint #Msg pretty. The various filter models are used to filter the displayed #Msg.
     */
    explicit MessageStream(
            const IDModel &msgStreamIDModel,
            const MsgTypeModel &msgStreamTypeModel,
            const FilterIDStore &msgStreamIDFilterModel,
            const FilterCodeStore &msgStreamCodeFilterModel,
            const FilterTimestampStore &msgStreamTimestampFilterModel,
            QWidget *parent = 0
            );
    /**
     * \brief Deletes and cleans up the #MessageStream when destroyed
     * 
     * \note Does not delete any of the passed models!
     */
    ~MessageStream();

signals:

private slots:
    void slt_ReceiveMsg(const Msg &receivedMsg);

private:
    Ui::MessageStream *ui;
    const IDModel &msgStreamIDModel;
    const MsgTypeModel &msgStreamTypeModel;
    MsgStreamModel msgStreamModel;
    MsgIDDelegate idDelegate;
    MsgDataDelegate dataDelegate;
};

#endif // MESSAGESTREAM_H
