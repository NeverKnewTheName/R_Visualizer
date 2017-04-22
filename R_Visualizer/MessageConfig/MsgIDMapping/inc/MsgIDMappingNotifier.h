/**
 * @file MsgIDMappingNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-18
 * 
 * @brief The signal and slot handler for the #IMsgIDMapping
 */
#ifndef MSGIDMAPPINGNOTIFIER_H
#define MSGIDMAPPINGNOTIFIER_H

#include <QObject>

class IMsgIDMappingManager;

/**
 * @brief The MsgIDMappingNotifier
 */
class MsgIDMappingNotifier : public QObject
{
    Q_OBJECT
public:
    MsgIDMappingNotifier(
            IMsgIDMappingManager *msgIDMappingManager,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgIDMappingNotifier();

private:
    IMsgIDMappingManager *msgIDMappingManager;
};

#endif /* MSGIDMAPPINGNOTIFIER_H */
