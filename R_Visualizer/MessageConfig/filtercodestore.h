#ifndef FILTERCODESTORE_H
#define FILTERCODESTORE_H

#include "msgtypemodel.h"

#include <QAbstractListModel>

class FilterCodeStore : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FilterCodeStore(MsgTypeModel *msgTypeModel, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    void addCode(unsigned int code);
    void addCode(QString &codeString);
    void removeCode(QModelIndex &index);

    bool containsCode(unsigned int code);

private:
    QModelIndex tempIndex;
    QVector<unsigned int> codeStore;
    MsgTypeModel *msgTypeModel;

signals:
    void internalModelChanged();
    void rowAdded(QModelIndex &index);

public slots:
};

#endif // FILTERCODESTORE_H
