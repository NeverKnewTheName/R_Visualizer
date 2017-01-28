#ifndef MSGDATAWIDGET_H
#define MSGDATAWIDGET_H

#include <QWidget>

namespace Ui {
class MsgDataWidget;
}

class MsgDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgDataWidget(QWidget *parent = 0);
    MsgDataWidget(const MsgDataWidget &other);
    ~MsgDataWidget();

    void setCode(const QString &code);
    void setData(const QString &Data);
    bool getDataShown() const;

private slots:
    void on_ShowDataPushButton_clicked();

private:
    Ui::MsgDataWidget *ui;
    bool DataShown;
};

Q_DECLARE_METATYPE(MsgDataWidget)

#endif // MSGDATAWIDGET_H
