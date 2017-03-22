/********************************************************************************
** Form generated from reading UI file 'limitevaluatorcreatorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIMITEVALUATORCREATORWIDGET_H
#define UI_LIMITEVALUATORCREATORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LimitEvaluatorCreatorWidget
{
public:
    QFormLayout *formLayout;
    QLabel *DataTypeLabel;
    QComboBox *DataTypeComboBox;
    QLabel *LimitValueLabel;
    QLineEdit *LimitValueLineEdit;
    QLabel *EvalOpLabel;
    QComboBox *EvalOpComboBox;

    void setupUi(QWidget *LimitEvaluatorCreatorWidget)
    {
        if (LimitEvaluatorCreatorWidget->objectName().isEmpty())
            LimitEvaluatorCreatorWidget->setObjectName(QStringLiteral("LimitEvaluatorCreatorWidget"));
        LimitEvaluatorCreatorWidget->resize(339, 108);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LimitEvaluatorCreatorWidget->sizePolicy().hasHeightForWidth());
        LimitEvaluatorCreatorWidget->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(LimitEvaluatorCreatorWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        DataTypeLabel = new QLabel(LimitEvaluatorCreatorWidget);
        DataTypeLabel->setObjectName(QStringLiteral("DataTypeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, DataTypeLabel);

        DataTypeComboBox = new QComboBox(LimitEvaluatorCreatorWidget);
        DataTypeComboBox->setObjectName(QStringLiteral("DataTypeComboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, DataTypeComboBox);

        LimitValueLabel = new QLabel(LimitEvaluatorCreatorWidget);
        LimitValueLabel->setObjectName(QStringLiteral("LimitValueLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, LimitValueLabel);

        LimitValueLineEdit = new QLineEdit(LimitEvaluatorCreatorWidget);
        LimitValueLineEdit->setObjectName(QStringLiteral("LimitValueLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, LimitValueLineEdit);

        EvalOpLabel = new QLabel(LimitEvaluatorCreatorWidget);
        EvalOpLabel->setObjectName(QStringLiteral("EvalOpLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, EvalOpLabel);

        EvalOpComboBox = new QComboBox(LimitEvaluatorCreatorWidget);
        EvalOpComboBox->setObjectName(QStringLiteral("EvalOpComboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, EvalOpComboBox);


        retranslateUi(LimitEvaluatorCreatorWidget);

        QMetaObject::connectSlotsByName(LimitEvaluatorCreatorWidget);
    } // setupUi

    void retranslateUi(QWidget *LimitEvaluatorCreatorWidget)
    {
        LimitEvaluatorCreatorWidget->setWindowTitle(QApplication::translate("LimitEvaluatorCreatorWidget", "Form", 0));
        DataTypeLabel->setText(QApplication::translate("LimitEvaluatorCreatorWidget", "Data type:", 0));
        LimitValueLabel->setText(QApplication::translate("LimitEvaluatorCreatorWidget", "Limit value:", 0));
        EvalOpLabel->setText(QApplication::translate("LimitEvaluatorCreatorWidget", "Evaluation operation:", 0));
    } // retranslateUi

};

namespace Ui {
    class LimitEvaluatorCreatorWidget: public Ui_LimitEvaluatorCreatorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIMITEVALUATORCREATORWIDGET_H
