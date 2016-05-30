#ifndef MSGTYPEMODEL_H
#define MSGTYPEMODEL_H

#include "msgtyperep.h"
#include "msg.h"

#include <QAbstractTableModel>
#include <QVector>

class MsgTypeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MsgTypeModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void removeRow(int row, const QModelIndex &parent);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    void add(unsigned int code, MsgTypeRep *msgTypeRep);
    void clear();

    QString getNameToCode(unsigned int code) const;
    QString getMessageToCode(unsigned int code, MsgDataT &msg) const;
    QColor getColorToCode(unsigned int code) const;
    int getNrLinesToCode(unsigned int code);

    QByteArray parseToJSON();
    void parseFromJSON(QByteArray jsonFile);

    enum HeaderCols
    {
        COL_CODE,
        COL_CODENAME,
        COL_MESSAGEFORMAT,
        COL_COLOR,
        COL_NR_OF_COLS
    };
private:
    //QVector<MsgTypeRep *> msgTypeStore;

    QVector<unsigned int> codeStore;
    QHash<unsigned int, MsgTypeRep *> msgTypePropStore;


signals:
    void internalModelChanged();
};

#endif // MSGTYPEMODEL_H
