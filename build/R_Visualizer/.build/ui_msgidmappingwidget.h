/********************************************************************************
** Form generated from reading UI file 'msgidmappingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGIDMAPPINGWIDGET_H
#define UI_MSGIDMAPPINGWIDGET_H

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

class Ui_MsgIDMappingWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_4;
    QSpacerItem *storeLoadSpacer;
    QTableView *idTableView;
    QPushButton *idAddBtn;
    QPushButton *idRmvBtn;
    QPushButton *idStoreBtn;
    QPushButton *idLoadBtn;
    QSpacerItem *RemoveAddSpacer;

    void setupUi(QWidget *MsgIDMappingWidget)
    {
        if (MsgIDMappingWidget->objectName().isEmpty())
            MsgIDMappingWidget->setObjectName(QStringLiteral("MsgIDMappingWidget"));
        MsgIDMappingWidget->resize(600, 400);
        verticalLayout = new QVBoxLayout(MsgIDMappingWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_9 = new QGroupBox(MsgIDMappingWidget);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(groupBox_9->sizePolicy().hasHeightForWidth());
        groupBox_9->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(groupBox_9);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        storeLoadSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(storeLoadSpacer, 5, 0, 1, 1);

        idTableView = new QTableView(groupBox_9);
        idTableView->setObjectName(QStringLiteral("idTableView"));

        gridLayout_4->addWidget(idTableView, 0, 0, 5, 5);

        idAddBtn = new QPushButton(groupBox_9);
        idAddBtn->setObjectName(QStringLiteral("idAddBtn"));

        gridLayout_4->addWidget(idAddBtn, 6, 2, 1, 1);

        idRmvBtn = new QPushButton(groupBox_9);
        idRmvBtn->setObjectName(QStringLiteral("idRmvBtn"));

        gridLayout_4->addWidget(idRmvBtn, 6, 1, 1, 1);

        idStoreBtn = new QPushButton(groupBox_9);
        idStoreBtn->setObjectName(QStringLiteral("idStoreBtn"));

        gridLayout_4->addWidget(idStoreBtn, 5, 1, 1, 1);

        idLoadBtn = new QPushButton(groupBox_9);
        idLoadBtn->setObjectName(QStringLiteral("idLoadBtn"));

        gridLayout_4->addWidget(idLoadBtn, 5, 2, 1, 1);

        RemoveAddSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(RemoveAddSpacer, 6, 0, 1, 1);


        verticalLayout->addWidget(groupBox_9);


        retranslateUi(MsgIDMappingWidget);

        QMetaObject::connectSlotsByName(MsgIDMappingWidget);
    } // setupUi

    void retranslateUi(QWidget *MsgIDMappingWidget)
    {
        MsgIDMappingWidget->setWindowTitle(QApplication::translate("MsgIDMappingWidget", "Form", 0));
        groupBox_9->setTitle(QApplication::translate("MsgIDMappingWidget", "MsgID Mapping", 0));
#ifndef QT_NO_TOOLTIP
        idTableView->setToolTip(QApplication::translate("MsgIDMappingWidget", "<html><head/><body><p>ID configuration browser which shows all currently available IDs and their parsing configuration.</p><p>Either load a whole ID configuration with the Load button or Add/Remove  IDs to the current configuration. </p><p>The current configuration can be saved (*.json) with the store button.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        idAddBtn->setToolTip(QApplication::translate("MsgIDMappingWidget", "<html><head/><body><p>Add a new ID configuration entry to the current ID configuration. The ID configuration tool is called.</p><p>The new entry will be appended to the list.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        idAddBtn->setText(QApplication::translate("MsgIDMappingWidget", "Add", 0));
#ifndef QT_NO_TOOLTIP
        idRmvBtn->setToolTip(QApplication::translate("MsgIDMappingWidget", "Remove the selected entry from the current ID configuration.", 0));
#endif // QT_NO_TOOLTIP
        idRmvBtn->setText(QApplication::translate("MsgIDMappingWidget", "Remove", 0));
#ifndef QT_NO_TOOLTIP
        idStoreBtn->setToolTip(QApplication::translate("MsgIDMappingWidget", "Save the current ID configuration (*.json) to a file", 0));
#endif // QT_NO_TOOLTIP
        idStoreBtn->setText(QApplication::translate("MsgIDMappingWidget", "Store", 0));
#ifndef QT_NO_TOOLTIP
        idLoadBtn->setToolTip(QApplication::translate("MsgIDMappingWidget", "Load an ID configuration (*.json)", 0));
#endif // QT_NO_TOOLTIP
        idLoadBtn->setText(QApplication::translate("MsgIDMappingWidget", "Load", 0));
    } // retranslateUi

};

namespace Ui {
    class MsgIDMappingWidget: public Ui_MsgIDMappingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGIDMAPPINGWIDGET_H
