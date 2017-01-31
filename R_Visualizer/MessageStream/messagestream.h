#ifndef MESSAGESTREAM_H
#define MESSAGESTREAM_H

#include <QWidget>

namespace Ui {
class MessageStream;
}

class MessageStream : public QWidget
{
    Q_OBJECT

public:
    explicit MessageStream(QWidget *parent = 0);
    ~MessageStream();

private:
    Ui::MessageStream *ui;
};

#endif // MESSAGESTREAM_H
