/**
 * @file MsgCodeFilterNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-19
 *
 * @brief The signal and slot manager for #IMsgCodeFilter
 */
#ifndef MSGCODEFILTERNOTIFIER_H
#define MSGCODEFILTERNOTIFIER_H

#include <QObject>

class MsgCodeFilter;

/**
 * @brief The MsgCodeFilterNotifier
 */
class MsgCodeFilterNotifier : public QObject
{
    Q_OBJECT
public:
    MsgCodeFilterNotifier(
            MsgCodeFilter *msgCodeFilter,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeFilterNotifier();

private:
    MsgCodeFilter *msgCodeFilter;
};

#endif /* MSGCODEFILTERNOTIFIER_H */
