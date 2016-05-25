#ifndef MSGTYPEMODEL_H
#define MSGTYPEMODEL_H

#include "msgtyperep.h"

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

    void add(unsigned int code, MsgTypeRep *msgTypeRep);
    void clear();

    QString getNameToCode(unsigned int code) const;
    QString getMessageToCode(unsigned int code) const;
    QColor getColorToCode(unsigned int code) const;

    QByteArray parseToJSON();
    void parseFromJSON(QByteArray jsonFile);

private:
    enum HeaderCols
    {
        COL_CODE,
        COL_MESSAGE,
        COL_COLOR,
        COL_NR_OF_COLS
    };
    //QVector<MsgTypeRep *> msgTypeStore;

    QVector<unsigned int> codeStore;
    QHash<unsigned int, MsgTypeRep *> msgTypePropStore;
};

#endif // MSGTYPEMODEL_H
