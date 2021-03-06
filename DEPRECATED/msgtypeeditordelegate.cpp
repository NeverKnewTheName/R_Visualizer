#include "msgtypeeditordelegate.h"

#include "msgtypemodel.h"
#include "msgtypeformatterdialog.h"

#include <QColorDialog>
#include <QLineEdit>

#include <QDebug>

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
    qDebug() << __PRETTY_FUNCTION__;
    if(!index.isValid())
        return QStyledItemDelegate::createEditor(parent, option, index);

    int col = index.column();
    if (col == MsgTypeModel::COL_CODENAME)
    {
        //NAME
        QLineEdit *textEdit = new QLineEdit(parent);
        textEdit->setText(qvariant_cast<QString>(index.data()));
        connect(textEdit, &QLineEdit::editingFinished,
                this, &MsgTypeEditorDelegate::commitAndCloseEditor);
        return textEdit;
    }
    else if (col == MsgTypeModel::COL_MESSAGEFORMAT )
    {
        //QLineEdit *textEdit = new QLineEdit(parent);
        MsgTypeFormatterDialog *formatEdit = new MsgTypeFormatterDialog(parent);
        connect(formatEdit, &MsgTypeFormatterDialog::finished,
                this, &MsgTypeEditorDelegate::commitAndCloseEditor);
        return formatEdit;
    }
    else if (col == MsgTypeModel::COL_COLOR) {
        //COLOR
        QColorDialog *colorEdit = new QColorDialog(parent);
        connect(colorEdit, &QColorDialog::finished,
                this, &MsgTypeEditorDelegate::commitAndCloseEditor);
        return colorEdit;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void MsgTypeEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << __PRETTY_FUNCTION__;
    if(!index.isValid())
        return;

    int col = index.column();
    if (col == MsgTypeModel::COL_CODENAME) {
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        QString currentCodeName = index.data(Qt::DisplayRole).value<QString>();
        textEdit->setText(currentCodeName);
        textEdit->update();
    }
    if (col == MsgTypeModel::COL_MESSAGEFORMAT) {
        //QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        MsgTypeFormatterDialog *formatEdit = qobject_cast<MsgTypeFormatterDialog *>(editor);
        formatEdit->setFormatString(index.data(Qt::DisplayRole).value<QString>());
    }
    else if (col == MsgTypeModel::COL_COLOR)
    {
        //COLOR
        QColorDialog *colorEdit = qobject_cast<QColorDialog *>(editor);
        colorEdit->setCurrentColor(index.data(Qt::BackgroundRole).value<QColor>());
    }
    else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void MsgTypeEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug() << __PRETTY_FUNCTION__;
    if(!index.isValid())
        return;
    int col = index.column();
    if (col == MsgTypeModel::COL_CODENAME) {
        //NAME
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        model->setData(index, textEdit->text());
    }
    else if (col == MsgTypeModel::COL_MESSAGEFORMAT)
    {
        MsgTypeFormatterDialog *formatEdit = qobject_cast<MsgTypeFormatterDialog *>(editor);
        model->setData(index, formatEdit->getFormatString());
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
    QWidget *editor = qobject_cast<QWidget *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
