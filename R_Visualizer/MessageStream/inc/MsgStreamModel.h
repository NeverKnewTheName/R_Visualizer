/**
 * @file MsgStreamModel.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The default MessageStream Model
 */
#ifndef MSGSTREAMMODEL_H
#define MSGSTREAMMODEL_H

#include <QAbstractTableModel>

#include "IMsgStreamModel.h"

class IMsgStreamStore;

/**
 * @brief The MsgStreamModel
 */
class MsgStreamModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    /**
     * @brief Enumeration of header columns
     */
    enum MsgStreamHeaderCols
    {
        MsgStreamHeaderCol_Timestamp, //!< Timestamp
        MsgStreamHeaderCol_Name, //!< ID/Name
        MsgStreamHeaderCol_Type, //!< Code/Type
        MsgStreamHeaderCol_Data, //!< Data
        MsgStreamHeaderCol_NR_OF_COLS //!< Total number of columns in the header
    };

    MsgStreamModel(
            IMsgStreamStore &msgStreamStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgStreamModel();

    int rowCount(
            const QModelIndex &parent = QModelIndex()
            ) const Q_DECL_OVERRIDE;

    int columnCount(
            const QModelIndex &parent = QModelIndex()
            ) const Q_DECL_OVERRIDE;

    QVariant data(
            const QModelIndex &index,
            int role = Qt::DisplayRole
            ) const Q_DECL_OVERRIDE;

    QVariant headerData(
            int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole
            ) const Q_DECL_OVERRIDE;

signals:

public slots:
    void slt_msgAboutToBeAppended();
    void slt_msgAppended();

    void slt_msgAboutToBePrepended();
    void slt_msgPrepended();

    void slt_storeAboutToOverflow();
    void slt_storeOverflow();

    void slt_storeAboutToUnderflow();
    void slt_storeUnderflow();

    void slt_storeAboutToBeCleared();
    void slt_storeCleared();

private:
    void connectMsgStreamStore();

private:
    IMsgStreamStore &msgStreamStore;

};

#endif /* MSGSTREAMMODEL_H */
