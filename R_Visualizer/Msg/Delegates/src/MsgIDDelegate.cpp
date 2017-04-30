#include "MsgIDDelegate.h"

#include "IMsgIDMappingManager.h"
#include "MsgIDMappingModel.h"

#include "MsgIDLineEdit.h"

#include <QPainter>
#include <QFont>
#include <QFontMetrics>

#include <QLineEdit>
#include <QDebug>

MsgIDDelegate::MsgIDDelegate(
        IMsgIDMappingManager *msgIDMappingManager,
        QObject *parent
        ) :
    QStyledItemDelegate(parent),
    msgIDMappingManager(msgIDMappingManager)
{
    connect(
            msgIDMappingManager,
            &IMsgIDMappingManager::sgnl_MsgIDMappingManagerChanged,
            this,
            &MsgIDDelegate::slt_MappingHasChanged
           );
}

MsgIDDelegate::~MsgIDDelegate()
{
}

void MsgIDDelegate::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
    const MsgIDType &msgID = index.data(Qt::UserRole).value<MsgIDType>();

    QString alias = msgIDMappingManager->getAliasToMsgID(msgID);

    if(alias.isEmpty())
    {
        alias = static_cast<QString>(msgID);
    }

    const QColor &colorRep = msgIDMappingManager->getColorToMsgID(msgID);

    painter->save();

    painter->setFont(option.font);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->fillRect(
            option.rect,
            (
                    (option.state & QStyle::State_Selected) ?
                        option.palette.highlight() :
                (option.features & QStyleOptionViewItem::Alternate) ?
                colorRep.darker(100) :
                colorRep
            )
            );

    painter->drawText(
            option.rect,
            Qt::TextWordWrap | Qt::AlignLeft,
            alias
            );

    painter->restore();
}

QSize MsgIDDelegate::sizeHint(
        const QStyleOptionViewItem &option,
        const QModelIndex &index
        ) const
{
    const MsgIDType &msgID = index.data(Qt::UserRole).value<MsgIDType>();

    QString alias = msgIDMappingManager->getAliasToMsgID(msgID);

    if(alias.isEmpty())
    {
        alias = static_cast<QString>(msgID);
    }

    /* const QStyle *appStyle( QApplication::style() ); */
    QFont font(option.font);

    const QFontMetrics fontMetrics(font);

    return fontMetrics.size(Qt::TextWordWrap, alias);
    /* const int aliasWidth = fontMetrics.width(alias); */
    /* const int aliasHeight = fontMetrics; */

    /* return QSize(aliasWidth, aliasHeight); */
}

QWidget *MsgIDDelegate::createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index
        ) const
{
    //return new QLineEdit(parent);

    MsgIDLineEdit *msgIDLineEdit = new MsgIDLineEdit(parent);
    msgIDLineEdit->setMappingManager(msgIDMappingManager);

    qDebug() << __PRETTY_FUNCTION__;

    connect(
            msgIDLineEdit,
            &MsgIDLineEdit::sgnl_EditingFinished,
            this,
            &MsgIDDelegate::slt_CommitAndCloseEditor
           );

    MsgIDMappingModel *msgIDMappingModel = new MsgIDMappingModel(
            msgIDMappingManager->getStore(),
            qobject_cast<QObject*>(msgIDLineEdit)
            );
    QCompleter *idAliasCompleter = new QCompleter(qobject_cast<QObject*>(msgIDLineEdit));

    idAliasCompleter->setModel(msgIDMappingModel);
    idAliasCompleter->setCompletionColumn(MsgIDMappingModel::COL_Alias);
    idAliasCompleter->setCompletionRole(Qt::DisplayRole);
    idAliasCompleter->setModelSorting(
            QCompleter::CaseInsensitivelySortedModel
            );
    idAliasCompleter->setCaseSensitivity(Qt::CaseInsensitive);

    msgIDLineEdit->setCompleter(idAliasCompleter);


    return msgIDLineEdit;
}

void MsgIDDelegate::setEditorData(
        QWidget *editor,
        const QModelIndex &index
        ) const
{
    MsgIDLineEdit *msgIDLineEdit = qobject_cast<MsgIDLineEdit*>(editor);
    if(msgIDLineEdit)
    {
        //QSignalBlocker editorSignalBlocker(msgIDLineEdit);
        //msgIDLineEdit->setMsgID(index.data(Qt::UserRole).value<MsgIDType>());
        qDebug() << __PRETTY_FUNCTION__;
        msgIDLineEdit->setMsgID(MsgIDType(0x100));
        msgIDLineEdit->setFocus();
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor,index);
    }
}

void MsgIDDelegate::setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex &index
        ) const
{
    MsgIDLineEdit *msgIDLineEdit = qobject_cast<MsgIDLineEdit*>(editor);
    if(msgIDLineEdit)
    {
        qDebug() << __PRETTY_FUNCTION__;
        const MsgIDType &msgIDToSet = msgIDLineEdit->getMsgID();

        model->setData(
                index,
                msgIDToSet,
                Qt::EditRole
                );
    }
    else
    {
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}

void MsgIDDelegate::slt_MappingHasChanged(
        const IMsgIDMappingManager &msgIDMappingManager
        )
{
}

void MsgIDDelegate::slt_CommitAndCloseEditor()
{
    qDebug() << __PRETTY_FUNCTION__;
    MsgIDLineEdit *editor = qobject_cast<MsgIDLineEdit *>(sender());

    emit commitData(editor);
    emit closeEditor(editor);
}


void MsgIDDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << editor->geometry();
    editor->setGeometry(option.rect);
}
