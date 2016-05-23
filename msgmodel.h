#ifndef MSGMODEL_H
#define MSGMODEL_H

#include "msg.h"

#include <QAbstractTableModel>
#include <QString>
#include <QVector>

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

    QVector<Msg *> getMsgs() const;
    void setMsgs(const QVector<Msg *> &value);

    QByteArray parseToJSON();
    void parseFromJSON(QByteArray jsonFile);

private:
    QVector<Msg *> msgs;

signals:
    //void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);
};

#endif // MSGMODEL_H
