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

#include "MsgIDType.h"
#include "MsgCodeType.h"
#include "MsgDataType.h"

class IMsgDataMappingManager;
class MsgDataMappingModel;
class IMsgDataMapping;


namespace Ui {
class MsgDataMappingWidget;
}

/**
 * @addtogroup MsgDataMappingGroup
 * 
 * @{
 */

/**
 * \brief The MsgDataMappingWidget
 */
class MsgDataMappingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MsgDataMappingWidget(
            IMsgDataMappingManager *msgDataMappingManager,
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
            const MsgIDType &msgID,
            const MsgCodeType &msgCode,
            const QString &formatString,
            const QColor &defaultColor
            );

private:
    void init();
    void connectModel();

private:
    Ui::MsgDataMappingWidget *ui;
    IMsgDataMappingManager *msgDataMappingManager;
    MsgDataMappingModel *msgDataMappingModel;
};

/**
 * @}
 */

#endif // MSGDATAMAPPINGWIDGET_H
