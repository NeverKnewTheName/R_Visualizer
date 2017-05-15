#include "MsgDataDelegate.h"

#include "IMsgDataMappingManager.h"

#include "MsgDataLineEdit.h"
#include "IMsg.h"
#include "IMsgDataFormatter.h"

#include <QPainter>

MsgDataDelegate::MsgDataDelegate(
        IMsgDataMappingManager *msgDataMappingManager,
        QObject *parent
        ) :
    QStyledItemDelegate(parent),
    msgDataMappingManager(msgDataMappingManager)
{
    connect(
            msgDataMappingManager,
            &IMsgDataMappingManager::sgnl_MsgDataMappingManagerChanged,
            this,
            &MsgDataDelegate::slt_MappingHasChanged
           );
}

MsgDataDelegate::~MsgDataDelegate()
{
}

void MsgDataDelegate::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
    QStyledItemDelegate::paint(painter,option,index);
    const IMsg *msg = index.data(Qt::UserRole + 1).value<const IMsg *>();

    const QString &msgDataAsString = msgDataMappingManager->parseMsgDataToString(*msg);
    const QColor &msgDataAsColor = msgDataMappingManager->parseMsgDataToColor(*msg);

    painter->save();

    painter->setFont(option.font);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->fillRect(
            option.rect,
            (
                    (option.state & QStyle::State_Selected) ?
                        option.palette.highlight() :
                (option.features & QStyleOptionViewItem::Alternate) ?
                msgDataAsColor.darker(100) :
                msgDataAsColor
            )
            );

    painter->drawText(
            option.rect,
            Qt::TextWordWrap | Qt::TextExpandTabs | Qt::AlignLeft | Qt::AlignVCenter,
            msgDataAsString
            );

    painter->restore();
}

QSize MsgDataDelegate::sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
    //QStyledItemDelegate::sizeHint(option,index);
    const IMsg *msg = index.data(Qt::UserRole + 1).value<const IMsg *>();

    const QString &msgDataAsString = msgDataMappingManager->parseMsgDataToString(*msg);

    /* const QStyle *appStyle( QApplication::style() ); */
    QFont font(option.font);

    const QFontMetrics fontMetrics(font);

    return fontMetrics.boundingRect(
                option.rect,
                Qt::TextWordWrap | Qt::TextExpandTabs | Qt::AlignLeft | Qt::AlignVCenter,
                msgDataAsString
                ).marginsAdded(QMargins(0,4,0,4)).size();
}

QWidget *MsgDataDelegate::createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index
        ) const
{
    MsgDataLineEdit *msgDataLineEdit = new MsgDataLineEdit(parent);
    msgDataLineEdit->setStyleSheet("background-color:white;");

    connect(
            msgDataLineEdit,
            &MsgDataLineEdit::sgnl_EditingFinished,
            this,
            &MsgDataDelegate::slt_CommitAndCloseEditor
           );

    return msgDataLineEdit;
}

void MsgDataDelegate::setEditorData(
        QWidget *editor,
        const QModelIndex &index
        ) const
{
    MsgDataLineEdit *msgDataLineEdit = qobject_cast<MsgDataLineEdit*>(editor);
    if(msgDataLineEdit)
    {
        msgDataLineEdit->setMsgData(index.data(Qt::UserRole).value<MsgDataType>());
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor,index);
    }
}

void MsgDataDelegate::setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex &index
        ) const
{
    MsgDataLineEdit *msgDataLineEdit = qobject_cast<MsgDataLineEdit*>(editor);
    if(msgDataLineEdit)
    {
        const MsgDataType &msgDataToSet = msgDataLineEdit->getMsgData();

        model->setData(
                index,
                QVariant::fromValue<MsgDataType>(msgDataToSet),
                Qt::EditRole
                );
    }
    else
    {
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}

void MsgDataDelegate::slt_MappingHasChanged(
        const IMsgDataMappingManager &msgDataMappingManager
        )
{
}

void MsgDataDelegate::slt_CommitAndCloseEditor()
{
    QWidget *editor = qobject_cast<QWidget *>(sender());

    emit commitData(editor);
    emit closeEditor(editor);
}


void MsgDataDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
