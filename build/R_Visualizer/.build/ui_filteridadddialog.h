/********************************************************************************
** Form generated from reading UI file 'filteridadddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERIDADDDIALOG_H
#define UI_FILTERIDADDDIALOG_H

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
#include <idlineedit.h>

QT_BEGIN_NAMESPACE

class Ui_FilterIDAddDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *idNameLbl;
    IDLineEdit *idNameLe;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FilterIDAddDialog)
    {
        if (FilterIDAddDialog->objectName().isEmpty())
            FilterIDAddDialog->setObjectName(QStringLiteral("FilterIDAddDialog"));
        FilterIDAddDialog->resize(312, 70);
        verticalLayout = new QVBoxLayout(FilterIDAddDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        idNameLbl = new QLabel(FilterIDAddDialog);
        idNameLbl->setObjectName(QStringLiteral("idNameLbl"));

        formLayout->setWidget(0, QFormLayout::LabelRole, idNameLbl);

        idNameLe = new IDLineEdit(FilterIDAddDialog);
        idNameLe->setObjectName(QStringLiteral("idNameLe"));

        formLayout->setWidget(0, QFormLayout::FieldRole, idNameLe);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(FilterIDAddDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(FilterIDAddDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FilterIDAddDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FilterIDAddDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FilterIDAddDialog);
    } // setupUi

    void retranslateUi(QDialog *FilterIDAddDialog)
    {
        FilterIDAddDialog->setWindowTitle(QApplication::translate("FilterIDAddDialog", "Dialog", 0));
        idNameLbl->setText(QApplication::translate("FilterIDAddDialog", "ID/Name:", 0));
    } // retranslateUi

};

namespace Ui {
    class FilterIDAddDialog: public Ui_FilterIDAddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERIDADDDIALOG_H
