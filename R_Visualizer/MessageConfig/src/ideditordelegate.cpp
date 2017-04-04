#include "ideditordelegate.h"

//#include "idmodel.h"

#include <QColorDialog>
#include <QLineEdit>

IDEditorDelegate::IDEditorDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

void IDEditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QSize IDEditorDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *IDEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();
    if (col == IDModel::COL_NAME)
    {
        //NAME
        QLineEdit *textEdit = new QLineEdit(parent);
        connect(textEdit, &QLineEdit::editingFinished,
                this, &IDEditorDelegate::commitAndCloseEditor);
        return textEdit;
    }
    else if (col == IDModel::COL_COLOR) {
        //COLOR
        QColorDialog *colorEdit = new QColorDialog(parent);
        connect(colorEdit, &QColorDialog::finished,
                this, &IDEditorDelegate::commitAndCloseEditor);
        return colorEdit;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void IDEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();
    if (col == IDModel::COL_NAME) {
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        textEdit->setText(index.data(Qt::DisplayRole).value<QString>());
    }
    else if (col == IDModel::COL_COLOR)
    {
        //COLOR
        QColorDialog *colorEdit = qobject_cast<QColorDialog *>(editor);
        colorEdit->setCurrentColor(index.data(Qt::BackgroundRole).value<QColor>());
    }
    else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void IDEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();
    if (col == IDModel::COL_NAME) {
        //NAME
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        model->setData(index, textEdit->text());
    }
    else if (col == IDModel::COL_COLOR)
    {
        //COLOR
        QColorDialog *colorEdit = qobject_cast<QColorDialog *>(editor);
        model->setData(index, colorEdit->currentColor());
    }
    else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void IDEditorDelegate::commitAndCloseEditor()
{
    //CAN EIHTER BE A QLineEdit or a QColorDialog...
    QWidget *editor = qobject_cast<QColorDialog *>(sender());
    /* if(editor == Q_NULLPTR) */
    /* { */
    /*     //How did this happen?? */
    /*     return; */
    /* } */
    emit commitData(editor);
    emit closeEditor(editor);
}


