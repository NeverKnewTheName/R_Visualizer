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

#include "MsgDataMappingModel.h"

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
    explicit MsgDataMappingWidget(
            MsgDataMappingModel *msgDataMappingModel,
            QWidget *parent = Q_NULLPTR
            );
    ~MsgDataMappingWidget();

    void setModel(MsgDataMappingModel *model);

signals:
    void sgnl_MappingsChanged();
    void sgnl_MsgDataMappingAdded(const IMsgDataMapping &newMsgDataMapping);
    void sgnl_MsgDataMappingUpdated(const IMsgDataMapping &updatedMsgDataMapping);
    void sgnl_MsgDataMappingRemoved(const MsgDataType relatedData);

    void sgnl_AddMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const IMsgDataMapping &mappingToAdd
            );

    void sgnl_RemoveMsgDataMapping(
            const MsgIDType &msgID,
            const MsgCodeType &msgCode
            );


private slots:
    void on_msgDataStoreBtn_clicked();
    void on_msgDataLoadBtn_clicked();
    void on_msgDataRemoveBtn_clicked();
    void on_msgDataAddBtn_clicked();

    void slt_clear();
    void slt_MsgDataMappingAddFinished(
            const IMsgDataMapping &addedMsgDataMapping
            );

private:
    void init();
    void connectModel();

private:
    Ui::MsgDataMappingWidget *ui;
    MsgDataMappingModel *msgDataMappingModel;
};

#endif // MSGDATAMAPPINGWIDGET_H
