#ifndef MSGPROXYMODEL_H
#define MSGPROXYMODEL_H

#include <QAbstractProxyModel>

class MainWindow;

class MsgProxyModel : public QAbstractProxyModel
{
    Q_OBJECT

public:
    MsgProxyModel(QObject *parent = 0);
    ~MsgProxyModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const Q_DECL_OVERRIDE;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const Q_DECL_OVERRIDE;

private slots:
    void newEntryInSourceModel();

private:
    friend class MainWindow;

    unsigned int rowCntr;
    unsigned int visRowCntr;
};

#endif // MSGPROXYMODEL_H
