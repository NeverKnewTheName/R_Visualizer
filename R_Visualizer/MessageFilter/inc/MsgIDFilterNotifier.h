#ifndef MSGIDFILTERNOTIFIER_H
#define MSGIDFILTERNOTIFIER_H

#include <QObject>

class IMsgIDFilter;

class MsgIDFilterNotifier
{
public:
    MsgIDFilterNotifier(
            IMsgIDFilter *msgIDFilter,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgIDFilterNotifier();

private:
    IMsgIDFilter *msgIDFilter;
};

#endif /* MSGIDFILTERNOTIFIER_H */
