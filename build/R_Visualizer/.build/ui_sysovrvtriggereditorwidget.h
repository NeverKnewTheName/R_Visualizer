/********************************************************************************
** Form generated from reading UI file 'sysovrvtriggereditorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSOVRVTRIGGEREDITORWIDGET_H
#define UI_SYSOVRVTRIGGEREDITORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SysOvrvTriggerEditorWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *IDLabel;
    QLineEdit *IDLineEdit;
    QLabel *CodeLabel;
    QLineEdit *CodeLineEdit;
    QLabel *TriggerTypeLabel;
    QComboBox *TriggerTypeComboBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QTableView *EvaluatorTableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *AddEvaluatorPushButton;
    QPushButton *EditEvaluatorPushButton;
    QPushButton *RemoveEvaluatorPushButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *SysOvrvTriggerEditorWidget)
    {
        if (SysOvrvTriggerEditorWidget->objectName().isEmpty())
            SysOvrvTriggerEditorWidget->setObjectName(QStringLiteral("SysOvrvTriggerEditorWidget"));
        SysOvrvTriggerEditorWidget->resize(867, 819);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SysOvrvTriggerEditorWidget->sizePolicy().hasHeightForWidth());
        SysOvrvTriggerEditorWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(SysOvrvTriggerEditorWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        IDLabel = new QLabel(SysOvrvTriggerEditorWidget);
        IDLabel->setObjectName(QStringLiteral("IDLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, IDLabel);

        IDLineEdit = new QLineEdit(SysOvrvTriggerEditorWidget);
        IDLineEdit->setObjectName(QStringLiteral("IDLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, IDLineEdit);

        CodeLabel = new QLabel(SysOvrvTriggerEditorWidget);
        CodeLabel->setObjectName(QStringLiteral("CodeLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, CodeLabel);

        CodeLineEdit = new QLineEdit(SysOvrvTriggerEditorWidget);
        CodeLineEdit->setObjectName(QStringLiteral("CodeLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, CodeLineEdit);

        TriggerTypeLabel = new QLabel(SysOvrvTriggerEditorWidget);
        TriggerTypeLabel->setObjectName(QStringLiteral("TriggerTypeLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, TriggerTypeLabel);

        TriggerTypeComboBox = new QComboBox(SysOvrvTriggerEditorWidget);
        TriggerTypeComboBox->setObjectName(QStringLiteral("TriggerTypeComboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, TriggerTypeComboBox);


        verticalLayout->addLayout(formLayout);

        groupBox = new QGroupBox(SysOvrvTriggerEditorWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(SysOvrvTriggerEditorWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        EvaluatorTableView = new QTableView(groupBox_2);
        EvaluatorTableView->setObjectName(QStringLiteral("EvaluatorTableView"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(EvaluatorTableView->sizePolicy().hasHeightForWidth());
        EvaluatorTableView->setSizePolicy(sizePolicy2);
        EvaluatorTableView->setAlternatingRowColors(true);
        EvaluatorTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        EvaluatorTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        EvaluatorTableView->horizontalHeader()->setDefaultSectionSize(200);
        EvaluatorTableView->horizontalHeader()->setStretchLastSection(true);
        EvaluatorTableView->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(EvaluatorTableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        AddEvaluatorPushButton = new QPushButton(groupBox_2);
        AddEvaluatorPushButton->setObjectName(QStringLiteral("AddEvaluatorPushButton"));

        horizontalLayout->addWidget(AddEvaluatorPushButton);

        EditEvaluatorPushButton = new QPushButton(groupBox_2);
        EditEvaluatorPushButton->setObjectName(QStringLiteral("EditEvaluatorPushButton"));

        horizontalLayout->addWidget(EditEvaluatorPushButton);

        RemoveEvaluatorPushButton = new QPushButton(groupBox_2);
        RemoveEvaluatorPushButton->setObjectName(QStringLiteral("RemoveEvaluatorPushButton"));

        horizontalLayout->addWidget(RemoveEvaluatorPushButton);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox_2);

        buttonBox = new QDialogButtonBox(SysOvrvTriggerEditorWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SysOvrvTriggerEditorWidget);

        QMetaObject::connectSlotsByName(SysOvrvTriggerEditorWidget);
    } // setupUi

    void retranslateUi(QWidget *SysOvrvTriggerEditorWidget)
    {
        SysOvrvTriggerEditorWidget->setWindowTitle(QApplication::translate("SysOvrvTriggerEditorWidget", "Trigger editor", 0));
        IDLabel->setText(QApplication::translate("SysOvrvTriggerEditorWidget", "ID", 0));
        CodeLabel->setText(QApplication::translate("SysOvrvTriggerEditorWidget", "Code", 0));
        TriggerTypeLabel->setText(QApplication::translate("SysOvrvTriggerEditorWidget", "TriggerType", 0));
        groupBox->setTitle(QApplication::translate("SysOvrvTriggerEditorWidget", "GroupBox", 0));
        pushButton->setText(QApplication::translate("SysOvrvTriggerEditorWidget", "Pick Color", 0));
        groupBox_2->setTitle(QApplication::translate("SysOvrvTriggerEditorWidget", "Evaluators", 0));
        AddEvaluatorPushButton->setText(QApplication::translate("SysOvrvTriggerEditorWidget", "Add Evaluator", 0));
        EditEvaluatorPushButton->setText(QApplication::translate("SysOvrvTriggerEditorWidget", "Edit Evaluator", 0));
        RemoveEvaluatorPushButton->setText(QApplication::translate("SysOvrvTriggerEditorWidget", "Remove Evaluator", 0));
    } // retranslateUi

};

namespace Ui {
    class SysOvrvTriggerEditorWidget: public Ui_SysOvrvTriggerEditorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSOVRVTRIGGEREDITORWIDGET_H
