/**
 * @file MsgCodeMappingNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-18
 * 
 * @brief The signal and slot handler for the #IMsgCodeMapping
 */
#ifndef MSGCODEMAPPINGNOTIFIER_H
#define MSGCODEMAPPINGNOTIFIER_H

#include <QObject>

class IMsgCodeMapping;
/**
 * @brief The MsgCodeMappingNotifier
 */
class MsgCodeMappingNotifier : public QObject
{
    Q_OBJECT
public:
    MsgCodeMappingNotifier(
            IMsgCodeMapping *msgCodeMapping,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgCodeMappingNotifier();

private:
    IMsgCodeMapping *msgCodeMapping;
};

#endif /* MSGCODEMAPPINGNOTIFIER_H */
