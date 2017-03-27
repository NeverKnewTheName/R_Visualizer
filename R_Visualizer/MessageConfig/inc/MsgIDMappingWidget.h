/**
 * \file MsgIDMappingWidget.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides a gui widget to manage message id mappings
 */
#ifndef MSGIDMAPPINGWIDGET_H
#define MSGIDMAPPINGWIDGET_H

#include <QWidget>

#include "IMsgIDRep.h"
#include "IMsgIDMappingModel.h"

namespace Ui {
class MsgIDMappingWidget;
}

/**
 * \brief The MsgIDMappingWidget
 */
class MsgIDMappingWidget : public QWidget
{
    Q_OBJECT

public:
    /* explicit MsgIDMappingWidget(QWidget *parent = 0); */
    explicit MsgIDMappingWidget(IMsgIDMappingModel *model, QWidget *parent = 0);
    ~MsgIDMappingWidget();

    void setModel(IMsgIDMappingModel *model);

private slots:
    void on_idStoreBtn_clicked();
    void on_idLoadBtn_clicked();
    void on_idRmvBtn_clicked();
    void on_idAddBtn_clicked();

    void slt_clear();
    void slt_MsgIDRepAddFinished(const IMsgIDRep &addedMsgIDRep);
signals:
    void sngl_MappingsChanged();
    void sgnl_MsgIDRepAdded(const IMsgIDRep &newMsgIDRep);
    void sgnl_MsgIDRepUpdated(const IMsgIDRep &updatedMsgIDRep);
    void sgnl_MsgIDRepRemoved(const MsgIDType relatedID);

private:
    Ui::MsgIDMappingWidget *ui;
    IMsgIDMappingModel *msgIDMappingModel;

    void appendMsgIDMapping(const IMsgIDRep &msgIDRepToAdd);
    void init();
};

#endif // MSGIDMAPPINGWIDGET_H
