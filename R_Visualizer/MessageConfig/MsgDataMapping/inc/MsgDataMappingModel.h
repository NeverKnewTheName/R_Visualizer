/**
 * \file MsgDataMappingModel.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief The default implementation of the #IMsgDataMappingModel interface
 */
#ifndef MSGDATAMAPPINGMODEL_H
#define MSGDATAMAPPINGMODEL_H

#include "IMsgDataMappingModel.h"
#include "IMsgDataMappingStore.h"

#include "MsgDataMapping.h"

#include <QAbstractTableModel>
#include <QVector>

/**
 * @brief The MsgDataMappingModel
 */
class MsgDataMappingModel :
    public QAbstractTableModel,
    public IMsgDataMappingModel
{
    Q_OBJECT
public:
    /**
     * \brief Enumeration of the header columns for the #MsgDataMappingModel
     */
    enum HeaderCols
    {
        COL_ID,
        COL_Code,
        COL_FormatString,
        COL_Color,
        COL_NR_OF_COLS
    };

    MsgDataMappingModel(
            IMsgDataMappingStore *msgDataMappingStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgDataMappingModel();

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
    QVariant headerData(
            int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole
            ) const;

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

    // IMsgDataMappingModel Implementation //
    IMsgDataMapping &getMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );

    IMsgDataMapping &getMsgDataMapping(
            const MessageTypeIdentifier &msgType
            );

    bool contains(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            ) const;

    bool contains(
            const MessageTypeIdentifier &msgType
            ) const;

    bool contains(const IMsgDataMapping &msgDataMapping) const;

    void appendMsgDataMapping(const IMsgDataMapping &msgDataMappingToAppend);

    void removeMsgDataMapping(
            const MsgIDType &relatedMsgID,
            const MsgCodeType &relatedMsgCode
            );

    void removeMsgDataMapping(
            const MessageTypeIdentifier &msgType
            );

    void clear();

    // \ IMsgDataMappingModel Implementation \ //

    // IFileParsable Implementation //
    void accept(FileParser *visitor);
    // \ IFileParsable Implementation \ //

signals:
    void sgnl_MappingHasChanged(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );
    void sgnl_AddMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const IMsgDataMapping &mappingToAdd
            );

    void sgnl_RemoveMapping(
            const MsgIDType &msgID,
            const MsgCodeType &MsgCode
            );

public slots:
    void slt_MsgDataMappingAboutToBeAdded(
            const MsgIDType &msgID,
            const MsgCodeType &msgCodde
            );
    void slt_MsgDataMappingAdded(
            const MsgIDType &msgID,
            const MsgCodeType &msgCodde
            );

    void slt_MsgDataMappingAboutToBeRemoved(
            const MsgIDType &msgID,
            const MsgCodeType &msgCodde
            );
    void slt_MsgDataMappingRemoved(
            const MsgIDType &msgID,
            const MsgCodeType &msgCodde
            );

    void slt_AboutToBeCleared();
    void slt_Cleared();

private:
    void connectToStore();

private:
    QVector<MessageTypeIdentifier> msgIdentifierStore;
    IMsgDataMappingStore *msgDataMappingStore;
};

#endif /* MSGDATAMAPPINGMODEL_H */
