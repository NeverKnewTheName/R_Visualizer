/**
 * \file filteridstore.h
 * \author Christian Neuberger
 * \date
 * 
 * \brief The Store that holds ids to filter for
 */
#ifndef FILTERIDSTORE_H
#define FILTERIDSTORE_H

#include <QAbstractListModel>
#include <QVector>
#include <QString>

class FilterIDStore : public QAbstractListModel
{
    Q_OBJECT
public:
    /**
     * \brief constructs a FilterIDStore
     * 
     * \param[in] idModel Data Model that holds the IDs (for autocompletion and coloring)
     */
    explicit FilterIDStore( const IDModel &idModel, QObject *parent = 0);

    /**
     * \brief Returns the current row count/number of elements in the store
     */
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    /**
     * \brief Returns the data of the given index corresponding to the given role
     */
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    /**
     * \brief returns the data for the header (of the table)
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    /**
     * \brief Sets the data for the given index to the given value corresponding to the given role
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
    /**
     * \brief returns the ItemFlags for the given index
     */
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    /**
     * \brief Remove count rows starting from row
     */
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    void removeRow(int row, const QModelIndex &parent = QModelIndex() );

    QModelIndex addID(const MsgIDType id);
    void removeID(QModelIndex &index);

    bool containsID(const MsgIDType id) const;
signals:
    void internalModelChanged();
    //void rowAdded(unsigned int pos);
    void rowAdded(QModelIndex &index);
public slots:

private:
    QVector<MsgIDType> idStore;
};

#endif // FILTERIDSTORE_H
