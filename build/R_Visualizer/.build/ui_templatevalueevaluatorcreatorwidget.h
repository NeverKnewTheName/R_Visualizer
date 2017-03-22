/********************************************************************************
** Form generated from reading UI file 'templatevalueevaluatorcreatorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLATEVALUEEVALUATORCREATORWIDGET_H
#define UI_TEMPLATEVALUEEVALUATORCREATORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemplateValueEvaluatorCreatorWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *EvaluatorTypeLabel;
    QComboBox *EvaluatorTypeComboBox;
    QWidget *SpecificValueEvaluatorCreatorWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *AddEvaluatorPushButton;

    void setupUi(QWidget *TemplateValueEvaluatorCreatorWidget)
    {
        if (TemplateValueEvaluatorCreatorWidget->objectName().isEmpty())
            TemplateValueEvaluatorCreatorWidget->setObjectName(QStringLiteral("TemplateValueEvaluatorCreatorWidget"));
        TemplateValueEvaluatorCreatorWidget->resize(394, 271);
        verticalLayout = new QVBoxLayout(TemplateValueEvaluatorCreatorWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(7);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        EvaluatorTypeLabel = new QLabel(TemplateValueEvaluatorCreatorWidget);
        EvaluatorTypeLabel->setObjectName(QStringLiteral("EvaluatorTypeLabel"));

        horizontalLayout->addWidget(EvaluatorTypeLabel);

        EvaluatorTypeComboBox = new QComboBox(TemplateValueEvaluatorCreatorWidget);
        EvaluatorTypeComboBox->setObjectName(QStringLiteral("EvaluatorTypeComboBox"));

        horizontalLayout->addWidget(EvaluatorTypeComboBox);


        verticalLayout->addLayout(horizontalLayout);

        SpecificValueEvaluatorCreatorWidget = new QWidget(TemplateValueEvaluatorCreatorWidget);
        SpecificValueEvaluatorCreatorWidget->setObjectName(QStringLiteral("SpecificValueEvaluatorCreatorWidget"));
        verticalLayout_2 = new QVBoxLayout(SpecificValueEvaluatorCreatorWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(SpecificValueEvaluatorCreatorWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(widget);


        verticalLayout->addWidget(SpecificValueEvaluatorCreatorWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        AddEvaluatorPushButton = new QPushButton(TemplateValueEvaluatorCreatorWidget);
        AddEvaluatorPushButton->setObjectName(QStringLiteral("AddEvaluatorPushButton"));

        horizontalLayout_2->addWidget(AddEvaluatorPushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(TemplateValueEvaluatorCreatorWidget);

        QMetaObject::connectSlotsByName(TemplateValueEvaluatorCreatorWidget);
    } // setupUi

    void retranslateUi(QWidget *TemplateValueEvaluatorCreatorWidget)
    {
        TemplateValueEvaluatorCreatorWidget->setWindowTitle(QApplication::translate("TemplateValueEvaluatorCreatorWidget", "Form", 0));
        EvaluatorTypeLabel->setText(QApplication::translate("TemplateValueEvaluatorCreatorWidget", "Evaluator type:", 0));
        AddEvaluatorPushButton->setText(QApplication::translate("TemplateValueEvaluatorCreatorWidget", "Add Evaluator", 0));
    } // retranslateUi

};

namespace Ui {
    class TemplateValueEvaluatorCreatorWidget: public Ui_TemplateValueEvaluatorCreatorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATEVALUEEVALUATORCREATORWIDGET_H
