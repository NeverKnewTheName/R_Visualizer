/**
 * \file MsgCodeMappingWidget.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Provides a gui widget to manage message code mappings
 */
#ifndef MSGCODEMAPPINGWIDGET_H
#define MSGCODEMAPPINGWIDGET_H

#include <QWidget>


#include "MsgCodeType.h"

class IMsgCodeMappingManager;
class MsgCodeMappingModel;
class IMsgCodeMapping;

namespace Ui {
class MsgCodeMappingWidget;
}

/**
 * \brief The MsgCodeMappingWidget
 */
class MsgCodeMappingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MsgCodeMappingWidget(
            IMsgCodeMappingManager *msgCodeMappingManager,
            MsgCodeMappingModel *msgCodeMappingModel,
            QWidget *parent = 0);
    ~MsgCodeMappingWidget();

    void setModel(
            MsgCodeMappingModel *model
            );

private slots:
    void on_msgCodeStoreBtn_clicked();
    void on_msgCodeLoadBtn_clicked();
    void on_msgCodeRemoveBtn_clicked();
    void on_msgCodeAddBtn_clicked();

    void slt_clear();
    void slt_MsgCodeMappingAddFinished(
            const IMsgCodeMapping &addedMsgCodeMapping
            );

signals:
    void sgnl_MappingsChanged();
    void sgnl_MsgCodeMappingAdded(const IMsgCodeMapping &newMsgCodeMapping);
    void sgnl_MsgCodeMappingUpdated(const IMsgCodeMapping &updatedMsgCodeMapping);
    void sgnl_MsgCodeMappingRemoved(const MsgCodeType relatedCode);

    void sgnl_AddMsgCodeMapping(
            const IMsgCodeMapping &mappingToAdd
            );

    void sgnl_RemoveMsgCodeMapping(
            const MsgCodeType &msgCode
            );

private:
    void connectModel();

    void appendMsgCodemapping(
            const IMsgCodeMapping &msgCodeMappingToAdd
            );
    void init();

private:
    Ui::MsgCodeMappingWidget *ui;
    IMsgCodeMappingManager *msgCodeMappingManager;
    MsgCodeMappingModel *msgCodeMappingModel;
};

#endif // MSGCODEMAPPINGWIDGET_H
