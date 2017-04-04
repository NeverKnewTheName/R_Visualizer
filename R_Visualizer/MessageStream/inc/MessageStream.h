#ifndef MESSAGESTREAM_H
#define MESSAGESTREAM_H

#include <QObject>

class MessageStream : public QObject
{
    Q_OBJECT
public:
    explicit MessageStream(QObject *parent = 0);

signals:

public slots:
};

#endif // MESSAGESTREAM_H