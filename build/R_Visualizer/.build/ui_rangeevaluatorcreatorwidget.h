/********************************************************************************
** Form generated from reading UI file 'rangeevaluatorcreatorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANGEEVALUATORCREATORWIDGET_H
#define UI_RANGEEVALUATORCREATORWIDGET_H

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

class Ui_RangeEvaluatorCreatorWidget
{
public:
    QFormLayout *formLayout;
    QLabel *DataTypeLabel;
    QComboBox *DataTypeComboBox;
    QComboBox *EvalOpComboBox;
    QLabel *EvalOpLabel;
    QLabel *LowerBoundaryValueLabel;
    QLineEdit *LowerBoundaryValueLineEdit;
    QLabel *UpperBoundaryLabel;
    QLineEdit *UpperBoundaryValueLineEdit;

    void setupUi(QWidget *RangeEvaluatorCreatorWidget)
    {
        if (RangeEvaluatorCreatorWidget->objectName().isEmpty())
            RangeEvaluatorCreatorWidget->setObjectName(QStringLiteral("RangeEvaluatorCreatorWidget"));
        RangeEvaluatorCreatorWidget->resize(372, 146);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RangeEvaluatorCreatorWidget->sizePolicy().hasHeightForWidth());
        RangeEvaluatorCreatorWidget->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(RangeEvaluatorCreatorWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        DataTypeLabel = new QLabel(RangeEvaluatorCreatorWidget);
        DataTypeLabel->setObjectName(QStringLiteral("DataTypeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, DataTypeLabel);

        DataTypeComboBox = new QComboBox(RangeEvaluatorCreatorWidget);
        DataTypeComboBox->setObjectName(QStringLiteral("DataTypeComboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, DataTypeComboBox);

        EvalOpComboBox = new QComboBox(RangeEvaluatorCreatorWidget);
        EvalOpComboBox->setObjectName(QStringLiteral("EvalOpComboBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, EvalOpComboBox);

        EvalOpLabel = new QLabel(RangeEvaluatorCreatorWidget);
        EvalOpLabel->setObjectName(QStringLiteral("EvalOpLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, EvalOpLabel);

        LowerBoundaryValueLabel = new QLabel(RangeEvaluatorCreatorWidget);
        LowerBoundaryValueLabel->setObjectName(QStringLiteral("LowerBoundaryValueLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, LowerBoundaryValueLabel);

        LowerBoundaryValueLineEdit = new QLineEdit(RangeEvaluatorCreatorWidget);
        LowerBoundaryValueLineEdit->setObjectName(QStringLiteral("LowerBoundaryValueLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, LowerBoundaryValueLineEdit);

        UpperBoundaryLabel = new QLabel(RangeEvaluatorCreatorWidget);
        UpperBoundaryLabel->setObjectName(QStringLiteral("UpperBoundaryLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, UpperBoundaryLabel);

        UpperBoundaryValueLineEdit = new QLineEdit(RangeEvaluatorCreatorWidget);
        UpperBoundaryValueLineEdit->setObjectName(QStringLiteral("UpperBoundaryValueLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, UpperBoundaryValueLineEdit);


        retranslateUi(RangeEvaluatorCreatorWidget);

        QMetaObject::connectSlotsByName(RangeEvaluatorCreatorWidget);
    } // setupUi

    void retranslateUi(QWidget *RangeEvaluatorCreatorWidget)
    {
        RangeEvaluatorCreatorWidget->setWindowTitle(QApplication::translate("RangeEvaluatorCreatorWidget", "Form", 0));
        DataTypeLabel->setText(QApplication::translate("RangeEvaluatorCreatorWidget", "Data type:", 0));
        EvalOpLabel->setText(QApplication::translate("RangeEvaluatorCreatorWidget", "Evaluation operation:", 0));
        LowerBoundaryValueLabel->setText(QApplication::translate("RangeEvaluatorCreatorWidget", "Lower boundary", 0));
        UpperBoundaryLabel->setText(QApplication::translate("RangeEvaluatorCreatorWidget", "Upper boundary", 0));
    } // retranslateUi

};

namespace Ui {
    class RangeEvaluatorCreatorWidget: public Ui_RangeEvaluatorCreatorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANGEEVALUATORCREATORWIDGET_H
