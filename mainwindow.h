#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "r_vis_timer.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void setChckBoxCheckedOVF(bool);
    void setChckBoxCheckedCMP(bool);


private slots:
    void timerOverflowed();
    void timerCompareMatch();

private:
    Ui::MainWindow *ui;
    R_Vis_Timer *tpmTimer_0;
};

#endif // MAINWINDOW_H
