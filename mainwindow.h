#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mysquare.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

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

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionConnect_triggered();

    void on_actionStart_triggered();

    void on_actionStop_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    MySquare *square;
    QString currentFileName;
};

#endif // MAINWINDOW_H
