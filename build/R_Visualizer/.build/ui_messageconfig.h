/********************************************************************************
** Form generated from reading UI file 'messageconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGECONFIG_H
#define UI_MESSAGECONFIG_H

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

class Ui_MessageConfig
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_4;
    QPushButton *idStoreBtn;
    QPushButton *idRmvBtn;
    QPushButton *idLoadBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *idAddBtn;
    QTableView *idTableView;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_5;
    QPushButton *msgTypeLoadBtn;
    QPushButton *msgTypeAddBtn;
    QPushButton *msgTypeStoreBtn;
    QPushButton *msgTypeRmvBtn;
    QSpacerItem *horizontalSpacer_2;
    QTableView *msgTypeTableView;

    void setupUi(QWidget *MessageConfig)
    {
        if (MessageConfig->objectName().isEmpty())
            MessageConfig->setObjectName(QStringLiteral("MessageConfig"));
        MessageConfig->resize(612, 820);
        verticalLayout = new QVBoxLayout(MessageConfig);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_9 = new QGroupBox(MessageConfig);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(groupBox_9->sizePolicy().hasHeightForWidth());
        groupBox_9->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(groupBox_9);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        idStoreBtn = new QPushButton(groupBox_9);
        idStoreBtn->setObjectName(QStringLiteral("idStoreBtn"));

        gridLayout_4->addWidget(idStoreBtn, 5, 2, 1, 1);

        idRmvBtn = new QPushButton(groupBox_9);
        idRmvBtn->setObjectName(QStringLiteral("idRmvBtn"));

        gridLayout_4->addWidget(idRmvBtn, 5, 4, 1, 1);

        idLoadBtn = new QPushButton(groupBox_9);
        idLoadBtn->setObjectName(QStringLiteral("idLoadBtn"));

        gridLayout_4->addWidget(idLoadBtn, 5, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 5, 0, 1, 1);

        idAddBtn = new QPushButton(groupBox_9);
        idAddBtn->setObjectName(QStringLiteral("idAddBtn"));

        gridLayout_4->addWidget(idAddBtn, 5, 3, 1, 1);

        idTableView = new QTableView(groupBox_9);
        idTableView->setObjectName(QStringLiteral("idTableView"));

        gridLayout_4->addWidget(idTableView, 0, 0, 5, 5);


        verticalLayout->addWidget(groupBox_9);

        groupBox_10 = new QGroupBox(MessageConfig);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        sizePolicy.setHeightForWidth(groupBox_10->sizePolicy().hasHeightForWidth());
        groupBox_10->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(groupBox_10);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        msgTypeLoadBtn = new QPushButton(groupBox_10);
        msgTypeLoadBtn->setObjectName(QStringLiteral("msgTypeLoadBtn"));

        gridLayout_5->addWidget(msgTypeLoadBtn, 5, 1, 1, 1);

        msgTypeAddBtn = new QPushButton(groupBox_10);
        msgTypeAddBtn->setObjectName(QStringLiteral("msgTypeAddBtn"));

        gridLayout_5->addWidget(msgTypeAddBtn, 5, 3, 1, 1);

        msgTypeStoreBtn = new QPushButton(groupBox_10);
        msgTypeStoreBtn->setObjectName(QStringLiteral("msgTypeStoreBtn"));

        gridLayout_5->addWidget(msgTypeStoreBtn, 5, 2, 1, 1);

        msgTypeRmvBtn = new QPushButton(groupBox_10);
        msgTypeRmvBtn->setObjectName(QStringLiteral("msgTypeRmvBtn"));

        gridLayout_5->addWidget(msgTypeRmvBtn, 5, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 5, 0, 1, 1);

        msgTypeTableView = new QTableView(groupBox_10);
        msgTypeTableView->setObjectName(QStringLiteral("msgTypeTableView"));

        gridLayout_5->addWidget(msgTypeTableView, 0, 0, 5, 5);


        verticalLayout->addWidget(groupBox_10);


        retranslateUi(MessageConfig);

        QMetaObject::connectSlotsByName(MessageConfig);
    } // setupUi

    void retranslateUi(QWidget *MessageConfig)
    {
        MessageConfig->setWindowTitle(QApplication::translate("MessageConfig", "MessageConfig", 0));
        groupBox_9->setTitle(QApplication::translate("MessageConfig", "IDs", 0));
#ifndef QT_NO_TOOLTIP
        idStoreBtn->setToolTip(QApplication::translate("MessageConfig", "Save the current ID configuration (*.json) to a file", 0));
#endif // QT_NO_TOOLTIP
        idStoreBtn->setText(QApplication::translate("MessageConfig", "Store", 0));
#ifndef QT_NO_TOOLTIP
        idRmvBtn->setToolTip(QApplication::translate("MessageConfig", "Remove the selected entry from the current ID configuration.", 0));
#endif // QT_NO_TOOLTIP
        idRmvBtn->setText(QApplication::translate("MessageConfig", "Remove", 0));
#ifndef QT_NO_TOOLTIP
        idLoadBtn->setToolTip(QApplication::translate("MessageConfig", "Load an ID configuration (*.json)", 0));
#endif // QT_NO_TOOLTIP
        idLoadBtn->setText(QApplication::translate("MessageConfig", "Load", 0));
#ifndef QT_NO_TOOLTIP
        idAddBtn->setToolTip(QApplication::translate("MessageConfig", "<html><head/><body><p>Add a new ID configuration entry to the current ID configuration. The ID configuration tool is called.</p><p>The new entry will be appended to the list.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        idAddBtn->setText(QApplication::translate("MessageConfig", "Add", 0));
#ifndef QT_NO_TOOLTIP
        idTableView->setToolTip(QApplication::translate("MessageConfig", "<html><head/><body><p>ID configuration browser which shows all currently available IDs and their parsing configuration.</p><p>Either load a whole ID configuration with the Load button or Add/Remove  IDs to the current configuration. </p><p>The current configuration can be saved (*.json) with the store button.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        groupBox_10->setTitle(QApplication::translate("MessageConfig", "Message Types", 0));
#ifndef QT_NO_TOOLTIP
        msgTypeLoadBtn->setToolTip(QApplication::translate("MessageConfig", "Load an Message Type configuration (*.json)", 0));
#endif // QT_NO_TOOLTIP
        msgTypeLoadBtn->setText(QApplication::translate("MessageConfig", "Load", 0));
#ifndef QT_NO_TOOLTIP
        msgTypeAddBtn->setToolTip(QApplication::translate("MessageConfig", "<html><head/><body><p>Add a new Message Type configuration entry to the current Message Type configuration. The Message Type configuration tool is called</p><p>The new entry will be appended to the list.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        msgTypeAddBtn->setText(QApplication::translate("MessageConfig", "Add", 0));
#ifndef QT_NO_TOOLTIP
        msgTypeStoreBtn->setToolTip(QApplication::translate("MessageConfig", "Save the current Message Type configuration (*.json) to a file", 0));
#endif // QT_NO_TOOLTIP
        msgTypeStoreBtn->setText(QApplication::translate("MessageConfig", "Store", 0));
#ifndef QT_NO_TOOLTIP
        msgTypeRmvBtn->setToolTip(QApplication::translate("MessageConfig", "Remove the selected entry from the current Message Type configuration.", 0));
#endif // QT_NO_TOOLTIP
        msgTypeRmvBtn->setText(QApplication::translate("MessageConfig", "Remove", 0));
#ifndef QT_NO_TOOLTIP
        msgTypeTableView->setToolTip(QApplication::translate("MessageConfig", "<html><head/><body><p>Message Type configuration browser which shows all currently available Message Types and their parsing configuration.</p><p>Either load a whole Message Type configuration with the Load button or Add/Remove Message Types to the current configuration. </p><p>The current configuration can be saved (*.json) with the store button.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class MessageConfig: public Ui_MessageConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGECONFIG_H
