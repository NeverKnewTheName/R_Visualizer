#ifndef FILTERIDSTORE_H
#define FILTERIDSTORE_H

#include "idmodel.h"

#include <QAbstractListModel>
#include <QVector>
#include <QString>
#include <QItemSelectionModel>

class FilterIDStore : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FilterIDStore(IDModel *idModel, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    void addID(unsigned int id);
    void addID(QString &idString);
    void removeID(QModelIndex &index);

    bool containsID(unsigned int id);
signals:
    void internalModelChanged();
    //void rowAdded(unsigned int pos);
    void rowAdded(QModelIndex &index);
public slots:

private:
    QModelIndex tempIndex;
    QVector<unsigned int> idStore;
    IDModel *idModel;
};

#endif // FILTERIDSTORE_H
