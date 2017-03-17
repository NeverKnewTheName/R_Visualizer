/**
 * \file idmodel.h
 * \author Christian Neuberger
 * \date 2017-02-04
 * 
 * \brief Model to hold ID to name and color mapping for #Msg
 * 
 */
#ifndef IDMODEL_H
#define IDMODEL_H


#include <QAbstractTableModel>
#include <QVector>
#include <QHash>
#include <QColor>
#include <QStyleOptionViewItem>
#include <QCompleter>

class FileParser;

#include "msg.h"
#include "idrep.h"
#include "IFileParsable.h"

/**
 * \brief The #IDModel class provides a model to hold ID to name and color mappings for #Msg
 */
class IDModel : public QAbstractTableModel, public IFileParsable
{
    Q_OBJECT

public:
    /**
     * \brief Constructs an empty #IDModel
     */
    IDModel(QObject *parent = 0);
    /**
     * \brief Returns the current number of rows/mappings
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * \brief Returns the columns for a view to dispaly
     * 
     * The default colums include:
     * - The MsgID
     * - An associated name
     * - An associated color
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * \brief Retrieves data from the #IDModel for the given index according to the given role
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    /**
     * \brief Sets the data for a mapping at the given index with to the given value according to the given role
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    /**
     * \brief Returns the HeaderData for the given section, orientation, and role
     * 
     * Per default the #IDModel has the following sections:
     * - The MsgId
     * - A Name mapping
     * - A Color mapping
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    /**
     * \brief Removes count rows/mappings starting at row
     */
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    /**
     * \brief Removes a single row/mapping at row
     */
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    /**
     * \brief Returns the valid flags for a given index
     * 
     * Per default items in the #IDModel are editable, selectable, and focuseable.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    /**
     * \brief Adds a #IDRep mapping to the #IDModel
     */
    void add(const IDRep &idRep);

    /**
     * \brief Returns the #IDRep that is stored in the model for the given id
     * 
     * Queries the model for the provided id. 
     * If there is an existing #IDRep associated with the id in the model,
     * it is returned.
     * If there is no existing #IDRep associated with the id in the model,
     * a new default #IDRep for that id is returned.
     */
    IDRep getIDRepToID(const MsgIDType id) const;
    /**
     * \brief Clears the whole #IDModel for a fresh start
     */
    void clear();

    const int size() const;

    const IDRep &at(const int index) const;

    /**
     * \brief Returns whether a given #MsgIDType is contained in the #IDModel
     */
    bool contains(const MsgIDType MsgID) const;
    /**
     * \brief Returns the name mapping to a given #MsgIDType
     */
    QString getNameToID(const MsgIDType id) const;
    /**
     * \brief Returns the #MsgIDType associated with a given name
     */
    MsgIDType getIDToName(const QString &name) const;
    /**
     * \brief Returns the color mapping to the given #MsgIDType
     */
    QColor getColorToID(const MsgIDType id) const;

//    QHash<int, IDRep *> getIdPropStore() const;
//    void setIdPropStore(const QHash<int, IDRep *> &value);

    /**
     * \brief Returns all names that are contained in the #IDModel
     */
    QStringList getAllIDNames() const;

    /**
     * \brief Parses the contents of the #IDModel to a JSON format QByteArray
     */
    QByteArray ParseToJson() const;
    /**
     * \brief Parses the contents of a QByteArray that was previously saved by the #IDModel into the #IDModel
     */
    void ParseFromJson(const QByteArray &jsonFile);

    /**
     * \brief Enumeration of the header columns for the #IDModel
     */
    enum HeaderCols
    {
        COL_ID, //!< Column in which the #MsgIDType is shown
        COL_NAME, //!< Column in which the name mapping is shown
        COL_COLOR, //!< Column in which the color mapping is shown
        COL_NR_OF_COLS //!< Number of header columns for the #IDModel
    };

    /**
     * \brief Paint a #Msg according to its #MsgIDType and the mappings contained in this #IDModel
     */
    void paintID(QPainter *painter, const QStyleOptionViewItem &option, const MsgIDType id) const;

    QCompleter *createIDCompleter(QObject *parent = Q_NULLPTR) const;

    void accept(FileParser *visitor);

private:
    /**
     * \brief QVector containing all stored #MsgIDTypes for which mappings exist in the #IDModel
     */
    QVector<MsgIDType> idStore; //ToDO MsgIDType
    /**
     * \brief QHash that contains the respective #MsgIDType to #IDRep mappings
     */
    QHash<MsgIDType, IDRep> idPropStore; //ToDO MsgIDType

signals:
    /**
     * \brief The #internalModelChanged signal is emitted every time the data in the #IDModel changes
     */
    void internalModelChanged();
    void sgnl_IDRepAdded(const IDRep &newIDRep);
    void sgnl_IDRepUpdated(const IDRep &updatedIDRep);
    void sgnl_IDRepRemoved(const MsgIDType relatedID);
};

#endif // IDMODEL_H
