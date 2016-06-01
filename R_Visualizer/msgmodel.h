#ifndef MSGMODEL_H
#define MSGMODEL_H

#include "can_packet.h"
#include "msg.h"
#include "idmodel.h"
#include "msgtypemodel.h"

#include <QAbstractTableModel>
#include <QString>
#include <QVector>

class MainWindow;

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

//    void setIDModel(IDModel *idModel);
//    void setMsgTypeModel(MsgTypeModel *msgTypeModel);

    void addMsg(Msg *msg);
    void clear();

    QVector<Msg *> getMsgs() const;
    void setMsgs(const QVector<Msg *> value);

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
    QVector<Msg *> msgs;
//    IDModel *idModel;
//    MsgTypeModel *msgTypeModel;
    friend class MainWindow;

private slots:
    void messageReceived(CAN_PacketPtr ptr);


signals:
    //void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
};

#endif // MSGMODEL_H
