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

#include <QAbstractTableModel>
#include <QString>

class MainWindow;
class MessageStream;
class FileParser;

class IDRep;
class MsgTypeRep;
/* class MsgDataRep; */

#include "datastorage.h"
#include "rsimpleringbuff.h"
#include "prettymsg.h"
#include "fileparsable.h"


class MsgStreamModel : public QAbstractTableModel, public FileParsable
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

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    /**
     * \brief Appends a #Msg to display to the #MsgStreamModel
     */
    void appendMsg(const PrettyMsg &msg);
    /**
     * \brief Prepends a #Msg to display to the #MsgStreamModel
     */
    void prependMsg(const PrettyMsg &msg);

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

    void accept(FileParser *visitor);

private slots:
    /**
     * \brief The #messageReceived slot shall be called whenever a new message that is to be displayed is received
     */
    void messageReceived(const PrettyMsg &msg);

    void slt_IDRepAdded(const IDRep &addedIDRep);
    void slt_IDRepUpdated(const IDRep &updatedIDRep);
    void slt_IDRepRemoved(const MsgIDType relatedID);

    void slt_MsgTypeRepAdded(const MsgTypeRep &addedMsgTypeRep);
    void slt_MsgTypeRepUpdated(const MsgTypeRep &updatedMsgTypeRep);
    void slt_MsgTypeRepRemoved(const MsgCodeType relatedCode);

    /* void slt_MsgDataRepAdded(const MsgDataRep &addedMsgDataRep); */
    /* void slt_MsgDataRepUpdated(const MsgDataRep &updatedMsgDataRep); */
    /* void slt_MsgDataRepRemoved(const MsgCodeType relatedCode); */

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

    void setIDRepForID(const MsgIDType relatedID, const IDRep &idRepToSet);
    void setMsgTypeRepForCode(const MsgCodeType relatedCode, const MsgTypeRep &msgTypeRepToSet);
    
    /**
     * \brief The #msgBuffer contains all messages that are to be displayed by the #MessageStream
     */
    RSimpleDestructiveRingBuff<PrettyMsg> msgBuffer;
    const size_t NrOfMessagesToDisplay;
    size_t currentLastIndex;
};

#endif // MSGSTREAMMODEL_H
