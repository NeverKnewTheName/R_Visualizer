/********************************************************************************
** Form generated from reading UI file 'messagestream.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGESTREAM_H
#define UI_MESSAGESTREAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessageStream
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *msgStreamTV;
    QHBoxLayout *horizontalLayout;
    QPushButton *scrollTopBtn;
    QPushButton *scrollBotBtn;

    void setupUi(QWidget *MessageStream)
    {
        if (MessageStream->objectName().isEmpty())
            MessageStream->setObjectName(QStringLiteral("MessageStream"));
        MessageStream->resize(607, 675);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MessageStream->sizePolicy().hasHeightForWidth());
        MessageStream->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(MessageStream);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        msgStreamTV = new QTableView(MessageStream);
        msgStreamTV->setObjectName(QStringLiteral("msgStreamTV"));

        verticalLayout->addWidget(msgStreamTV);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        scrollTopBtn = new QPushButton(MessageStream);
        scrollTopBtn->setObjectName(QStringLiteral("scrollTopBtn"));

        horizontalLayout->addWidget(scrollTopBtn);

        scrollBotBtn = new QPushButton(MessageStream);
        scrollBotBtn->setObjectName(QStringLiteral("scrollBotBtn"));

        horizontalLayout->addWidget(scrollBotBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MessageStream);

        QMetaObject::connectSlotsByName(MessageStream);
    } // setupUi

    void retranslateUi(QWidget *MessageStream)
    {
        MessageStream->setWindowTitle(QApplication::translate("MessageStream", "Form", 0));
        scrollTopBtn->setText(QApplication::translate("MessageStream", "Scroll to top", 0));
        scrollBotBtn->setText(QApplication::translate("MessageStream", "Scroll to bottom", 0));
    } // retranslateUi

};

namespace Ui {
    class MessageStream: public Ui_MessageStream {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGESTREAM_H
