#ifndef MSGDELEGATE_H
#define MSGDELEGATE_H

#include "msgtypemodel.h"
#include "idmodel.h"

#include <QStyledItemDelegate>


class MsgDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    MsgDelegate(MsgTypeModel &msgTypeModel, IDModel &idModel, QWidget *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

//    void setMsgTypeModel(MsgTypeModel *msgTypeModel);
//    void setIDModel(IDModel *idModel);

private:
    MsgTypeModel &msgTypeModel;
    IDModel &idModel;

private slots:
    void commitAndCloseEditor();

};

#endif // MSGDELEGATE_H
