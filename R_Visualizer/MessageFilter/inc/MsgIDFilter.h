#ifndef MSGIDFILTER_H
#define MSGIDFILTER_H

#include <QObject>

#include "IMsg.h"
#include "IMsgFilter.h"
#include "IMsgIDFilterStore.h"

#include "MsgIDType.h"

class MsgIDFilter : public QOjbect, public IMsgFilter
{
    Q_OBJECT
public:
    explicit MsgIDFilter(
            IMsgIDFilterStore *msgIDFilterStore,
            QOjbect * parent = Q_NULLPTR
            );
    virtual ~MsgIDFilter();

    virtual bool filterMessage(const IMsg &msgToFilter) const;

    virtual void enableFilter(const bool enable);
    virtual bool isEnabled() const;

    virtual void invertFilter(const bool invert);
    virtual bool isInverted() const;

    void addMsgIDToFilter(const MsgIDType &msgIDToAdd);
    void removeMsgIDFromFilter(const MsgIDType &msgIDToRemove);

signals:
    void sgnl_filterEnabled(const bool enabled);
    void sgnl_filterInverted(const bool inverted);
    void sngl_filterChanged();

public slots:
    void slt_enableFilter(const bool enable);
    void slt_invertFilter(const bool invert);

    void slt_addMsgIDToFilter(const MsgIDType &msgIDToAdd);
    void slt_removeMsgIDToFilter(const MsgIDType &msgIDToRemove);

private:
    bool applyInversion(const bool intermediateFilterResult) const;

private:
    IMsgIDFilterStore *msgIDFilterStore;

    bool isEnabled;
    bool isInverted;
};

#endif /* MSGIDFILTER_H */
