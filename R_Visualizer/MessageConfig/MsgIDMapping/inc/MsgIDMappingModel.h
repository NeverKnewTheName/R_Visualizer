/**
 * \file MsgIDMappingModel.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief A model that manages message id mappings
 */
#ifndef MSGIDMAPPINGMODEL_H
#define MSGIDMAPPINGMODEL_H

#include "IMsgIDMappingModel.h"
#include "IMsgIDMappingStore.h"

#include "IMsgIDMapping.h"

#include <QAbstractTableModel>
#include <QVector>

class FileParser;

/**
 * \brief The MsgIDMappingModel
 */
class MsgIDMappingModel : public QAbstractTableModel, public IMsgIDMappingModel
{
    Q_OBJECT
public:
    /**
     * \brief Enumeration of the header columns for the #MsgIDMappingModel
     */
    enum HeaderCols
    {
        COL_ID, //!< Column in which the #MsgIDType is shown
        COL_Alias, //!< Column in which the name mapping is shown
        COL_Color, //!< Column in which the color mapping is shown
        COL_NR_OF_COLS //!< Number of header columns for the #IDModel
    };


    MsgIDMappingModel(
            IMsgIDMappingStore *msgIDMappingStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgIDMappingModel();

    //QAbstractItemModel Implementation//

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
     * \brief Returns the HeaderData for the given section, orientation, and
     * role
     * 
     * Per default the #IDModel has the following sections:
     * - The MsgId
     * - A plain-text alias
     * - A color representation
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role =
            Qt::DisplayRole) const;

    /**
     * \brief Retrieves data from the #IDModel for the given index according to
     * the given role
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /**
     * \brief Sets the data for a mapping at the given index with to the given
     * value according to the given role
     */

    bool setData(const QModelIndex &index, const QVariant &value, int role =
            Qt::EditRole);

    /* bool insertRows(int row, int count, const QModelIndex &parent = */
    /*         QModelIndex()) Q_DECL_OVERRIDE; */

    /**
     * \brief Removes count rows/mappings starting at row
     */
    bool removeRows(int row, int count, const QModelIndex &parent =
            QModelIndex()) Q_DECL_OVERRIDE;

    /**
     * \brief Returns the valid flags for a given index
     * 
     * Per default items in the #IDModel are editable, selectable, and
     * focuseable.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    // \ QAbstractItemModel Implementation \ //

    // IMsgIDMappingModel Implementation //
    /* IMsgIDMapping &getMsgIDMappingToMsgID(const MsgIDType &msgID) const; */
    IMsgIDMapping &getMsgIDMappingToMsgID(const MsgIDType &msgID);

    /* QString getAliasToMsgID(const MsgIDType msgID) const; */
    /* MsgIDType getMsgIDToAlias(const QString &alias) const; */
    /* QColor getColorToMsgID(const MsgIDType msgID) const; */
    /* QColor getColorToAlias(const QString &alias) const; */

    bool contains(const MsgIDType &msgID) const;
    bool contains(const IMsgIDMapping &msgIDMapping) const;

    void appendMsgIDMapping(const IMsgIDMapping &msgIDMappingToAppend);
    void removeMsgIDMapping(const MsgIDType &relatedMsgID);

    void clear();

    // \ IMsgIDMappingModel Implementation \ //

    // IFileParsable Implementation //
    void accept(FileParser *visitor);
    // \ IFileParsable Implementation \ //

signals:
    void sgnl_MappingHasChanged(const MsgIDType &msgID);
    void sgnl_AddMapping(
            const MsgIDType &msgID,
            const IMsgIDMapping &mappingToAdd
            );

    void sgnl_RemoveMapping(
            const MsgIDType &msgID
            );

public slots:
    void slt_MsgIDMappingAboutToBeAdded(const MsgIDType &msgID);
    void slt_MsgIDMappingAdded(const MsgIDType &msgID);

    void slt_MsgIDMappingAboutToBeRemoved(const MsgIDType &msgID);
    void slt_MsgIDMappingRemoved(const MsgIDType &msgID);

    void slt_AboutToBeCleared();
    void slt_Cleared();

private:
    void connectToStore();

private:
    QVector<MsgIDType> msgIDStore;
    IMsgIDMappingStore *msgIDMappingStore;
};

#endif /* MSGIDMAPPINGMODEL_H */
