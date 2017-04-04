#ifndef MESSAGEFILTER_H
#define MESSAGEFILTER_H

#include <QObject>
#include <QVector>
#include "IMessageFilter.h"

class MessageFilter :public QOjbect, public IMessageFilter
{
    Q_OBJECT
public:
    MessageFilter();
    virtual ~MessageFilter();

    virtual bool filterMessage(const IMsg &msgToFilter) const;

    virtual void addFilter(IFilter *filterToAdd);
    virtual void removeFilter(IFilter *filterToRemove);

signals:
    void sgnl_FilterChanged();
    void sgnl_PropagateUserRole(
            const UserRoleMngr::UserRole roleToApply
            );

public slots:
    void slt_applyRole(
            const UserRoleMngr::UserRole roleToApply
            );

private:
    QVector<IFilter *> filterStore;

};

#endif // MESSAGEFILTER_H
