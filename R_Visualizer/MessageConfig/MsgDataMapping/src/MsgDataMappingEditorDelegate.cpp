#include "MsgDataMappingEditorDelegate.h"

#include "MsgDataMappingModel.h"

#include <QLineEdit>
#include <QColorDialog>

MsgDataMappingEditorDelegate::MsgDataMappingEditorDelegate(QObject *parent) :
    QItemDelegate(parent)
{

}


QWidget *MsgDataMappingEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgDataMappingModel::COL_FormatString:
    {
        QLineEdit *formatStringLineEdit = new QLineEdit(parent);
        connect(
                formatStringLineEdit,
                &QLineEdit::editingFinished,
                this,
                &MsgDataMappingEditorDelegate::commitAndCloseEditor
                );
        return formatStringLineEdit;
    }
        break;
    case MsgDataMappingModel::COL_Color:
    {
        QColorDialog *colorPicker = new QColorDialog(parent);
        connect(
                colorPicker,
                &QColorDialog::finished,
                this,
                &MsgDataMappingEditorDelegate::commitAndCloseEditor
                );
        return colorPicker;
    }
        break;
    default:
        return QItemDelegate::createEditor(parent,option,index);
    }
}

void MsgDataMappingEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgDataMappingModel::COL_FormatString:
        qobject_cast<QLineEdit*>(editor)->setText(index.data().toString());
        break;
    case MsgDataMappingModel::COL_Color:
        qobject_cast<QColorDialog*>(editor)->setCurrentColor(index.data().value<QColor>());
        break;
    default:
        QItemDelegate::setEditorData(editor,index);
    }
}

void MsgDataMappingEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    const int col = index.column();

    switch(col)
    {
    case MsgDataMappingModel::COL_FormatString:
    {
        QLineEdit *formatLineEdit = qobject_cast<QLineEdit*>(editor);
        model->setData(index, formatLineEdit->text(),Qt::EditRole);
    }
        break;
    case MsgDataMappingModel::COL_Color:
    {
        QColorDialog *colorPicker = qobject_cast<QColorDialog*>(editor);
        model->setData(index, QVariant::fromValue<QColor>(colorPicker->selectedColor()),Qt::EditRole);
    }
        break;
    default:
        QItemDelegate::setModelData(editor,model,index);
    }
}

void MsgDataMappingEditorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::updateEditorGeometry(editor,option,index);
}

void MsgDataMappingEditorDelegate::commitAndCloseEditor()
{
    QWidget *editor = qobject_cast<QWidget *>(sender());

    emit commitData(editor);
    emit closeEditor(editor);
}
