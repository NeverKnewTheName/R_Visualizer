/********************************************************************************
** Form generated from reading UI file 'sendmessages.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDMESSAGES_H
#define UI_SENDMESSAGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include <codelineedit.h>
#include <idlineedit.h>

QT_BEGIN_NAMESPACE

class Ui_SendMessages
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QTableView *sndPcktTableView;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *sndPcktAddBtn;
    QPushButton *sndPcktRmvBtn;
    QPushButton *sndPcktClrBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *sndPcktLoadBtn;
    QPushButton *sndPcktStoreBtn;
    QPushButton *sndPcktSendBtn;
    QLabel *label_7;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_2;
    IDLineEdit *sndMsgIDLineEdit;
    CodeLineEdit *sndMsgCodeLineEdit;
    QLineEdit *sndMsgMsgLineEdit;
    QComboBox *msgDataFormatComboBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *sndMsgAddToPacketBtn;
    QPushButton *sndMsgSendBtn;

    void setupUi(QWidget *SendMessages)
    {
        if (SendMessages->objectName().isEmpty())
            SendMessages->setObjectName(QStringLiteral("SendMessages"));
        SendMessages->resize(627, 706);
        gridLayout = new QGridLayout(SendMessages);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_3 = new QGroupBox(SendMessages);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        sndPcktTableView = new QTableView(groupBox_3);
        sndPcktTableView->setObjectName(QStringLiteral("sndPcktTableView"));

        gridLayout_2->addWidget(sndPcktTableView, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        sndPcktAddBtn = new QPushButton(groupBox_3);
        sndPcktAddBtn->setObjectName(QStringLiteral("sndPcktAddBtn"));

        horizontalLayout_4->addWidget(sndPcktAddBtn);

        sndPcktRmvBtn = new QPushButton(groupBox_3);
        sndPcktRmvBtn->setObjectName(QStringLiteral("sndPcktRmvBtn"));

        horizontalLayout_4->addWidget(sndPcktRmvBtn);

        sndPcktClrBtn = new QPushButton(groupBox_3);
        sndPcktClrBtn->setObjectName(QStringLiteral("sndPcktClrBtn"));

        horizontalLayout_4->addWidget(sndPcktClrBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        sndPcktLoadBtn = new QPushButton(groupBox_3);
        sndPcktLoadBtn->setObjectName(QStringLiteral("sndPcktLoadBtn"));

        horizontalLayout_4->addWidget(sndPcktLoadBtn);

        sndPcktStoreBtn = new QPushButton(groupBox_3);
        sndPcktStoreBtn->setObjectName(QStringLiteral("sndPcktStoreBtn"));

        horizontalLayout_4->addWidget(sndPcktStoreBtn);

        sndPcktSendBtn = new QPushButton(groupBox_3);
        sndPcktSendBtn->setObjectName(QStringLiteral("sndPcktSendBtn"));

        horizontalLayout_4->addWidget(sndPcktSendBtn);


        gridLayout_2->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox = new QGroupBox(SendMessages);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 0, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 0, 3, 1, 1);

        sndMsgIDLineEdit = new IDLineEdit(groupBox);
        sndMsgIDLineEdit->setObjectName(QStringLiteral("sndMsgIDLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sndMsgIDLineEdit->sizePolicy().hasHeightForWidth());
        sndMsgIDLineEdit->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(sndMsgIDLineEdit, 1, 0, 1, 1);

        sndMsgCodeLineEdit = new CodeLineEdit(groupBox);
        sndMsgCodeLineEdit->setObjectName(QStringLiteral("sndMsgCodeLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sndMsgCodeLineEdit->sizePolicy().hasHeightForWidth());
        sndMsgCodeLineEdit->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(sndMsgCodeLineEdit, 1, 1, 1, 1);

        sndMsgMsgLineEdit = new QLineEdit(groupBox);
        sndMsgMsgLineEdit->setObjectName(QStringLiteral("sndMsgMsgLineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(8);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sndMsgMsgLineEdit->sizePolicy().hasHeightForWidth());
        sndMsgMsgLineEdit->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(sndMsgMsgLineEdit, 1, 2, 1, 1);

        msgDataFormatComboBox = new QComboBox(groupBox);
        msgDataFormatComboBox->setObjectName(QStringLiteral("msgDataFormatComboBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(msgDataFormatComboBox->sizePolicy().hasHeightForWidth());
        msgDataFormatComboBox->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(msgDataFormatComboBox, 1, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        sndMsgAddToPacketBtn = new QPushButton(groupBox);
        sndMsgAddToPacketBtn->setObjectName(QStringLiteral("sndMsgAddToPacketBtn"));

        horizontalLayout->addWidget(sndMsgAddToPacketBtn);


        gridLayout_3->addLayout(horizontalLayout, 2, 1, 1, 2);

        sndMsgSendBtn = new QPushButton(groupBox);
        sndMsgSendBtn->setObjectName(QStringLiteral("sndMsgSendBtn"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(sndMsgSendBtn->sizePolicy().hasHeightForWidth());
        sndMsgSendBtn->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(sndMsgSendBtn, 2, 3, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        QWidget::setTabOrder(sndMsgIDLineEdit, sndMsgCodeLineEdit);
        QWidget::setTabOrder(sndMsgCodeLineEdit, sndPcktTableView);
        QWidget::setTabOrder(sndPcktTableView, sndPcktSendBtn);
        QWidget::setTabOrder(sndPcktSendBtn, sndPcktLoadBtn);
        QWidget::setTabOrder(sndPcktLoadBtn, sndPcktStoreBtn);
        QWidget::setTabOrder(sndPcktStoreBtn, sndPcktAddBtn);
        QWidget::setTabOrder(sndPcktAddBtn, sndPcktRmvBtn);

        retranslateUi(SendMessages);

        QMetaObject::connectSlotsByName(SendMessages);
    } // setupUi

    void retranslateUi(QWidget *SendMessages)
    {
        SendMessages->setWindowTitle(QApplication::translate("SendMessages", "SendMessages", 0));
        groupBox_3->setTitle(QApplication::translate("SendMessages", "Send Packet", 0));
#ifndef QT_NO_TOOLTIP
        sndPcktTableView->setToolTip(QApplication::translate("SendMessages", "<html><head/><body><p>Message browser which displays all messages from the loaded or created packet.</p><p>Use System Config to edit the format and depiction of messages.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sndPcktAddBtn->setToolTip(QApplication::translate("SendMessages", "<html><head/><body><p>Add an entry to the current message packet after the current selction.</p><p>If no entry is selcted the new message will be appended to the package</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        sndPcktAddBtn->setText(QApplication::translate("SendMessages", "Add", 0));
#ifndef QT_NO_TOOLTIP
        sndPcktRmvBtn->setToolTip(QApplication::translate("SendMessages", "<html><head/><body><p>Remvoe the selected entry from the current message packet.</p><p>If no message is selected nothing will happen.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        sndPcktRmvBtn->setText(QApplication::translate("SendMessages", "Remove", 0));
        sndPcktClrBtn->setText(QApplication::translate("SendMessages", "Clear", 0));
#ifndef QT_NO_TOOLTIP
        sndPcktLoadBtn->setToolTip(QApplication::translate("SendMessages", "Load a message packet (*.json or *.csv)", 0));
#endif // QT_NO_TOOLTIP
        sndPcktLoadBtn->setText(QApplication::translate("SendMessages", "Load", 0));
#ifndef QT_NO_TOOLTIP
        sndPcktStoreBtn->setToolTip(QApplication::translate("SendMessages", "Save the current message packet (*.json or *.csv)", 0));
#endif // QT_NO_TOOLTIP
        sndPcktStoreBtn->setText(QApplication::translate("SendMessages", "Store", 0));
#ifndef QT_NO_TOOLTIP
        sndPcktSendBtn->setToolTip(QApplication::translate("SendMessages", "Send the current message packet", 0));
#endif // QT_NO_TOOLTIP
        sndPcktSendBtn->setText(QApplication::translate("SendMessages", "Send", 0));
        label_7->setText(QApplication::translate("SendMessages", "Packet:", 0));
        groupBox->setTitle(QApplication::translate("SendMessages", "Send Single Message", 0));
        label_5->setText(QApplication::translate("SendMessages", "ID/Name", 0));
        label->setText(QApplication::translate("SendMessages", "Code", 0));
        label_6->setText(QApplication::translate("SendMessages", "Message", 0));
        label_2->setText(QApplication::translate("SendMessages", "Format", 0));
        sndMsgIDLineEdit->setInputMask(QString());
        sndMsgCodeLineEdit->setInputMask(QString());
        sndMsgCodeLineEdit->setText(QString());
        sndMsgMsgLineEdit->setInputMask(QApplication::translate("SendMessages", "\\0\\xhhhhhhhhhhhhhh", 0));
        sndMsgMsgLineEdit->setText(QApplication::translate("SendMessages", "0x", 0));
        sndMsgAddToPacketBtn->setText(QApplication::translate("SendMessages", "Add to Packet", 0));
        sndMsgSendBtn->setText(QApplication::translate("SendMessages", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class SendMessages: public Ui_SendMessages {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDMESSAGES_H
