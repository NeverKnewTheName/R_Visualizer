#ifndef LINEEDITTESTER_H
#define LINEEDITTESTER_H

#include <QWidget>

#include "MsgCodeLineEdit.h"

namespace Ui {
class LineEditTester;
}

class LineEditTester : public QWidget
{
    Q_OBJECT

public:
    explicit LineEditTester(MsgCodeLineEdit *lineEdit,
            QWidget *parent = 0
            );
    ~LineEditTester();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LineEditTester *ui;
    MsgCodeLineEdit *lineEdit;
};

#endif // LINEEDITTESTER_H
