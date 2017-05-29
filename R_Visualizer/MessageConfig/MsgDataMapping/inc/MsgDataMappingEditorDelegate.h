#ifndef MSGDATAMAPPINGEDITORDELEGATE_H
#define MSGDATAMAPPINGEDITORDELEGATE_H

#include <QItemDelegate>

class MsgDataMappingEditorDelegate : public QItemDelegate
{
public:
    MsgDataMappingEditorDelegate(QObject *parent = Q_NULLPTR);

    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private slots:
    void commitAndCloseEditor();
};

#endif // MSGDATAMAPPINGEDITORDELEGATE_H
