#ifndef MSGDELEGATE_H
#define MSGDELEGATE_H

#include <QAbstractItemDelegate>

class MsgDelegate// : public QAbstractItemDelegate
{
public:
    MsgDelegate(QWidget *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index);
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index);
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index);

};

#endif // MSGDELEGATE_H
