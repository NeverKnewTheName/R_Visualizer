/********************************************************************************
** Form generated from reading UI file 'msgtypeformatterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGTYPEFORMATTERDIALOG_H
#define UI_MSGTYPEFORMATTERDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_MsgTypeFormatterDialog
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QLabel *fieldLabel;
    QComboBox *fieldComboBox;
    QPushButton *addFieldPushButton;
    QGridLayout *gridLayout;
    QLabel *operand1Label;
    QLabel *operationLabel;
    QLabel *operand2Label;
    QComboBox *operand1_ComboBox;
    QComboBox *operationComboBox;
    QComboBox *operand2_ComboBox;
    QPushButton *addOperationPushButton;
    QGridLayout *gridLayout_3;
    QLabel *textFormattingLabel;
    QPushButton *AddNewLinepushButton;
    QPushButton *addTabPushButton;
    QSpacerItem *horizontalSpacer;
    QPlainTextEdit *formatPlainTextEdit;
    QLineEdit *formatStringLineEdit;
    QDialogButtonBox *buttonBox;
    QLabel *formatStringLabel;
    QLabel *formatLabel;

    void setupUi(QDialog *MsgTypeFormatterDialog)
    {
        if (MsgTypeFormatterDialog->objectName().isEmpty())
            MsgTypeFormatterDialog->setObjectName(QStringLiteral("MsgTypeFormatterDialog"));
        MsgTypeFormatterDialog->resize(495, 459);
        gridLayout_4 = new QGridLayout(MsgTypeFormatterDialog);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        fieldLabel = new QLabel(MsgTypeFormatterDialog);
        fieldLabel->setObjectName(QStringLiteral("fieldLabel"));

        gridLayout_2->addWidget(fieldLabel, 0, 0, 1, 1);

        fieldComboBox = new QComboBox(MsgTypeFormatterDialog);
        fieldComboBox->setObjectName(QStringLiteral("fieldComboBox"));
        fieldComboBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout_2->addWidget(fieldComboBox, 1, 0, 1, 1);

        addFieldPushButton = new QPushButton(MsgTypeFormatterDialog);
        addFieldPushButton->setObjectName(QStringLiteral("addFieldPushButton"));
        addFieldPushButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout_2->addWidget(addFieldPushButton, 1, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 5, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        operand1Label = new QLabel(MsgTypeFormatterDialog);
        operand1Label->setObjectName(QStringLiteral("operand1Label"));

        gridLayout->addWidget(operand1Label, 0, 0, 1, 1);

        operationLabel = new QLabel(MsgTypeFormatterDialog);
        operationLabel->setObjectName(QStringLiteral("operationLabel"));

        gridLayout->addWidget(operationLabel, 0, 1, 1, 1);

        operand2Label = new QLabel(MsgTypeFormatterDialog);
        operand2Label->setObjectName(QStringLiteral("operand2Label"));

        gridLayout->addWidget(operand2Label, 0, 2, 1, 1);

        operand1_ComboBox = new QComboBox(MsgTypeFormatterDialog);
        operand1_ComboBox->setObjectName(QStringLiteral("operand1_ComboBox"));
        operand1_ComboBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(operand1_ComboBox, 1, 0, 1, 1);

        operationComboBox = new QComboBox(MsgTypeFormatterDialog);
        operationComboBox->setObjectName(QStringLiteral("operationComboBox"));
        operationComboBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(operationComboBox, 1, 1, 1, 1);

        operand2_ComboBox = new QComboBox(MsgTypeFormatterDialog);
        operand2_ComboBox->setObjectName(QStringLiteral("operand2_ComboBox"));
        operand2_ComboBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(operand2_ComboBox, 1, 2, 1, 1);

        addOperationPushButton = new QPushButton(MsgTypeFormatterDialog);
        addOperationPushButton->setObjectName(QStringLiteral("addOperationPushButton"));
        addOperationPushButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout->addWidget(addOperationPushButton, 1, 3, 1, 1);


        gridLayout_4->addLayout(gridLayout, 6, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        textFormattingLabel = new QLabel(MsgTypeFormatterDialog);
        textFormattingLabel->setObjectName(QStringLiteral("textFormattingLabel"));

        gridLayout_3->addWidget(textFormattingLabel, 0, 0, 1, 1);

        AddNewLinepushButton = new QPushButton(MsgTypeFormatterDialog);
        AddNewLinepushButton->setObjectName(QStringLiteral("AddNewLinepushButton"));
        AddNewLinepushButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout_3->addWidget(AddNewLinepushButton, 1, 0, 1, 1);

        addTabPushButton = new QPushButton(MsgTypeFormatterDialog);
        addTabPushButton->setObjectName(QStringLiteral("addTabPushButton"));
        addTabPushButton->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout_3->addWidget(addTabPushButton, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 4, 0, 1, 1);

        formatPlainTextEdit = new QPlainTextEdit(MsgTypeFormatterDialog);
        formatPlainTextEdit->setObjectName(QStringLiteral("formatPlainTextEdit"));
        formatPlainTextEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        gridLayout_4->addWidget(formatPlainTextEdit, 3, 0, 1, 1);

        formatStringLineEdit = new QLineEdit(MsgTypeFormatterDialog);
        formatStringLineEdit->setObjectName(QStringLiteral("formatStringLineEdit"));
        formatStringLineEdit->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        formatStringLineEdit->setReadOnly(true);

        gridLayout_4->addWidget(formatStringLineEdit, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(MsgTypeFormatterDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_4->addWidget(buttonBox, 7, 0, 1, 1);

        formatStringLabel = new QLabel(MsgTypeFormatterDialog);
        formatStringLabel->setObjectName(QStringLiteral("formatStringLabel"));

        gridLayout_4->addWidget(formatStringLabel, 0, 0, 1, 1);

        formatLabel = new QLabel(MsgTypeFormatterDialog);
        formatLabel->setObjectName(QStringLiteral("formatLabel"));

        gridLayout_4->addWidget(formatLabel, 2, 0, 1, 1);

        QWidget::setTabOrder(formatPlainTextEdit, AddNewLinepushButton);
        QWidget::setTabOrder(AddNewLinepushButton, addTabPushButton);
        QWidget::setTabOrder(addTabPushButton, fieldComboBox);
        QWidget::setTabOrder(fieldComboBox, addFieldPushButton);
        QWidget::setTabOrder(addFieldPushButton, operand1_ComboBox);
        QWidget::setTabOrder(operand1_ComboBox, operationComboBox);
        QWidget::setTabOrder(operationComboBox, operand2_ComboBox);
        QWidget::setTabOrder(operand2_ComboBox, addOperationPushButton);
        QWidget::setTabOrder(addOperationPushButton, formatStringLineEdit);

        retranslateUi(MsgTypeFormatterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MsgTypeFormatterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MsgTypeFormatterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MsgTypeFormatterDialog);
    } // setupUi

    void retranslateUi(QDialog *MsgTypeFormatterDialog)
    {
        MsgTypeFormatterDialog->setWindowTitle(QApplication::translate("MsgTypeFormatterDialog", "Dialog", 0));
        fieldLabel->setText(QApplication::translate("MsgTypeFormatterDialog", "Field", 0));
#ifndef QT_NO_TOOLTIP
        fieldComboBox->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "Select a field to add", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        addFieldPushButton->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "Add the selected field at the cursor position", 0));
#endif // QT_NO_TOOLTIP
        addFieldPushButton->setText(QApplication::translate("MsgTypeFormatterDialog", "Add Data field", 0));
        operand1Label->setText(QApplication::translate("MsgTypeFormatterDialog", "Operand 1", 0));
        operationLabel->setText(QApplication::translate("MsgTypeFormatterDialog", "Operation", 0));
        operand2Label->setText(QApplication::translate("MsgTypeFormatterDialog", "Operand 2", 0));
#ifndef QT_NO_TOOLTIP
        operand1_ComboBox->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "Select the first operand of the operation", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        operationComboBox->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "Select an operation which shall be applied to the operands", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        operand2_ComboBox->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "Select the second operand of the operation", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        addOperationPushButton->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "Add the specified operation at the cursor position", 0));
#endif // QT_NO_TOOLTIP
        addOperationPushButton->setText(QApplication::translate("MsgTypeFormatterDialog", "Add Operation", 0));
        textFormattingLabel->setText(QApplication::translate("MsgTypeFormatterDialog", "Text formatting", 0));
#ifndef QT_NO_TOOLTIP
        AddNewLinepushButton->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "Adds a new line at the cursor position", 0));
#endif // QT_NO_TOOLTIP
        AddNewLinepushButton->setText(QApplication::translate("MsgTypeFormatterDialog", "Add new line", 0));
#ifndef QT_NO_TOOLTIP
        addTabPushButton->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "Adds a tabulator at the cursor position", 0));
#endif // QT_NO_TOOLTIP
        addTabPushButton->setText(QApplication::translate("MsgTypeFormatterDialog", "Add Tab", 0));
#ifndef QT_NO_TOOLTIP
        formatPlainTextEdit->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "<html><head/><body><p>Input the formatting which shall be applied to the messages.</p><p>Use the buttons and fields below to insert specific fields at the cursor position.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        formatStringLineEdit->setToolTip(QApplication::translate("MsgTypeFormatterDialog", "<html><head/><body><p>Shows the format string resulting from the input below</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        formatStringLabel->setText(QApplication::translate("MsgTypeFormatterDialog", "Format string", 0));
        formatLabel->setText(QApplication::translate("MsgTypeFormatterDialog", "Format", 0));
    } // retranslateUi

};

namespace Ui {
    class MsgTypeFormatterDialog: public Ui_MsgTypeFormatterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGTYPEFORMATTERDIALOG_H
