#include "MsgDataMappingStore.h"

#include "fileparser.h"

MsgDataMappingStore::MsgDataMappingStore(
        QObject *parent
        ) :
    IMsgDataMappingStore(parent)
{
    connect(
            this,
            &IMsgDataMappingStore::sgnl_Cleared,
            this,
            &IMsgDataMappingStore::sgnl_MappingHasChanged
            );
    connect(
            this,
            &IMsgDataMappingStore::sgnl_MsgDataMappingAdded,
            this,
            &IMsgDataMappingStore::sgnl_MappingHasChanged
            );
    connect(
            this,
            &IMsgDataMappingStore::sgnl_MsgDataMappingRemoved,
            this,
            &IMsgDataMappingStore::sgnl_MappingHasChanged
            );
}

MsgDataMappingStore::~MsgDataMappingStore()
{
}

QSharedPointer<IMsgDataFormatter> MsgDataMappingStore::getMsgDataFormatter(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        ) const
{
    return getMsgDataFormatter(MessageTypeIdentifier(msgID,msgCode));
}

QSharedPointer<IMsgDataFormatter> MsgDataMappingStore::getMsgDataFormatter(
        const MessageTypeIdentifier &msgType
        ) const
{
    return msgDataMappingStore[msgType].getMsgDataFormatter();
}

IMsgDataMapping &MsgDataMappingStore::getMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    return getMsgDataMapping(MessageTypeIdentifier(msgID,msgCode));
}

IMsgDataMapping &MsgDataMappingStore::getMsgDataMapping(
        const MessageTypeIdentifier &msgType
        )
{
    return msgDataMappingStore[msgType];
}

bool MsgDataMappingStore::contains(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        ) const
{
    return contains(MessageTypeIdentifier(msgID,msgCode));
}

bool MsgDataMappingStore::contains(
        const MessageTypeIdentifier &msgType
        ) const
{
    return msgDataMappingStore.contains(msgType);
}

bool MsgDataMappingStore::contains(
        const IMsgDataMapping &msgDataMapping
    ) const
{
    const MsgIDType &msgID = msgDataMapping.getMsgID();
    const MsgCodeType &msgCode = msgDataMapping.getMsgCode();

    return contains(MessageTypeIdentifier(msgID,msgCode));
}

IMsgDataMapping &MsgDataMappingStore::addMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode,
        const IMsgDataMapping &msgDataMapping
        )
{
    return addMsgDataMapping(
            MessageTypeIdentifier(msgID,msgCode),
            msgDataMapping
            );
}

IMsgDataMapping &MsgDataMappingStore::addMsgDataMapping(
        const MessageTypeIdentifier &msgType,
        const IMsgDataMapping &msgDataMapping
        )
{
    emit sgnl_MsgDataMappingAboutToBeAdded(
            msgType.getID(),
            msgType.getCode()
            );
    msgDataMappingStore.insert(
            msgType,
            dynamic_cast<const MsgDataMapping&>(msgDataMapping)
            );

    emit sgnl_MsgDataMappingAdded(
            msgType.getID(),
            msgType.getCode()
            );

    return msgDataMappingStore[msgType];
}

void MsgDataMappingStore::removeMsgDataMapping(
        const MsgIDType &msgID,
        const MsgCodeType &msgCode
        )
{
    removeMsgDataMapping(MessageTypeIdentifier(msgID,msgCode));
}

void MsgDataMappingStore::removeMsgDataMapping(
        const MessageTypeIdentifier &msgType
        )
{
    emit sgnl_MsgDataMappingAboutToBeRemoved(
            msgType.getID(),
            msgType.getCode()
            );
    msgDataMappingStore.remove(msgType);

    emit sgnl_MsgDataMappingRemoved(
            msgType.getID(),
            msgType.getCode()
            );
}

void MsgDataMappingStore::clear()
{
    emit sgnl_AboutToBeCleared();
    msgDataMappingStore.clear();
    emit sgnl_Cleared();
}

void MsgDataMappingStore::accept(FileParser *visitor)
{
    visitor->visit(*this);
}

QVector<MessageTypeIdentifier> MsgDataMappingStore::getContainedTypeIdentifiers() const
{
    return msgDataMappingStore.keys().toVector();
}
