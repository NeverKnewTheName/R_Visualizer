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

#include "MsgIDType.h"

class IMsgIDMappingManager;
class MsgIDMappingModel;
class IMsgIDMapping;

namespace Ui {
class MsgIDMappingWidget;
}

/**
 * @addtogroup MsgIDMappingGroup
 * 
 * @{
 */

/**
 * \brief The MsgIDMappingWidget
 */
class MsgIDMappingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MsgIDMappingWidget(
            IMsgIDMappingManager *msgIDMappingManager,
            MsgIDMappingModel *model,
            QWidget *parent = Q_NULLPTR
            );
    ~MsgIDMappingWidget();

    void setModel(MsgIDMappingModel *model);

signals:
    void sgnl_MappingsChanged();
    void sgnl_MsgIDMappingAdded(const IMsgIDMapping &newMsgIDMapping);
    void sgnl_MsgIDMappingUpdated(const IMsgIDMapping &updatedMsgIDMapping);
    void sgnl_MsgIDMappingRemoved(const MsgIDType relatedID);

    void sgnl_AddMsgIDMapping(
            const IMsgIDMapping &mappingToAdd
            );

    void sgnl_RemoveMsgIDMapping(
            const MsgIDType &msgID
            );

private slots:
    void on_idStoreBtn_clicked();
    void on_idLoadBtn_clicked();
    void on_idRmvBtn_clicked();
    void on_idAddBtn_clicked();

    void slt_clear();
    void slt_MsgIDMappingAddFinished(const IMsgIDMapping &addedMsgIDMapping);

private:
    void init();
    void connectModel();
    void appendMsgIDMapping(const IMsgIDMapping &msgIDMappingToAdd);

private:
    Ui::MsgIDMappingWidget *ui;
    IMsgIDMappingManager *msgIDMappingManager;
    MsgIDMappingModel *msgIDMappingModel;
};

/**
 * @}
 */

#endif // MSGIDMAPPINGWIDGET_H
