#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mysquare.h"
#include "msgmodel.h"

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

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionConnect_triggered();

    void on_actionStart_triggered();

    void on_actionStop_triggered();

private:

    void initMsgsTableView();
    void initVisualizerGraphicsView();

    Ui::MainWindow *ui;
    QString currentFileName;
    MsgModel *msgModel;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    MySquare *square;

};

#endif // MAINWINDOW_H
