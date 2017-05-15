#ifndef LINEEDITTESTER_H
#define LINEEDITTESTER_H

#include <QWidget>

#include "MsgIDLineEdit.h"

namespace Ui {
class LineEditTester;
}

class LineEditTester : public QWidget
{
    Q_OBJECT

public:
    explicit LineEditTester(
            MsgIDLineEdit *lineEdit,
            QWidget *parent = 0
            );
    ~LineEditTester();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LineEditTester *ui;
    MsgIDLineEdit *lineEdit;
};

#endif // LINEEDITTESTER_H
