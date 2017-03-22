/********************************************************************************
** Form generated from reading UI file 'idadddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDADDDIALOG_H
#define UI_IDADDDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_IDAddDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *idLineEdit;
    QComboBox *numericallFormatComboBox;
    QSpacerItem *horizontalSpacer;
    QLineEdit *nameLineEdit;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *colorLineEdit;
    QPushButton *pushButton;
    QLabel *idLabel;
    QLabel *nameLabel;
    QLabel *colorLabel;

    void setupUi(QDialog *IDAddDialog)
    {
        if (IDAddDialog->objectName().isEmpty())
            IDAddDialog->setObjectName(QStringLiteral("IDAddDialog"));
        IDAddDialog->resize(400, 300);
        gridLayout = new QGridLayout(IDAddDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        idLineEdit = new QLineEdit(IDAddDialog);
        idLineEdit->setObjectName(QStringLiteral("idLineEdit"));
        idLineEdit->setMinimumSize(QSize(100, 0));
        idLineEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        idLineEdit->setFrame(true);
        idLineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);
        idLineEdit->setClearButtonEnabled(false);

        horizontalLayout_2->addWidget(idLineEdit);

        numericallFormatComboBox = new QComboBox(IDAddDialog);
        numericallFormatComboBox->setObjectName(QStringLiteral("numericallFormatComboBox"));
        numericallFormatComboBox->setMinimumSize(QSize(100, 0));
        numericallFormatComboBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout_2->addWidget(numericallFormatComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        nameLineEdit = new QLineEdit(IDAddDialog);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));
        nameLineEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(nameLineEdit, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(IDAddDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        colorLineEdit = new QLineEdit(IDAddDialog);
        colorLineEdit->setObjectName(QStringLiteral("colorLineEdit"));
        colorLineEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout->addWidget(colorLineEdit);

        pushButton = new QPushButton(IDAddDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        pushButton->setFlat(false);

        horizontalLayout->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        idLabel = new QLabel(IDAddDialog);
        idLabel->setObjectName(QStringLiteral("idLabel"));

        gridLayout->addWidget(idLabel, 0, 0, 1, 1);

        nameLabel = new QLabel(IDAddDialog);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        gridLayout->addWidget(nameLabel, 1, 0, 1, 1);

        colorLabel = new QLabel(IDAddDialog);
        colorLabel->setObjectName(QStringLiteral("colorLabel"));

        gridLayout->addWidget(colorLabel, 2, 0, 1, 1);


        retranslateUi(IDAddDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), IDAddDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), IDAddDialog, SLOT(reject()));

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(IDAddDialog);
    } // setupUi

    void retranslateUi(QDialog *IDAddDialog)
    {
        IDAddDialog->setWindowTitle(QApplication::translate("IDAddDialog", "Dialog", 0));
#ifndef QT_NO_TOOLTIP
        idLineEdit->setToolTip(QApplication::translate("IDAddDialog", "Enter the ID for the message to be parsed", 0));
#endif // QT_NO_TOOLTIP
        idLineEdit->setInputMask(QApplication::translate("IDAddDialog", "\\0\\xhhhh", 0));
        idLineEdit->setText(QApplication::translate("IDAddDialog", "0x", 0));
        idLineEdit->setPlaceholderText(QString());
#ifndef QT_NO_TOOLTIP
        numericallFormatComboBox->setToolTip(QApplication::translate("IDAddDialog", "Select the input format of the code", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        nameLineEdit->setToolTip(QApplication::translate("IDAddDialog", "<html><head/><body><p>Enter the name which shall substitute the ID.</p><p>The numerical ID will then be replaced in each message by this name.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        nameLineEdit->setPlaceholderText(QApplication::translate("IDAddDialog", "Name", 0));
#ifndef QT_NO_TOOLTIP
        colorLineEdit->setToolTip(QApplication::translate("IDAddDialog", "<html><head/><body><p>Enter the color for messages with the specified code.</p><p>Use the Color Picker for simplified color selection.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        colorLineEdit->setInputMask(QApplication::translate("IDAddDialog", "\\#hhhhhh", 0));
        colorLineEdit->setPlaceholderText(QApplication::translate("IDAddDialog", "#000000", 0));
#ifndef QT_NO_TOOLTIP
        pushButton->setToolTip(QApplication::translate("IDAddDialog", "Call the Color Picker", 0));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("IDAddDialog", "Color Picker", 0));
        idLabel->setText(QApplication::translate("IDAddDialog", "ID", 0));
        nameLabel->setText(QApplication::translate("IDAddDialog", "Name", 0));
        colorLabel->setText(QApplication::translate("IDAddDialog", "Color", 0));
    } // retranslateUi

};

namespace Ui {
    class IDAddDialog: public Ui_IDAddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDADDDIALOG_H
