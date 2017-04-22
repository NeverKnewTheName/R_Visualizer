/**
 * @file MsgDataMappingNotifier.h
 * @author Christian Neuberger
 * @date 2017-04-18
 * 
 * @brief The Signal and slot handler for #IMsgDataMapping
 */
#ifndef MSGDATAMAPPINGNOTIFIER_H
#define MSGDATAMAPPINGNOTIFIER_H

#include <QObject>

class IMsgDataMappingManager;

/**
 * @brief The MsgDataMappingNotifier
 */
class MsgDataMappingNotifier : public QObject
{
    Q_OBJECT
public:
    MsgDataMappingNotifier(
            IMsgDataMappingManager *msgDataMappingManager,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgDataMappingNotifier();

private:
    IMsgDataMappingManager *msgDataMappingManager;
};

#endif /* MSGDATAMAPPINGNOTIFIER_H */
