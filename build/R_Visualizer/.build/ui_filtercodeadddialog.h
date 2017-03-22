/********************************************************************************
** Form generated from reading UI file 'filtercodeadddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERCODEADDDIALOG_H
#define UI_FILTERCODEADDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <codelineedit.h>

QT_BEGIN_NAMESPACE

class Ui_FilterCodeAddDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *codeTypeLbl;
    CodeLineEdit *codeTypeLe;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FilterCodeAddDialog)
    {
        if (FilterCodeAddDialog->objectName().isEmpty())
            FilterCodeAddDialog->setObjectName(QStringLiteral("FilterCodeAddDialog"));
        FilterCodeAddDialog->resize(376, 70);
        verticalLayout = new QVBoxLayout(FilterCodeAddDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        codeTypeLbl = new QLabel(FilterCodeAddDialog);
        codeTypeLbl->setObjectName(QStringLiteral("codeTypeLbl"));

        formLayout->setWidget(0, QFormLayout::LabelRole, codeTypeLbl);

        codeTypeLe = new CodeLineEdit(FilterCodeAddDialog);
        codeTypeLe->setObjectName(QStringLiteral("codeTypeLe"));

        formLayout->setWidget(0, QFormLayout::FieldRole, codeTypeLe);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(FilterCodeAddDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(FilterCodeAddDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FilterCodeAddDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FilterCodeAddDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FilterCodeAddDialog);
    } // setupUi

    void retranslateUi(QDialog *FilterCodeAddDialog)
    {
        FilterCodeAddDialog->setWindowTitle(QApplication::translate("FilterCodeAddDialog", "Dialog", 0));
        codeTypeLbl->setText(QApplication::translate("FilterCodeAddDialog", "Code/Type: ", 0));
    } // retranslateUi

};

namespace Ui {
    class FilterCodeAddDialog: public Ui_FilterCodeAddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERCODEADDDIALOG_H
