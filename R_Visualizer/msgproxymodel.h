#ifndef MSGPROXYMODEL_H
#define MSGPROXYMODEL_H

#include <QAbstractProxyModel>

#define VISIBLEROWS 100u

class MainWindow;

class MsgProxyModel : public QAbstractProxyModel
{
    Q_OBJECT

public:
    MsgProxyModel(QObject *parent = 0);
    MsgProxyModel(unsigned int visibleRows, QObject *parent = 0);
    ~MsgProxyModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const Q_DECL_OVERRIDE;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const Q_DECL_OVERRIDE;

signals:
    void rowFetched(int direction);
    void rowAppended();

private slots:
    void newEntryInSourceModel();
    void newEntryAppendedInSourceModel(QModelIndex &index);
    void continuousChange(bool state);
    void fetchRowsFromSource(int direction);

private:
    friend class MainWindow;

    bool continuous;
    unsigned int rowCntr;
    unsigned int visibleRows;
    unsigned int rowOffset;
    unsigned int scrollOffset;
};

#endif // MSGPROXYMODEL_H
