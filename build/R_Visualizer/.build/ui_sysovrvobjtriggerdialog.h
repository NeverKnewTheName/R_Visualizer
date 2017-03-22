/********************************************************************************
** Form generated from reading UI file 'sysovrvobjtriggerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSOVRVOBJTRIGGERDIALOG_H
#define UI_SYSOVRVOBJTRIGGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QColumnView>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SysOvrvObjTriggerDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QColumnView *TriggerColumnView;
    QVBoxLayout *verticalLayout;
    QPushButton *AddTriggerBtn;
    QPushButton *RemoveTriggerBtn;
    QPushButton *EditTriggerBtn;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SysOvrvObjTriggerDialog)
    {
        if (SysOvrvObjTriggerDialog->objectName().isEmpty())
            SysOvrvObjTriggerDialog->setObjectName(QStringLiteral("SysOvrvObjTriggerDialog"));
        SysOvrvObjTriggerDialog->resize(1106, 647);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SysOvrvObjTriggerDialog->sizePolicy().hasHeightForWidth());
        SysOvrvObjTriggerDialog->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(SysOvrvObjTriggerDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        TriggerColumnView = new QColumnView(SysOvrvObjTriggerDialog);
        TriggerColumnView->setObjectName(QStringLiteral("TriggerColumnView"));
        sizePolicy.setHeightForWidth(TriggerColumnView->sizePolicy().hasHeightForWidth());
        TriggerColumnView->setSizePolicy(sizePolicy);
        TriggerColumnView->setSelectionMode(QAbstractItemView::SingleSelection);

        horizontalLayout->addWidget(TriggerColumnView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        AddTriggerBtn = new QPushButton(SysOvrvObjTriggerDialog);
        AddTriggerBtn->setObjectName(QStringLiteral("AddTriggerBtn"));

        verticalLayout->addWidget(AddTriggerBtn);

        RemoveTriggerBtn = new QPushButton(SysOvrvObjTriggerDialog);
        RemoveTriggerBtn->setObjectName(QStringLiteral("RemoveTriggerBtn"));

        verticalLayout->addWidget(RemoveTriggerBtn);

        EditTriggerBtn = new QPushButton(SysOvrvObjTriggerDialog);
        EditTriggerBtn->setObjectName(QStringLiteral("EditTriggerBtn"));

        verticalLayout->addWidget(EditTriggerBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(SysOvrvObjTriggerDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(SysOvrvObjTriggerDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SysOvrvObjTriggerDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SysOvrvObjTriggerDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SysOvrvObjTriggerDialog);
    } // setupUi

    void retranslateUi(QDialog *SysOvrvObjTriggerDialog)
    {
        SysOvrvObjTriggerDialog->setWindowTitle(QApplication::translate("SysOvrvObjTriggerDialog", "Edit triggers for Object", 0));
        AddTriggerBtn->setText(QApplication::translate("SysOvrvObjTriggerDialog", "Add Trigger", 0));
        RemoveTriggerBtn->setText(QApplication::translate("SysOvrvObjTriggerDialog", "Remove Trigger", 0));
        EditTriggerBtn->setText(QApplication::translate("SysOvrvObjTriggerDialog", "Edit Trigger", 0));
    } // retranslateUi

};

namespace Ui {
    class SysOvrvObjTriggerDialog: public Ui_SysOvrvObjTriggerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSOVRVOBJTRIGGERDIALOG_H
