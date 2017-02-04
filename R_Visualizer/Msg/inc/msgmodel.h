/**
 * \file msgmodel.h
 * \author Christian Neuberger
 * \date 2017-02-04
 * 
 * \brief The MsgModel holds all messages that are to be displayed by the MessageStream
 * 
 * 
 */
#ifndef MSGMODEL_H
#define MSGMODEL_H

class Msg;

/* #include "hugeqvector.h" */

#include "datastorage.h"
#include "rsimpleringbuff.h"

#include <QAbstractTableModel>
#include <QString>

class MainWindow;

class MsgModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum HeaderCols
    {
        COL_TIMESTAMP,
        COL_NAME,
        COL_MESSAGE,
        COL_NR_OF_COLS
    };

    /**
     * \brief Constructs an empty #MsgModel for use with a MessageStream
     */
    MsgModel(size_t nrOfMessagesToDisplay, QObject *parent = Q_NULLPTR);
    /**
     * \brief Cleans up the MsgModel
     */
    ~MsgModel();

    /**
     * \brief Returns the current number of rows/#Msg that are contained in the #MsgModel object
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * \brief Returns the headers of the #MsgModel/ the number of fields of a #Msg
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * \brief Retrieves Data from the #MsgModel according to the provided role for the given index
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    /**
     * \brief Sets the data of the #Msg at the given index according to the given role
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    /**
     * \brief Retunrs the HeaderData for the given section, orientation, and role
     * 
     * The #MsgModel does only have vertical colums, thus horizontal orientation will not return valid values.
     * The returned header data corresponds to the fields of a #Msg
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    /**
     * \brief Removes count rows/#Msg starting from row
     */
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    /** 
     * \brief Removes a single row/#Msg at row
     */
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    void addMsg(const Msg &msg);
    /**
     * \brief Clears the whole #MsgModel for a fresh start
     * 
     * This method does only delete data (free memory) of data that is contained in the model.
     * NO #Msg is deleted that is stored elsewhere.
     */
    void clear();

    //Kept for compatibility with SendMessages ... //ToDELETE
    RSimpleDestructiveRingBuff<Msg> getMsgs() const;
    //Kept for compatibility with SendMessages ... //ToDELETE
    void setMsgs(const RSimpleDestructiveRingBuff<Msg> value);
    /* HugeQVector<Msg> getMsgs() const; */
    /* void setMsgs(const HugeQVector<Msg> value); */

    /**
     * \brief Parses the contents of the #MsgModel to JSON format
     * 
     * The #MsgModel consists of its #msgBuffer
     */
    QByteArray ParseToJSON();
    /**
     * \brief Parses a QByteArray that was previously saved by a #MsgModel back to a valid #MsgModel
     * 
     * The QByteArray shall contain the #msgBuffer for the #MsgModel
     * \warning All contents that were in the #MsgModel prior to calling this method are dropped!
     */
    void ParseFromJSON(QByteArray jsonFile);

private:
    /**
     * \brief The #msgBuffer contains all messages that are to be displayed by the #MessageStream
     */
    RSimpleDestructiveRingBuff<Msg> msgBuffer;
    /* DataStorage<Msg> msgs; */
    /* HugeQVector<Msg> msgs; */
    const size_t NrOfMessagesToDisplay;
    friend class MainWindow;

private slots:
    /**
     * \brief The #messageReceived slot shall be called whenever a new message that is to be displayed is received
     */
    void messageReceived(const Msg &msg);

signals:
    /**
     * \brief The #rowAppended signal is emitted every time a message is added to the #MsgModel
     */
    void rowAppended(unsigned int rowNr);
    /**
     * \brief The #rowsAdded signal is emitted every time multiple messages are added to the #MsgModel
     */
    void rowsAdded(unsigned int nrOfRowsAdded);
    /**
     * \brief The #rowInvalidated singal is emitted every time a row/#Msg is invalidated
     */
    void rowInvalidated(const QModelIndex &index);
};

#endif // MSGMODEL_H
