#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mysquare.h"
#include "msgmodel.h"
#include "idmodel.h"
#include "msgtypemodel.h"

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

    void on_idStoreBtn_clicked();

    void on_idLoadBtn_clicked();

    void on_msgTypeSoreBtn_clicked();

    void on_msgTypeLoadBtn_clicked();

private:
    void initMsgsTableView();
    void initIDTableView();
    void initMsgTypeTableView();
    void initVisualizerGraphicsView();

    Ui::MainWindow *ui;
    QString currentFileName;
    MsgModel *msgModel;
    IDModel *idModel;
    MsgTypeModel *msgTypeModel;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    MySquare *square;

};

#endif // MAINWINDOW_H
