/**
 * \file msgstreammodel.h
 * \author Christian Neuberger
 * \date 2017-02-04
 * 
 * \brief The MsgStreamModel holds all messages that are to be displayed by the MessageStream
 * 
 * 
 */
#ifndef MSGSTREAMMODEL_H
#define MSGSTREAMMODEL_H


/* #include "hugeqvector.h" */

#include "datastorage.h"
#include "rsimpleringbuff.h"

#include <QAbstractTableModel>
#include <QString>

class Msg;
class MainWindow;
class MessageStream;
class FilterIDStore;
class FilterCodeStore;
class FilterTimestampStore;

class IDRep;
class MsgTypeRep;
/* class MsgDataRep; */

class MsgStreamModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum HeaderCols
    {
        COL_TIMESTAMP,
        COL_ID,
        COL_CODE,
        COL_DATA,
        COL_NR_OF_COLS
    };

    enum DataUserRole
    {
        DataUsr_RawData = Qt::UserRole+0,
        DataUsr_Msg = Qt::UserRole+1
    };

    /**
     * \brief Constructs an empty #MsgStreamModel for use with a MessageStream
     */
    MsgStreamModel(
             size_t nrOfMessagesToDisplay,
             const FilterIDStore &filterIDModel,
             const FilterCodeStore &filterCodeModel,
             const FilterTimestampStore &filterTimestampModel,
             QObject *parent = Q_NULLPTR
             );
    /**
     * \brief Cleans up the MsgStreamModel
     */
    ~MsgStreamModel();

    /**
     * \brief Returns the current number of rows/#Msg that are contained in the #MsgStreamModel object
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * \brief Returns the headers of the #MsgStreamModel/ the number of fields of a #Msg
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * \brief Retrieves Data from the #MsgStreamModel according to the provided role for the given index
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    /**
     * \brief Returns the HeaderData for the given section, orientation, and role
     * 
     * The #MsgStreamModel does only have vertical colums, thus horizontal orientation will not return valid values.
     * The returned header data corresponds to the fields of a #Msg
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    void addMsg(const Msg &msg);
    /**
     * \brief Clears the whole #MsgStreamModel for a fresh start
     * 
     * This method does only delete data (free memory) of data that is contained in the model.
     * NO #Msg is deleted that is stored elsewhere.
     */
    void clear();

    /**
     * \brief Parses the contents of the #MsgStreamModel to JSON format
     * 
     * The #MsgStreamModel consists of its #msgBuffer
     */
    QByteArray ParseToJson();
    /**
     * \brief Parses a QByteArray that was previously saved by a #MsgStreamModel back to a valid #MsgStreamModel
     * 
     * The QByteArray shall contain the #msgBuffer for the #MsgStreamModel
     * \warning All contents that were in the #MsgStreamModel prior to calling this method are dropped!
     */
    void ParseFromJson(const QByteArray &jsonFile);

private slots:
    /**
     * \brief The #messageReceived slot shall be called whenever a new message that is to be displayed is received
     */
    void messageReceived(const Msg &msg);

    void slt_IDRepAdded(const IDRep &addedIDRep);
    void slt_IDRepUpdated(const IDRep &changedIDRep);
    void slt_IDRepRemoved(const MsgIDType idWhoseIDRepWasRemoved);
    void slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep);
    void slt_MsgTypeRepUpdated(const MsgTypeRep &changedMsgTypeRep);
    void slt_MsgTypeRepRemoved(const MsgCodeType codeWhoseMsgTypeRepWasRemoved);
    /* void slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep); */
    /* void slt_MsgDataRepUpdated(const MsgDataRep &changedMsgDataRep); */
    /* void slt_MsgDataRepRemoved(const MsgCodeType codeWhoseDataRepWasRemoved); */

signals:
    /**
     * \brief The #rowAppended signal is emitted every time a message is added to the #MsgStreamModel
     */
    void rowAppended(unsigned int rowNr);
    /**
     * \brief The #rowsAdded signal is emitted every time multiple messages are added to the #MsgStreamModel
     */
    void rowsAdded(unsigned int nrOfRowsAdded);
    /**
     * \brief The #rowInvalidated singal is emitted every time a row/#Msg is invalidated
     */
    void rowInvalidated(const QModelIndex &index);

private:
    friend class MainWindow;
    friend class MessageStream;
    /**
     * \brief The #msgBuffer contains all messages that are to be displayed by the #MessageStream
     */
    RSimpleDestructiveRingBuff<Msg> msgBuffer;
    const size_t NrOfMessagesToDisplay;

    const FilterIDStore &FilterIDModel;
    const FilterCodeStore &FilterCodeModel;
    const FilterTimestampStore &FilterTimestampModel;
};

#endif // MSGSTREAMMODEL_H
