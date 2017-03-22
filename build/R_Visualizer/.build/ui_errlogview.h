/********************************************************************************
** Form generated from reading UI file 'errlogview.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRLOGVIEW_H
#define UI_ERRLOGVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErrorLogView
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *errorLogView;
    QHBoxLayout *horizontalLayout_2;
    QTableView *errLogTblV;
    QVBoxLayout *verticalLayout_5;
    QPushButton *savePB;
    QPushButton *openPB;
    QSpacerItem *verticalSpacer_2;
    QWidget *errorLogConfig;
    QHBoxLayout *horizontalLayout;
    QTableView *errConfigsTblV;
    QVBoxLayout *verticalLayout_4;
    QPushButton *saveErrConfPB;
    QPushButton *openErrConfPB;
    QPushButton *addErrConfPB;
    QPushButton *removeErrConfPB;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *closePB;

    void setupUi(QDialog *ErrorLogView)
    {
        if (ErrorLogView->objectName().isEmpty())
            ErrorLogView->setObjectName(QStringLiteral("ErrorLogView"));
        ErrorLogView->resize(614, 504);
        verticalLayout_2 = new QVBoxLayout(ErrorLogView);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(ErrorLogView);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        errorLogView = new QWidget();
        errorLogView->setObjectName(QStringLiteral("errorLogView"));
        horizontalLayout_2 = new QHBoxLayout(errorLogView);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        errLogTblV = new QTableView(errorLogView);
        errLogTblV->setObjectName(QStringLiteral("errLogTblV"));

        horizontalLayout_2->addWidget(errLogTblV);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        savePB = new QPushButton(errorLogView);
        savePB->setObjectName(QStringLiteral("savePB"));

        verticalLayout_5->addWidget(savePB);

        openPB = new QPushButton(errorLogView);
        openPB->setObjectName(QStringLiteral("openPB"));

        verticalLayout_5->addWidget(openPB);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_5);

        tabWidget->addTab(errorLogView, QString());
        errorLogConfig = new QWidget();
        errorLogConfig->setObjectName(QStringLiteral("errorLogConfig"));
        horizontalLayout = new QHBoxLayout(errorLogConfig);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        errConfigsTblV = new QTableView(errorLogConfig);
        errConfigsTblV->setObjectName(QStringLiteral("errConfigsTblV"));

        horizontalLayout->addWidget(errConfigsTblV);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        saveErrConfPB = new QPushButton(errorLogConfig);
        saveErrConfPB->setObjectName(QStringLiteral("saveErrConfPB"));

        verticalLayout_4->addWidget(saveErrConfPB);

        openErrConfPB = new QPushButton(errorLogConfig);
        openErrConfPB->setObjectName(QStringLiteral("openErrConfPB"));

        verticalLayout_4->addWidget(openErrConfPB);

        addErrConfPB = new QPushButton(errorLogConfig);
        addErrConfPB->setObjectName(QStringLiteral("addErrConfPB"));

        verticalLayout_4->addWidget(addErrConfPB);

        removeErrConfPB = new QPushButton(errorLogConfig);
        removeErrConfPB->setObjectName(QStringLiteral("removeErrConfPB"));

        verticalLayout_4->addWidget(removeErrConfPB);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_4);

        tabWidget->addTab(errorLogConfig, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        closePB = new QPushButton(ErrorLogView);
        closePB->setObjectName(QStringLiteral("closePB"));

        horizontalLayout_3->addWidget(closePB);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(ErrorLogView);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ErrorLogView);
    } // setupUi

    void retranslateUi(QDialog *ErrorLogView)
    {
        ErrorLogView->setWindowTitle(QApplication::translate("ErrorLogView", "Dialog", 0));
        savePB->setText(QApplication::translate("ErrorLogView", "Save", 0));
        openPB->setText(QApplication::translate("ErrorLogView", "Open", 0));
        tabWidget->setTabText(tabWidget->indexOf(errorLogView), QApplication::translate("ErrorLogView", "Error Log", 0));
        saveErrConfPB->setText(QApplication::translate("ErrorLogView", "Save", 0));
        openErrConfPB->setText(QApplication::translate("ErrorLogView", "Open", 0));
        addErrConfPB->setText(QApplication::translate("ErrorLogView", "Add", 0));
        removeErrConfPB->setText(QApplication::translate("ErrorLogView", "Remove", 0));
        tabWidget->setTabText(tabWidget->indexOf(errorLogConfig), QApplication::translate("ErrorLogView", "Config", 0));
        closePB->setText(QApplication::translate("ErrorLogView", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class ErrorLogView: public Ui_ErrorLogView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRLOGVIEW_H
