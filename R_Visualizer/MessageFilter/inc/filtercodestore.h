/**
 * \file filtercodestore.h
 * \author Christian Neuberger
 * \date
 * 
 * \brief The Store that holds codes to filter for
 */
#ifndef FILTERCODESTORE_H
#define FILTERCODESTORE_H

#include <QAbstractListModel>
#include <QVector>
#include <QString>

class FileParser;

#include "msg.h"
#include "fileparsable.h"

class FilterCodeStore : public QAbstractListModel, public FileParsable
{
    Q_OBJECT
public:
    /**
     * \brief constructs a FilterCodeStore 
     * 
     * \param[in] msgTypeModel Data Model that holds the MsgTypes (for autocompletion and coloring)
     */
    explicit FilterCodeStore(QObject *parent = 0);

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
     * \brief remove the row at row
     */
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    /**
     * \brief Appends the given code to the store
     */
    void addCode(const MsgCodeType code);
    /**
     * \brief appends the given codeString to the store
     */
    void addCode(const QString &codeString);
    /**
     * \brief removes the code associated with the given index
     */
    void removeCode(const QModelIndex &index);

    /**
     * \brief verifies whether the store contains the given code
     */
    bool containsCode(const MsgCodeType code) const;

    const int size() const;
    const MsgCodeType at(const int index) const;

    void accept(FileParser *visitor);

private:
    QVector<MsgCodeType> codeStore;

signals:
    void internalModelChanged();
    /**
     * \brief this signal is emitted when a new row is appended to the store
     * 
     * A new row is appneded when a new code is added to the store
     * 
     * \note The parameter index contains the current index of the newly added row.
     */
    void rowAdded(const QModelIndex &index);

public slots:
};

#endif // FILTERCODESTORE_H
