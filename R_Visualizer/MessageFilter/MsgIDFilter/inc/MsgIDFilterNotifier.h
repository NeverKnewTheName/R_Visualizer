#ifndef MSGIDFILTERNOTIFIER_H
#define MSGIDFILTERNOTIFIER_H

#include <QObject>

class MsgIDFilter;

class MsgIDFilterNotifier : public QObject
{
    Q_OBJECT
public:
    MsgIDFilterNotifier(
            MsgIDFilter *msgIDFilter,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgIDFilterNotifier();

private:
    MsgIDFilter *msgIDFilter;
};

#endif /* MSGIDFILTERNOTIFIER_H */
