/**
 * @file filteriddelegate.h
 * @author Christian Neuberger
 * @date 2017-03-23
 * 
 * @brief A delegate for message ids in the message id filter
 */
#ifndef FILTERIDDELEGATE_H
#define FILTERIDDELEGATE_H

#include "idmodel.h"

#include <QStyledItemDelegate>
#include <QStringList>


/**
 * \brief The FilterIDDelegate
 */
class FilterIDDelegate : public QStyledItemDelegate
{
public:
    FilterIDDelegate(const MessageConfig *msgConfig, QWidget *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    const MessageConfig *msgConfig;
    QStringList availableIDNames;

private slots:
    void commitAndCloseEditor();
    void addIDName(QString &idName);
    void removeIDName(QString &idName);
};

#endif // FILTERIDDELEGATE_H
