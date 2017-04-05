#ifndef MSGTIMESTAMPFILTER_H
#define MSGTIMESTAMPFILTER_H

#include <QDateTime>

#include "IMsg.h"
#include "ITimestampedMsgFilter.h"

class MsgTimestampFilter : public QObject, public ITimestampedMsgFilter
{
    Q_OBJECT
public:
    explicit MsgTimestampFilter(QObject *parent = 0);
    virtual ~MsgTimestampFilter();

    virtual bool filterMessage(const ITimestampedMsg &msgToFilter) const;

    void enableFilter(const bool enable);
    bool isEnabled() const;

    void invertFilter(const bool invert);
    bool isInverted() const;

    void setTimestampFrom(const QDateTime &timestampFrom);
    QDateTime getTimestampFrom() const;
    void setTimestampTo(const QDateTime &timestampTo);
    QDateTime getTimestampTo() const;

signals:
    void sgnl_filterEnabled(const bool enabled);
    void sgnl_filterInverted(const bool inverted);
    void sngl_filterChanged();

public slots:
    void slt_enableFilter(const bool enable);
    void slt_invertFilter(const bool invert);

    void slt_changeTimestampFrom(const QDateTime &newTimestampFrom);
    void slt_changeTimestampTo(const QDateTime &newTimestampTo);

private:
    virtual bool greaterThanTimestampFrom(const QDateTime &timestamp) const;
    virtual bool lowerThanTimestampTo(const QDateTime &timestamp) const;
    bool applyInversion(const bool intermediateFilterResult) const;

private:
    QDateTime timestampeFrom;
    QDateTime timestampTo;

    bool isEnabled;
    bool isInverted;
};

#endif /* MSGTIMESTAMPFILTER_H */
