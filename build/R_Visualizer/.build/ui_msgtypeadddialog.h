/********************************************************************************
** Form generated from reading UI file 'msgtypeadddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGTYPEADDDIALOG_H
#define UI_MSGTYPEADDDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_MsgTypeAddDialog
{
public:
    QFormLayout *formLayout;
    QLabel *codeLabel;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *codeLineEdit;
    QComboBox *numericallFormatComboBox;
    QSpacerItem *horizontalSpacer;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *dataFormatLabel;
    QPlainTextEdit *formatPlainTextEdit;
    QLabel *colorLabel;
    QHBoxLayout *horizontalLayout;
    QLineEdit *colorLineEdit;
    QPushButton *colorPickerPushButton;
    QDialogButtonBox *buttonBox;
    QPushButton *formatterPushButton;

    void setupUi(QDialog *MsgTypeAddDialog)
    {
        if (MsgTypeAddDialog->objectName().isEmpty())
            MsgTypeAddDialog->setObjectName(QStringLiteral("MsgTypeAddDialog"));
        MsgTypeAddDialog->resize(408, 332);
        formLayout = new QFormLayout(MsgTypeAddDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        codeLabel = new QLabel(MsgTypeAddDialog);
        codeLabel->setObjectName(QStringLiteral("codeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, codeLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        codeLineEdit = new QLineEdit(MsgTypeAddDialog);
        codeLineEdit->setObjectName(QStringLiteral("codeLineEdit"));
        codeLineEdit->setMinimumSize(QSize(100, 0));
        codeLineEdit->setFocusPolicy(Qt::ClickFocus);
        codeLineEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        codeLineEdit->setMaxLength(4);
        codeLineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);

        horizontalLayout_2->addWidget(codeLineEdit);

        numericallFormatComboBox = new QComboBox(MsgTypeAddDialog);
        numericallFormatComboBox->setObjectName(QStringLiteral("numericallFormatComboBox"));
        numericallFormatComboBox->setMinimumSize(QSize(100, 0));
        numericallFormatComboBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout_2->addWidget(numericallFormatComboBox);

        horizontalSpacer = new QSpacerItem(356, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout_2);

        nameLabel = new QLabel(MsgTypeAddDialog);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(MsgTypeAddDialog);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));
        nameLineEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(2, QFormLayout::FieldRole, nameLineEdit);

        dataFormatLabel = new QLabel(MsgTypeAddDialog);
        dataFormatLabel->setObjectName(QStringLiteral("dataFormatLabel"));

        formLayout->setWidget(4, QFormLayout::SpanningRole, dataFormatLabel);

        formatPlainTextEdit = new QPlainTextEdit(MsgTypeAddDialog);
        formatPlainTextEdit->setObjectName(QStringLiteral("formatPlainTextEdit"));
        formatPlainTextEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(5, QFormLayout::FieldRole, formatPlainTextEdit);

        colorLabel = new QLabel(MsgTypeAddDialog);
        colorLabel->setObjectName(QStringLiteral("colorLabel"));

        formLayout->setWidget(7, QFormLayout::LabelRole, colorLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        colorLineEdit = new QLineEdit(MsgTypeAddDialog);
        colorLineEdit->setObjectName(QStringLiteral("colorLineEdit"));
        colorLineEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout->addWidget(colorLineEdit);

        colorPickerPushButton = new QPushButton(MsgTypeAddDialog);
        colorPickerPushButton->setObjectName(QStringLiteral("colorPickerPushButton"));
        colorPickerPushButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout->addWidget(colorPickerPushButton);


        formLayout->setLayout(7, QFormLayout::FieldRole, horizontalLayout);

        buttonBox = new QDialogButtonBox(MsgTypeAddDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(9, QFormLayout::FieldRole, buttonBox);

        formatterPushButton = new QPushButton(MsgTypeAddDialog);
        formatterPushButton->setObjectName(QStringLiteral("formatterPushButton"));
        formatterPushButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(6, QFormLayout::FieldRole, formatterPushButton);

        QWidget::setTabOrder(codeLineEdit, nameLineEdit);
        QWidget::setTabOrder(nameLineEdit, formatPlainTextEdit);
        QWidget::setTabOrder(formatPlainTextEdit, formatterPushButton);
        QWidget::setTabOrder(formatterPushButton, colorLineEdit);
        QWidget::setTabOrder(colorLineEdit, colorPickerPushButton);

        retranslateUi(MsgTypeAddDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MsgTypeAddDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MsgTypeAddDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MsgTypeAddDialog);
    } // setupUi

    void retranslateUi(QDialog *MsgTypeAddDialog)
    {
        MsgTypeAddDialog->setWindowTitle(QApplication::translate("MsgTypeAddDialog", "Dialog", 0));
        codeLabel->setText(QApplication::translate("MsgTypeAddDialog", "Code", 0));
#ifndef QT_NO_TOOLTIP
        codeLineEdit->setToolTip(QApplication::translate("MsgTypeAddDialog", "Enter the code for the message to be parsed", 0));
#endif // QT_NO_TOOLTIP
        codeLineEdit->setInputMask(QApplication::translate("MsgTypeAddDialog", "\\0\\xhh", 0));
        codeLineEdit->setPlaceholderText(QString());
#ifndef QT_NO_TOOLTIP
        numericallFormatComboBox->setToolTip(QApplication::translate("MsgTypeAddDialog", "Select the input format of the code", 0));
#endif // QT_NO_TOOLTIP
        nameLabel->setText(QApplication::translate("MsgTypeAddDialog", "Name", 0));
#ifndef QT_NO_TOOLTIP
        nameLineEdit->setToolTip(QApplication::translate("MsgTypeAddDialog", "<html><head/><body><p>Enter the name which shall substitute the code.</p><p>The numerical code will then be replaced in each message by this name.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        nameLineEdit->setPlaceholderText(QApplication::translate("MsgTypeAddDialog", "Name", 0));
        dataFormatLabel->setText(QApplication::translate("MsgTypeAddDialog", "Data Format:", 0));
#ifndef QT_NO_TOOLTIP
        formatPlainTextEdit->setToolTip(QApplication::translate("MsgTypeAddDialog", "<html><head/><body><p>Enter the formatting which shall be applied to the data of the message.</p><p>Use the Formatter by clicking on the button below for simplified input.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        formatPlainTextEdit->setPlaceholderText(QApplication::translate("MsgTypeAddDialog", "Data Format", 0));
        colorLabel->setText(QApplication::translate("MsgTypeAddDialog", "Color", 0));
#ifndef QT_NO_TOOLTIP
        colorLineEdit->setToolTip(QApplication::translate("MsgTypeAddDialog", "<html><head/><body><p>Enter the color for messages with the specified code.</p><p>Use the Color Picker for simplified color selection.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        colorLineEdit->setInputMask(QApplication::translate("MsgTypeAddDialog", "\\#hhhhhh", 0));
        colorLineEdit->setPlaceholderText(QApplication::translate("MsgTypeAddDialog", "#000000", 0));
#ifndef QT_NO_TOOLTIP
        colorPickerPushButton->setToolTip(QApplication::translate("MsgTypeAddDialog", "Call the Color Picker", 0));
#endif // QT_NO_TOOLTIP
        colorPickerPushButton->setText(QApplication::translate("MsgTypeAddDialog", "Color Picker", 0));
#ifndef QT_NO_TOOLTIP
        formatterPushButton->setToolTip(QApplication::translate("MsgTypeAddDialog", "Call the Formatter  to ease input of a message format", 0));
#endif // QT_NO_TOOLTIP
        formatterPushButton->setText(QApplication::translate("MsgTypeAddDialog", "Formatter", 0));
    } // retranslateUi

};

namespace Ui {
    class MsgTypeAddDialog: public Ui_MsgTypeAddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGTYPEADDDIALOG_H
