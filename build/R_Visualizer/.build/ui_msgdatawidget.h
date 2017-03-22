/********************************************************************************
** Form generated from reading UI file 'msgdatawidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGDATAWIDGET_H
#define UI_MSGDATAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsgDataWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *CodeLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *ShowDataPushButton;
    QTextEdit *DataTextEdit;

    void setupUi(QWidget *MsgDataWidget)
    {
        if (MsgDataWidget->objectName().isEmpty())
            MsgDataWidget->setObjectName(QStringLiteral("MsgDataWidget"));
        MsgDataWidget->resize(148, 77);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MsgDataWidget->sizePolicy().hasHeightForWidth());
        MsgDataWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(MsgDataWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(MsgDataWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        CodeLabel = new QLabel(MsgDataWidget);
        CodeLabel->setObjectName(QStringLiteral("CodeLabel"));
        sizePolicy1.setHeightForWidth(CodeLabel->sizePolicy().hasHeightForWidth());
        CodeLabel->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(CodeLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        ShowDataPushButton = new QPushButton(MsgDataWidget);
        ShowDataPushButton->setObjectName(QStringLiteral("ShowDataPushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ShowDataPushButton->sizePolicy().hasHeightForWidth());
        ShowDataPushButton->setSizePolicy(sizePolicy2);
        ShowDataPushButton->setMinimumSize(QSize(0, 15));
        QFont font;
        font.setPointSize(7);
        ShowDataPushButton->setFont(font);

        verticalLayout->addWidget(ShowDataPushButton);

        DataTextEdit = new QTextEdit(MsgDataWidget);
        DataTextEdit->setObjectName(QStringLiteral("DataTextEdit"));
        DataTextEdit->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(DataTextEdit->sizePolicy().hasHeightForWidth());
        DataTextEdit->setSizePolicy(sizePolicy3);
        DataTextEdit->setMinimumSize(QSize(0, 10));
        DataTextEdit->setMaximumSize(QSize(16777215, 16777215));
        DataTextEdit->setBaseSize(QSize(0, 0));
        DataTextEdit->setAcceptDrops(false);
        DataTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DataTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DataTextEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        DataTextEdit->setUndoRedoEnabled(false);
        DataTextEdit->setReadOnly(true);
        DataTextEdit->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><title>Data</title><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"));
        DataTextEdit->setPlaceholderText(QStringLiteral(""));

        verticalLayout->addWidget(DataTextEdit);


        retranslateUi(MsgDataWidget);

        QMetaObject::connectSlotsByName(MsgDataWidget);
    } // setupUi

    void retranslateUi(QWidget *MsgDataWidget)
    {
        MsgDataWidget->setWindowTitle(QApplication::translate("MsgDataWidget", "Form", 0));
        label->setText(QApplication::translate("MsgDataWidget", "Code: ", 0));
        CodeLabel->setText(QApplication::translate("MsgDataWidget", "placeHolder", 0));
        ShowDataPushButton->setText(QApplication::translate("MsgDataWidget", "More", 0));
        DataTextEdit->setDocumentTitle(QApplication::translate("MsgDataWidget", "Data", 0));
    } // retranslateUi

};

namespace Ui {
    class MsgDataWidget: public Ui_MsgDataWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGDATAWIDGET_H
