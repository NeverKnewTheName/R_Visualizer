#include "msgtypeeditordelegate.h"

#include "msgtypemodel.h"

#include <QColorDialog>
#include <QLineEdit>

MsgTypeEditorDelegate::MsgTypeEditorDelegate( QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

void MsgTypeEditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QSize MsgTypeEditorDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *MsgTypeEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();
    if (col == MsgTypeModel::COL_MESSAGE)
    {
        //NAME
        QLineEdit *textEdit = new QLineEdit(parent);
        connect(textEdit, &QLineEdit::editingFinished,
                this, &MsgTypeEditorDelegate::commitAndCloseEditor);
        return textEdit;
    }
    else if (col == MsgTypeModel::COL_COLOR) {
        //COLOR
        QColorDialog *colorEdit = new QColorDialog(parent);
        connect(colorEdit, &QColorDialog::finished,
                this, &MsgTypeEditorDelegate::commitAndCloseEditor);
        return colorEdit;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void MsgTypeEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();
    if (col == MsgTypeModel::COL_MESSAGE) {
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        textEdit->setText(index.model()->data(index, Qt::DisplayRole).value<QString>());
    }
    else if (col == MsgTypeModel::COL_COLOR)
    {
        //COLOR
        QColorDialog *colorEdit = qobject_cast<QColorDialog *>(editor);
        colorEdit->setCurrentColor(index.model()->data(index, Qt::BackgroundRole).value<QColor>());
    }
    else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void MsgTypeEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();
    if (col == MsgTypeModel::COL_MESSAGE) {
        //NAME
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        model->setData(index, textEdit->text());
    }
    else if (col == MsgTypeModel::COL_COLOR)
    {
        //COLOR
        QColorDialog *colorEdit = qobject_cast<QColorDialog *>(editor);
        model->setData(index, colorEdit->currentColor());
    }
    else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void MsgTypeEditorDelegate::commitAndCloseEditor()
{
    QColorDialog *editor = qobject_cast<QColorDialog *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
