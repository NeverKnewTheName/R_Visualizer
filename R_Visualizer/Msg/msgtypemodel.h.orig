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

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    void add(const MsgTypeRep &msgTypeRep);
    void clear();

    QString getNameToCode(const quint8 code) const;
    quint8/*ToDO MsgCodeType*/ getCodeToName(const QString &name) const;
    QString getMessageToCode(const quint8/*ToDO MsgCodeType*/ code) const;
    QColor getColorToCode(const quint8 code) const;
    int getNrLinesToCode(const quint8/*ToDO MsgCodeType*/ code);

    QStringList getAllCodeNames() const;

    QByteArray parseToJSON() const;
    void parseFromJSON(const QByteArray &jsonFile);

    enum HeaderCols
    {
        COL_CODE,
        COL_CODENAME,
        COL_MESSAGEFORMAT,
        COL_COLOR,
        COL_NR_OF_COLS
    };

    const QPixmap &paintMsgTypeRep(const QRect &boundingRect, const quint8/*ToDO MsgCodeType*/ code);
private:
    QVector<quint8/*ToDO MsgCodeType*/> codeStore;
    QHash<quint8/*ToDO MsgCodeType*/, MsgTypeRep> msgTypePropStore;


signals:
    void internalModelChanged();
};

#endif // MSGTYPEMODEL_H
