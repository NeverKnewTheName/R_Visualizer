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

class FileParser;

#include "msg.h"
#include "IFileParsable.h"

class FilterIDStore : public QAbstractListModel, public IFileParsable
{
    Q_OBJECT
public:
    /**
     * \brief constructs a FilterIDStore
     * 
     * \param[in] idModel Data Model that holds the IDs (for autocompletion and coloring)
     */
    explicit FilterIDStore(QObject *parent = 0);

    /**
     * \brief Returns the current row count/number of elements in the store
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    /**
     * \brief Returns the data of the given index corresponding to the given role
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    /**
     * \brief returns the data for the header (of the table)
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    /**
     * \brief Sets the data for the given index to the given value corresponding to the given role
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    /**
     * \brief returns the ItemFlags for the given index
     */
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    /**
     * \brief Remove count rows starting from row
     */
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    /**
     * \brief Remove one row at row
     */
    void removeRow(int row, const QModelIndex &parent = QModelIndex() );

    /**
     * \brief Add an #MsgIDType to the #FilterIDStore
     */
    QModelIndex addID(const MsgIDType id);
    void removeID(const MsgIDType id);
    void removeID(const QModelIndex &index);

    const int size() const;
    const MsgIDType at(const int index) const;

    bool containsID(const MsgIDType id) const;

    void accept(FileParser *visitor);

signals:
    void internalModelChanged();
    //void rowAdded(unsigned int pos);
    void rowAdded(const QModelIndex &index);
public slots:

private:
    QVector<MsgIDType> idStore;
};

#endif // FILTERIDSTORE_H
