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

class IMsgCodeFilter;

/**
 * @brief The MsgCodeFilterNotifier
 */
class MsgCodeFilterNotifier
{
    Q_OBJECT
public:
    MsgCodeFilterNotifier(
            IMsgCodeFilter *msgCodeFilter,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeFilterNotifier();

private:
    IMsgCodeFilter *msgCodeFilter;
};

#endif /* MSGCODEFILTERNOTIFIER_H */
