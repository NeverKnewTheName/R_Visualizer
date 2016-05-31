#ifndef MESSAGECONFIG_H
#define MESSAGECONFIG_H

#include <QWidget>

namespace Ui {
class MessageConfig;
}

class MessageConfig : public QWidget
{
    Q_OBJECT

public:
    explicit MessageConfig(QWidget *parent = 0);
    ~MessageConfig();

private:
    Ui::MessageConfig *ui;
};

#endif // MESSAGECONFIG_H
