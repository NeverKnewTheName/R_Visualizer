#include "filtermsgtypedelegate.h"

#include <QLineEdit>
#include <QCompleter>
#include <QPainter>

FilterMsgTypeDelegate::FilterMsgTypeDelegate(MsgTypeModel *msgTypeModel, QWidget *parent) :
    QStyledItemDelegate(parent),
    msgTypeModel(msgTypeModel)
{

}

void FilterMsgTypeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    QColor background = option.palette.color(
                option.palette.currentColorGroup(),
                (option.features & QStyleOptionViewItem::Alternate) ? QPalette::AlternateBase : QPalette::Base);

    int code = index.model()->data(index, Qt::DisplayRole).value<int>();
    QColor itemBackground(this->msgTypeModel->getColorToCode(code));
    if(itemBackground.isValid())
    {
        if(option.features & QStyleOptionViewItem::Alternate)
        {
            background = itemBackground.darker(110);
        }
        else
        {
            background = itemBackground;
        }
    }

    if(option.state & QStyle::State_Selected)
    {
        background = option.palette.color(option.palette.currentColorGroup(), QPalette::Highlight);
    }
    painter->fillRect(option.rect, background);


    QString name = this->msgTypeModel->getNameToCode(code);
    if(name.isEmpty())
    {
        // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
        name =  QString("0x%1").arg(code/*decimal*/, 2/*width*/, 16/*base*/, QLatin1Char( '0' )/*fill character*/); // convert integer to string with hexadecimal representation (preceding '0x' inlcuded)
    }

    painter->drawText(option.rect, Qt::AlignLeft/* | Qt::AlignBottom*/, name);
}

QSize FilterMsgTypeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *FilterMsgTypeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();
    if (col == 0)
    {
        //NAME
        QLineEdit *textEdit = new QLineEdit(parent);

        QCompleter *completer = new QCompleter(msgTypeModel->getAllCodeNames(), textEdit);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        textEdit->setCompleter(completer);

        connect(textEdit, &QLineEdit::editingFinished,
                this, &FilterMsgTypeDelegate::commitAndCloseEditor);
        return textEdit;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void FilterMsgTypeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();
    if (col == 0) {
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        textEdit->setText(index.model()->data(index, Qt::DisplayRole).value<QString>());
    }
    else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void FilterMsgTypeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();
    if (col == 0) {
        //NAME
        QLineEdit *textEdit = qobject_cast<QLineEdit *>(editor);
        QString editorContent = textEdit->text();
        bool conversionOK;
        unsigned int retrievedCode = editorContent.toInt(&conversionOK, (editorContent.startsWith("0x")) ? 16 : 0);

        if(!conversionOK)
        {
            retrievedCode = msgTypeModel->getCodeToName(editorContent);
        }
        model->setData(index, retrievedCode);
    }
    else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void FilterMsgTypeDelegate::commitAndCloseEditor()
{
    QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}


