/**
 * @file MsgTimestampFilterNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-19
 * 
 * @brief The signal and slot handler for #IMsgTimestampFilter
 */
#ifndef MSGTIMESTAMPTIMESTAMPNOTIFIER_H
#define MSGTIMESTAMPTIMESTAMPNOTIFIER_H

#include <QObject>

class IMsgTimestampFilter;

/**
 * @brief The MsgTimestampFilterNotifier
 */
class MsgTimestampFilterNotifier : public QObject
{
    Q_OBJECT
public:
    MsgTimestampFilterNotifier(
            IMsgTimestampFilter *msgTimestampFilter
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgTimestampFilterNotifier();

private:
    IMsgTimestampFilter *msgTimestampFilter;
};

#endif /* MSGTIMESTAMPTIMESTAMPNOTIFIER_H */
