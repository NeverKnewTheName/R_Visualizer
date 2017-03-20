#ifndef MSGCODEMAPPINGWIDGET_H
#define MSGCODEMAPPINGWIDGET_H

#include <QWidget>

namespace Ui {
class MsgCodeMappingWidget;
}

class MsgCodeMappingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgCodeMappingWidget(QWidget *parent = 0);
    ~MsgCodeMappingWidget();

private slots:
    void on_msgCodeStoreBtn_clicked();

    void on_msgCodeLoadBtn_clicked();

    void on_msgCodeRemoveBtn_clicked();

    void on_msgCodeAddBtn_clicked();

private:
    Ui::MsgCodeMappingWidget *ui;
};

#endif // MSGCODEMAPPINGWIDGET_H
