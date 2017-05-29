/**
 * @file filtermsgtypedelegate.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief A Delegate for message codes for the message code filter widget
 */
#ifndef FILTERMSGTYPEDELEGATE_H
#define FILTERMSGTYPEDELEGATE_H

#include <QStyledItemDelegate>
class MessageConfig;

class FilterMsgTypeDelegate : public QStyledItemDelegate
{
public:
    FilterMsgTypeDelegate(const MessageConfig *msgConfig, QWidget *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
    const MessageConfig *msgConfig;

private slots:
    void commitAndCloseEditor();
};

#endif // FILTERMSGTYPEDELEGATE_H
