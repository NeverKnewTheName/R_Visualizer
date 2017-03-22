/********************************************************************************
** Form generated from reading UI file 'msgdatamappingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGDATAMAPPINGWIDGET_H
#define UI_MSGDATAMAPPINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsgDataMappingWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_4;
    QSpacerItem *StoreLoadSpacer;
    QPushButton *msgDataLoadBtn;
    QTableView *msgDataTableView;
    QPushButton *msgDataStoreBtn;
    QPushButton *msgDataAddBtn;
    QPushButton *msgDataRemoveBtn;
    QSpacerItem *RemoveAddSpacer;

    void setupUi(QWidget *MsgDataMappingWidget)
    {
        if (MsgDataMappingWidget->objectName().isEmpty())
            MsgDataMappingWidget->setObjectName(QStringLiteral("MsgDataMappingWidget"));
        MsgDataMappingWidget->resize(600, 400);
        verticalLayout = new QVBoxLayout(MsgDataMappingWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_9 = new QGroupBox(MsgDataMappingWidget);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(groupBox_9->sizePolicy().hasHeightForWidth());
        groupBox_9->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(groupBox_9);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        StoreLoadSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(StoreLoadSpacer, 5, 0, 1, 1);

        msgDataLoadBtn = new QPushButton(groupBox_9);
        msgDataLoadBtn->setObjectName(QStringLiteral("msgDataLoadBtn"));

        gridLayout_4->addWidget(msgDataLoadBtn, 5, 3, 1, 1);

        msgDataTableView = new QTableView(groupBox_9);
        msgDataTableView->setObjectName(QStringLiteral("msgDataTableView"));

        gridLayout_4->addWidget(msgDataTableView, 0, 0, 5, 6);

        msgDataStoreBtn = new QPushButton(groupBox_9);
        msgDataStoreBtn->setObjectName(QStringLiteral("msgDataStoreBtn"));

        gridLayout_4->addWidget(msgDataStoreBtn, 5, 2, 1, 1);

        msgDataAddBtn = new QPushButton(groupBox_9);
        msgDataAddBtn->setObjectName(QStringLiteral("msgDataAddBtn"));

        gridLayout_4->addWidget(msgDataAddBtn, 6, 3, 1, 1);

        msgDataRemoveBtn = new QPushButton(groupBox_9);
        msgDataRemoveBtn->setObjectName(QStringLiteral("msgDataRemoveBtn"));

        gridLayout_4->addWidget(msgDataRemoveBtn, 6, 2, 1, 1);

        RemoveAddSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(RemoveAddSpacer, 6, 0, 1, 1);


        verticalLayout->addWidget(groupBox_9);


        retranslateUi(MsgDataMappingWidget);

        QMetaObject::connectSlotsByName(MsgDataMappingWidget);
    } // setupUi

    void retranslateUi(QWidget *MsgDataMappingWidget)
    {
        MsgDataMappingWidget->setWindowTitle(QApplication::translate("MsgDataMappingWidget", "Form", 0));
        groupBox_9->setTitle(QApplication::translate("MsgDataMappingWidget", "MsgData Mapping", 0));
#ifndef QT_NO_TOOLTIP
        msgDataLoadBtn->setToolTip(QApplication::translate("MsgDataMappingWidget", "Load an ID configuration (*.json)", 0));
#endif // QT_NO_TOOLTIP
        msgDataLoadBtn->setText(QApplication::translate("MsgDataMappingWidget", "Load", 0));
#ifndef QT_NO_TOOLTIP
        msgDataTableView->setToolTip(QApplication::translate("MsgDataMappingWidget", "<html><head/><body><p>ID configuration browser which shows all currently available IDs and their parsing configuration.</p><p>Either load a whole ID configuration with the Load button or Add/Remove  IDs to the current configuration. </p><p>The current configuration can be saved (*.json) with the store button.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        msgDataStoreBtn->setToolTip(QApplication::translate("MsgDataMappingWidget", "Save the current ID configuration (*.json) to a file", 0));
#endif // QT_NO_TOOLTIP
        msgDataStoreBtn->setText(QApplication::translate("MsgDataMappingWidget", "Store", 0));
#ifndef QT_NO_TOOLTIP
        msgDataAddBtn->setToolTip(QApplication::translate("MsgDataMappingWidget", "<html><head/><body><p>Add a new ID configuration entry to the current ID configuration. The ID configuration tool is called.</p><p>The new entry will be appended to the list.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        msgDataAddBtn->setText(QApplication::translate("MsgDataMappingWidget", "Add", 0));
#ifndef QT_NO_TOOLTIP
        msgDataRemoveBtn->setToolTip(QApplication::translate("MsgDataMappingWidget", "Remove the selected entry from the current ID configuration.", 0));
#endif // QT_NO_TOOLTIP
        msgDataRemoveBtn->setText(QApplication::translate("MsgDataMappingWidget", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class MsgDataMappingWidget: public Ui_MsgDataMappingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGDATAMAPPINGWIDGET_H
