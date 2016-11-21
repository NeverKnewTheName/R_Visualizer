#ifndef MSGTYPEMODEL_H
#define MSGTYPEMODEL_H

#include "msg.h"
#include "msgtyperep.h"

#include <QAbstractTableModel>
#include <QVector>
#include <QStyleOptionViewItem>

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

    QString getNameToCode(const MsgCodeType code) const;
    quint8/*ToDO MsgCodeType*/ getCodeToName(const QString &name) const;
    QString getMessageToCode(const MsgCodeType/*ToDO MsgCodeType*/ code) const;
    QColor getColorToCode(const MsgCodeType code) const;
    int getNrLinesToCode(const MsgCodeType/*ToDO MsgCodeType*/ code);

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

    void paintMsgTypeRep(const QRect &rect, QPixmap &destPixMap, const MsgCodeType/*ToDO MsgCodeType*/ code);
private:
    QVector<MsgCodeType/*ToDO MsgCodeType*/> codeStore;
    QHash<MsgCodeType/*ToDO MsgCodeType*/, MsgTypeRep> msgTypePropStore;

signals:
    void internalModelChanged();
};

#endif // MSGTYPEMODEL_H
