/********************************************************************************
** Form generated from reading UI file 'msgcodemappingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGCODEMAPPINGWIDGET_H
#define UI_MSGCODEMAPPINGWIDGET_H

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

class Ui_MsgCodeMappingWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_5;
    QPushButton *msgCodeLoadBtn;
    QSpacerItem *StoreLoadSpacer;
    QPushButton *msgCodeStoreBtn;
    QTableView *msgCodeTableView;
    QPushButton *msgCodeAddBtn;
    QPushButton *msgCodeRemoveBtn;
    QSpacerItem *RemoveAddSpacer;

    void setupUi(QWidget *MsgCodeMappingWidget)
    {
        if (MsgCodeMappingWidget->objectName().isEmpty())
            MsgCodeMappingWidget->setObjectName(QStringLiteral("MsgCodeMappingWidget"));
        MsgCodeMappingWidget->resize(600, 400);
        verticalLayout = new QVBoxLayout(MsgCodeMappingWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_10 = new QGroupBox(MsgCodeMappingWidget);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(groupBox_10->sizePolicy().hasHeightForWidth());
        groupBox_10->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(groupBox_10);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        msgCodeLoadBtn = new QPushButton(groupBox_10);
        msgCodeLoadBtn->setObjectName(QStringLiteral("msgCodeLoadBtn"));

        gridLayout_5->addWidget(msgCodeLoadBtn, 5, 3, 1, 1);

        StoreLoadSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(StoreLoadSpacer, 5, 0, 1, 1);

        msgCodeStoreBtn = new QPushButton(groupBox_10);
        msgCodeStoreBtn->setObjectName(QStringLiteral("msgCodeStoreBtn"));

        gridLayout_5->addWidget(msgCodeStoreBtn, 5, 2, 1, 1);

        msgCodeTableView = new QTableView(groupBox_10);
        msgCodeTableView->setObjectName(QStringLiteral("msgCodeTableView"));

        gridLayout_5->addWidget(msgCodeTableView, 0, 0, 5, 6);

        msgCodeAddBtn = new QPushButton(groupBox_10);
        msgCodeAddBtn->setObjectName(QStringLiteral("msgCodeAddBtn"));

        gridLayout_5->addWidget(msgCodeAddBtn, 6, 3, 1, 1);

        msgCodeRemoveBtn = new QPushButton(groupBox_10);
        msgCodeRemoveBtn->setObjectName(QStringLiteral("msgCodeRemoveBtn"));

        gridLayout_5->addWidget(msgCodeRemoveBtn, 6, 2, 1, 1);

        RemoveAddSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(RemoveAddSpacer, 6, 0, 1, 1);


        verticalLayout->addWidget(groupBox_10);


        retranslateUi(MsgCodeMappingWidget);

        QMetaObject::connectSlotsByName(MsgCodeMappingWidget);
    } // setupUi

    void retranslateUi(QWidget *MsgCodeMappingWidget)
    {
        MsgCodeMappingWidget->setWindowTitle(QApplication::translate("MsgCodeMappingWidget", "Form", 0));
        groupBox_10->setTitle(QApplication::translate("MsgCodeMappingWidget", "MsgCode Mapping", 0));
#ifndef QT_NO_TOOLTIP
        msgCodeLoadBtn->setToolTip(QApplication::translate("MsgCodeMappingWidget", "Load an Message Type configuration (*.json)", 0));
#endif // QT_NO_TOOLTIP
        msgCodeLoadBtn->setText(QApplication::translate("MsgCodeMappingWidget", "Load", 0));
#ifndef QT_NO_TOOLTIP
        msgCodeStoreBtn->setToolTip(QApplication::translate("MsgCodeMappingWidget", "Save the current Message Type configuration (*.json) to a file", 0));
#endif // QT_NO_TOOLTIP
        msgCodeStoreBtn->setText(QApplication::translate("MsgCodeMappingWidget", "Store", 0));
#ifndef QT_NO_TOOLTIP
        msgCodeTableView->setToolTip(QApplication::translate("MsgCodeMappingWidget", "<html><head/><body><p>Message Type configuration browser which shows all currently available Message Types and their parsing configuration.</p><p>Either load a whole Message Type configuration with the Load button or Add/Remove Message Types to the current configuration. </p><p>The current configuration can be saved (*.json) with the store button.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        msgCodeAddBtn->setToolTip(QApplication::translate("MsgCodeMappingWidget", "<html><head/><body><p>Add a new Message Type configuration entry to the current Message Type configuration. The Message Type configuration tool is called</p><p>The new entry will be appended to the list.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        msgCodeAddBtn->setText(QApplication::translate("MsgCodeMappingWidget", "Add", 0));
#ifndef QT_NO_TOOLTIP
        msgCodeRemoveBtn->setToolTip(QApplication::translate("MsgCodeMappingWidget", "Remove the selected entry from the current Message Type configuration.", 0));
#endif // QT_NO_TOOLTIP
        msgCodeRemoveBtn->setText(QApplication::translate("MsgCodeMappingWidget", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class MsgCodeMappingWidget: public Ui_MsgCodeMappingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGCODEMAPPINGWIDGET_H
