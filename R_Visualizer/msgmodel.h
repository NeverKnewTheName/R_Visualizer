#ifndef MSGMODEL_H
#define MSGMODEL_H

#include "can_packet.h"
#include "msg.h"
#include "idmodel.h"
#include "msgtypemodel.h"
#include "hugeqvector.h"

#include <QAbstractTableModel>
#include <QString>
#include <QVector>

class MainWindow;
class MsgProxyModel;

class MsgModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MsgModel(QObject *parent = Q_NULLPTR);
    ~MsgModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;


    void addMsg(Msg *msg);
    void clear();

    HugeQVector getMsgs() const;
    void setMsgs(const HugeQVector value);

    QByteArray parseToJSON();
    void parseFromJSON(QByteArray jsonFile);

    enum HeaderCols
    {
        COL_TIMESTAMP,
        COL_NAME,
        COL_MESSAGE,
        COL_NR_OF_COLS
    };
private:
//    QVector<Msg *> msgs;
    HugeQVector msgs;
    friend class MainWindow;
    friend class MsgProxyModel;

private slots:
    void messageReceived(CAN_PacketPtr ptr);


signals:
    void rowAppended(unsigned int rowNr);
    void rowsAdded(unsigned int nrOfRowsAdded);
    //void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
};

#endif // MSGMODEL_H
