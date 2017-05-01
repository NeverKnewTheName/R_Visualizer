/**
 * @file SendMsgPackageModel.h
 * @author Christian Neuberger
 * @date 2017-04-15
 * 
 * @brief The default implementation for the #IMsgPackageModel
 */
#ifndef SENDMSGPACKAGEMODEL_H
#define SENDMSGPACKAGEMODEL_H

#include <QAbstractTableModel>

class ISendMsgPackageStore;

class IMsg;

/**
 * @brief The SendMsgPackageModel
 */
class SendMsgPackageModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum HeaderColumns
    {
        COL_MsgID,
        COL_MsgCode,
        COL_MsgData,
        COL_NR_OF_COLS
    };

    SendMsgPackageModel(
            ISendMsgPackageStore *sendMsgPackageStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~SendMsgPackageModel();

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    bool removeRows(int row, int count, const QModelIndex &parent) Q_DECL_OVERRIDE;

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:
    void sgnl_HasChanged();

public slots:
    void slt_msgAboutToBeInserted(
            const int index,
            const IMsg &msgToBePrepended
            );

    void slt_msgInserted(
            const int index,
            const IMsg &msgToBePrepended
            );

    void slt_msgAboutToBeRemoved(
            const int index,
            const int count
            );

    void slt_msgRemoved(
            const int index,
            const int count
            );

    void slt_AboutToBeCleared();

    void slt_Cleared();

private:
    void connectStore();

private:
    ISendMsgPackageStore *sendMsgPackageStore;
};

#endif /* SENDMSGPACKAGEMODEL_H */
