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

class IMsgDataMapping;

/**
 * @brief The MsgDataMappingNotifier
 */
class MsgDataMappingNotifier : public QObject
{
    Q_OBJECT
public:
    MsgDataMappingNotifier(
            IMsgDataMapping *msgDataMapping,
            QObject *parent = Q_NULLPTR
            );
    virtual ~MsgDataMappingNotifier();

private:
    IMsgDataMapping *msgDataMapping;
};

#endif /* MSGDATAMAPPINGNOTIFIER_H */
