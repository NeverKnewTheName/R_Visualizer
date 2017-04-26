/**
 * @file MsgCodeFilterStore.h
 * @author Christian Neuberger
 * @date 2017-04-26
 * 
 * @brief Default implementation of #IMsgCodeFilterStore
 */
#ifndef MSGCODEFILTERSTORE_H
#define MSGCODEFILTERSTORE_H

#include <QVector>
#include "IMsgCodeFilterStore.h"

/**
 * @addtogroup MsgCodeFilterGroup
 * 
 * @{
 */

class MsgCodeFilterStore : public IMsgCodeFilterStore
{
public:
    MsgCodeFilterStore(QObject *parent = Q_NULLPTR);
    virtual ~MsgCodeFilterStore();

    void addMsgCode(const MsgCodeType &msgCodeToAdd);
    void removeMsgCode(const MsgCodeType &msgCodeToRemove);

    bool containsMsgCode(const MsgCodeType &msgCode) const;

    const MsgCodeType &at(const int index) const;
    MsgCodeType &at(const int index);

    int size() const;

    int indexOf(const MsgCodeType &msgCode) const;

    void clear();

private:
    QVector<MsgCodeType> msgCodeVector;
};

/**
 * @}
 */
#endif /* MSGCODEFILTERSTORE_H */
