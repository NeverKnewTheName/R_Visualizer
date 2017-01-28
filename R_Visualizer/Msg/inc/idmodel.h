#ifndef IDMODEL_H
#define IDMODEL_H

#include "msg.h"
#include "idrep.h"

#include <QAbstractTableModel>
#include <QVector>
#include <QHash>
#include <QColor>
#include <QStyleOptionViewItem>

class IDModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    IDModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    void add(const IDRep &idRep);
    void clear();

    bool contains(const MsgIDType MsgID) const;
    QString getNameToID(const MsgIDType id) const;
    MsgIDType getIDToName(const QString &name) const;
    QColor getColorToID(const MsgIDType id) const;

//    QHash<int, IDRep *> getIdPropStore() const;
//    void setIdPropStore(const QHash<int, IDRep *> &value);

    QStringList getAllIDNames() const;

    QByteArray parseToJSON() const;
    void parseFromJSON(const QByteArray &jsonFile);

    enum HeaderCols
    {
        COL_ID,
        COL_NAME,
        COL_COLOR,
        COL_NR_OF_COLS
    };

    void paintID(QPainter *painter, const QStyleOptionViewItem &option, const MsgIDType id) const;

private:
    QVector<MsgIDType> idStore; //ToDO MsgIDType
    QHash<MsgIDType, IDRep> idPropStore; //ToDO MsgIDType

signals:
    void internalModelChanged();

};

#endif // IDMODEL_H
