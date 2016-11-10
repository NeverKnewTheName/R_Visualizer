#ifndef MSGMODEL_H
#define MSGMODEL_H

class Msg;
class IDModel;
class MsgTypeModel;

//#include "msg.h"
//#include "idmodel.h"
//#include "msgtypemodel.h"
#include "hugeqvector.h"

#include <QAbstractTableModel>
#include <QString>

class MainWindow;

class MsgModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MsgModel(QObject *parent = Q_NULLPTR);
    ~MsgModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    void addMsg(Msg *msg);
    void clear();

    HugeQVector<Msg> getMsgs() const;
    void setMsgs(const HugeQVector<Msg> value);

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
    HugeQVector<Msg> msgs;
    friend class MainWindow;

private slots:
    void messageReceived(Msg *msg);

signals:
    void rowAppended(unsigned int rowNr);
    void rowsAdded(unsigned int nrOfRowsAdded);
};

#endif // MSGMODEL_H
