#ifndef IDMODEL_H
#define IDMODEL_H

#include "idrep.h"

#include <QAbstractTableModel>
#include <QVector>
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

    void add(IDRep *idRep);
    void clear();

    QString getNameToID(int id);
    QColor getColorToID(int id);

    QByteArray parseToJSON();
    void parseFromJSON(QByteArray jsonFile);

private:
    enum HeaderCols
    {
        COL_ID,
        COL_NAME,
        COL_COLOR,
        COL_NR_OF_COLS
    };

    QVector<IDRep *> idStore;

};

#endif // IDMODEL_H
