/********************************************************************************
** Form generated from reading UI file 'msgdisplaywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGDISPLAYWIDGET_H
#define UI_MSGDISPLAYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsgDisplayWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *IDLineEdit;
    QSpacerItem *verticalSpacer;
    QTextEdit *DataTextEdit;

    void setupUi(QWidget *MsgDisplayWidget)
    {
        if (MsgDisplayWidget->objectName().isEmpty())
            MsgDisplayWidget->setObjectName(QStringLiteral("MsgDisplayWidget"));
        MsgDisplayWidget->resize(661, 67);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MsgDisplayWidget->sizePolicy().hasHeightForWidth());
        MsgDisplayWidget->setSizePolicy(sizePolicy);
        MsgDisplayWidget->setAutoFillBackground(false);
        MsgDisplayWidget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(MsgDisplayWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(MsgDisplayWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(MsgDisplayWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(6);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        IDLineEdit = new QLineEdit(MsgDisplayWidget);
        IDLineEdit->setObjectName(QStringLiteral("IDLineEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(IDLineEdit->sizePolicy().hasHeightForWidth());
        IDLineEdit->setSizePolicy(sizePolicy3);
        IDLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        IDLineEdit->setReadOnly(true);

        verticalLayout->addWidget(IDLineEdit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        DataTextEdit = new QTextEdit(MsgDisplayWidget);
        DataTextEdit->setObjectName(QStringLiteral("DataTextEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(6);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(DataTextEdit->sizePolicy().hasHeightForWidth());
        DataTextEdit->setSizePolicy(sizePolicy4);
        DataTextEdit->setMinimumSize(QSize(0, 22));
        DataTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DataTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DataTextEdit->setReadOnly(true);

        gridLayout->addWidget(DataTextEdit, 1, 1, 1, 1);


        retranslateUi(MsgDisplayWidget);

        QMetaObject::connectSlotsByName(MsgDisplayWidget);
    } // setupUi

    void retranslateUi(QWidget *MsgDisplayWidget)
    {
        MsgDisplayWidget->setWindowTitle(QApplication::translate("MsgDisplayWidget", "Form", 0));
        label->setText(QApplication::translate("MsgDisplayWidget", "Identifier", 0));
        label_2->setText(QApplication::translate("MsgDisplayWidget", "Data", 0));
        IDLineEdit->setText(QApplication::translate("MsgDisplayWidget", "TESTTEXT", 0));
        DataTextEdit->setHtml(QApplication::translate("MsgDisplayWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">MsgData: Code - 0x00 Data - 0x00 0x00 0x00 0x00 0x00 0x00 0x00</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MsgDisplayWidget: public Ui_MsgDisplayWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGDISPLAYWIDGET_H
