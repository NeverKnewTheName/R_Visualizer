#ifndef SENDMSGMODEL_H
#define SENDMSGMODEL_H

#include <QAbstractTableModel>
#include <QString>

#include "msg.h"

class IDRep;
class MsgTypeRep;
/* class MsgDataRep; */

class SendMsgModel : public QAbstractTableModel
{
public:
    enum HeaderCols
    {
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

    SendMsgModel(
            QObject *parent = Q_NULLPTR
            );
    virtual ~SendMsgModel();


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

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    /**
     * \brief Returns the HeaderData for the given section, orientation, and role
     * 
     * The #MsgStreamModel does only have vertical colums, thus horizontal orientation will not return valid values.
     * The returned header data corresponds to the fields of a #Msg
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    void addMsg(const Msg &newMsg);

    void clear();

    QByteArray ParseToJson();
    void ParseFromJson(const QByteArray &jsonFile);

    QVector<Msg> getMsgPacket() const;
    void setMsgPacket(const QVector<Msg> &msgPacket);

private slots:
    void slt_addMsg(const Msg &newMsg);

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

private:
    QVector<Msg> msgPacketStorage;
};

#endif /* SENDMSGMODEL_H */
