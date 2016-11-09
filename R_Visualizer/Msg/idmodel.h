#ifndef IDMODEL_H
#define IDMODEL_H

#include "idrep.h"

#include <QAbstractTableModel>
#include <QVector>
#include <QHash>
#include <QColor>

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

    void add(int id, IDRep *idRep);
    void clear();

    QString getNameToID(int id);
    unsigned int getIDToName(const QString &name) const;
    QColor getColorToID(int id);

    QHash<int, IDRep *> getIdPropStore() const;
    void setIdPropStore(const QHash<int, IDRep *> &value);

    QStringList getAllIDNames() const;

    QByteArray parseToJSON() const;
    void parseFromJSON(QByteArray jsonFile);

    enum HeaderCols
    {
        COL_ID,
        COL_NAME,
        COL_COLOR,
        COL_NR_OF_COLS
    };

private:
    QVector<int> idStore;
    QHash<int, IDRep *> idPropStore;

signals:
    void internalModelChanged();

};

#endif // IDMODEL_H
