/********************************************************************************
** Form generated from reading UI file 'systemoverview.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMOVERVIEW_H
#define UI_SYSTEMOVERVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <SystemOverview/inc/sysoverviewgraphicsview.h>

QT_BEGIN_NAMESPACE

class Ui_SystemOverview
{
public:
    QHBoxLayout *horizontalLayout;
    SysOverviewGraphicsView *visualizerGraphicsView;

    void setupUi(QWidget *SystemOverview)
    {
        if (SystemOverview->objectName().isEmpty())
            SystemOverview->setObjectName(QStringLiteral("SystemOverview"));
        SystemOverview->resize(577, 700);
        horizontalLayout = new QHBoxLayout(SystemOverview);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        visualizerGraphicsView = new SysOverviewGraphicsView(SystemOverview);
        visualizerGraphicsView->setObjectName(QStringLiteral("visualizerGraphicsView"));

        horizontalLayout->addWidget(visualizerGraphicsView);


        retranslateUi(SystemOverview);

        QMetaObject::connectSlotsByName(SystemOverview);
    } // setupUi

    void retranslateUi(QWidget *SystemOverview)
    {
        SystemOverview->setWindowTitle(QApplication::translate("SystemOverview", "SystemOverview", 0));
    } // retranslateUi

};

namespace Ui {
    class SystemOverview: public Ui_SystemOverview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMOVERVIEW_H
