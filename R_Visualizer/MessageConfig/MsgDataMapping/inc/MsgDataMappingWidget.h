/**
 * \file MsgDataMappingWidget.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides a gui widget to manage message data mappings
 */
#ifndef MSGDATAMAPPINGWIDGET_H
#define MSGDATAMAPPINGWIDGET_H

#include <QWidget>

namespace Ui {
class MsgDataMappingWidget;
}

/**
 * \brief The MsgDataMappingWidget
 */
class MsgDataMappingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MsgDataMappingWidget(QWidget *parent = 0);
    ~MsgDataMappingWidget();

private slots:
    void on_msgDataStoreBtn_clicked();

    void on_msgDataLoadBtn_clicked();

    void on_msgDataRemoveBtn_clicked();

    void on_msgDataAddBtn_clicked();

private:
    Ui::MsgDataMappingWidget *ui;
};

#endif // MSGDATAMAPPINGWIDGET_H
