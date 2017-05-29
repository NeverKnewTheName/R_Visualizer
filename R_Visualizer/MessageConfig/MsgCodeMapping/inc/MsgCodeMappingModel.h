/**
 * @file MsgCodeMappingModel.h
 * @author Christian Neuberger
 * @date 2017-04-11
 * 
 * @brief The default model for MsgCode Mappings
 */
#ifndef MSGCODEMAPPINGMODEL_H
#define MSGCODEMAPPINGMODEL_H

#include "IMsgCodeMappingModel.h"
#include "IMsgCodeMappingStore.h"

#include "IMsgCodeMapping.h"

#include <QAbstractTableModel>
#include <QVector>

class FileParser;

/**
 * @addtogroup MsgCodeMappingGroup
 * 
 * @{
 */

/**
 * @brief The MsgCodeMappingModel
 */
class MsgCodeMappingModel :
    public QAbstractTableModel,
    public IMsgCodeMappingModel
{
    Q_OBJECT
public:
    enum HeaderCols
    {
        COL_Code,
        COL_Alias,
        COL_Color,
        COL_NR_OF_COLS
    };

    MsgCodeMappingModel(
            IMsgCodeMappingStore *msgCodeMappingStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeMappingModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant headerData(
            int section,
            Qt::Orientation orientation,
            int role = Qt::DisplayRole
            ) const Q_DECL_OVERRIDE;

    QVariant data(
            const QModelIndex &index,
            int role = Qt::DisplayRole
            ) const Q_DECL_OVERRIDE;

    bool setData(
            const QModelIndex &index,
            const QVariant &value,
            int role = Qt::EditRole
            ) Q_DECL_OVERRIDE;

    bool removeRows(
            int row,
            int count,
            const QModelIndex &parent = QModelIndex()
            ) Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(
            const QModelIndex &index
            ) const Q_DECL_OVERRIDE;

    ///////////////////////

    IMsgCodeMapping &getMsgCodeMappingToMsgCode(const MsgCodeType &msgCode);

    bool contains(const MsgCodeType &msgCode) const;
    bool contains(const IMsgCodeMapping &msgCodeMapping) const;

    void appendMsgCodeMapping(const IMsgCodeMapping &msgCodeMappingToAppend);
    void removeMsgCodeMapping(const MsgCodeType &relatedCode);

    void clear();

    void accept(FileParser *visitor);

signals:
    void sgnl_MappingHasChanged(const MsgCodeType &msgCode);
    void sgnl_AddMapping(
            const MsgCodeType &msgCode,
            const IMsgCodeMapping &mappingToAdd
            );

    void sgnl_RemoveMapping(
            const MsgCodeType &msgCode
            );

public slots:
    void slt_MsgCodeMappingAboutToBeAdded(const MsgCodeType &msgCode);
    void slt_MsgCodeMappingAdded(const MsgCodeType &msgCode);

    void slt_MsgCodeMappingAboutToBeRemoved(const MsgCodeType &msgCode);
    void slt_MsgCodeMappingRemoved(const MsgCodeType &msgCode);

    void slt_AboutToBeCleared();
    void slt_Cleared();

private:
    void connectToStore();


private:
    QVector<MsgCodeType> msgCodeStore;
    IMsgCodeMappingStore *msgCodeMappingStore;
};

/**
 * @}
 */

#endif /* MSGCODEMAPPINGMODEL_H */
