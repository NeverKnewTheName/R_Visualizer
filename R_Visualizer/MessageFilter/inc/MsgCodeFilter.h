#ifndef MSGCODEFILTER_H
#define MSGCODEFILTER_H

#include <QObject>

#include "IMsg.h"
#include "IMsgFilter.h"
#include "IMsgCodeFilterStore.h"

#include "MsgCodeType.h"

class MsgCodeFilter : public QOjbect, public IMsgFilter
{
    Q_OBJECT
public:
    MsgCodeFilter(
            IMsgCodeFilterStore *msgCodeFilterStore,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeFilter();

    virtual bool filterMessage(const IMsg &msgToFilter) const;

    virtual void enableFilter(const bool enable);
    virtual bool isEnabled() const;

    virtual void invertFilter(const bool invert);
    virtual bool isInverted() const;

    void addMsgCodeToFilter(const MsgCodeType &msgCodeToAdd);
    void removeMsgCodeFromFilter(const MsgCodeType &msgCodeToRemove);

signals:
    void sgnl_filterEnabled(const bool enabled);
    void sgnl_filterInverted(const bool inverted);
    void sngl_filterChanged();

public slots:
    void slt_enableFilter(const bool enable);
    void slt_invertFilter(const bool invert);

    void slt_addMsgCodeToFilter(const MsgCodeType &msgCodeToAdd);
    void slt_removeMsgCodeToFilter(const MsgCodeType &msgCodeToRemove);

private:
    bool applyInversion(const bool intermediateFilterResult) const;

private:
    IMsgCodeFilterStore *msgCodeFilterStore;

    bool isEnabled;
    bool isInverted;
};

#endif /* MSGCODEFILTER_H */
