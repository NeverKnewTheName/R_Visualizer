/********************************************************************************
** Form generated from reading UI file 'sysovrvobjectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSOVRVOBJECTDIALOG_H
#define UI_SYSOVRVOBJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SysOvrvObjectDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *objectNameLE;
    QLabel *label_2;
    QComboBox *objectShapeComboBox;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *ObjectColorLE;
    QPushButton *OpenColorPicker;
    QLabel *transparencyLbl;
    QDoubleSpinBox *transparencySpinBox;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *objectVisualizerGraphicsView;
    QVBoxLayout *verticalLayout;
    QPushButton *addPropertyBtn;
    QPushButton *rmvPropertyBtn;
    QPushButton *edtPropertyBtn;
    QPushButton *pushButton;
    QPushButton *edtTriggerBtn;
    QPushButton *addLblBtn;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SysOvrvObjectDialog)
    {
        if (SysOvrvObjectDialog->objectName().isEmpty())
            SysOvrvObjectDialog->setObjectName(QStringLiteral("SysOvrvObjectDialog"));
        SysOvrvObjectDialog->resize(562, 423);
        verticalLayout_2 = new QVBoxLayout(SysOvrvObjectDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(SysOvrvObjectDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        objectNameLE = new QLineEdit(SysOvrvObjectDialog);
        objectNameLE->setObjectName(QStringLiteral("objectNameLE"));

        formLayout->setWidget(0, QFormLayout::FieldRole, objectNameLE);

        label_2 = new QLabel(SysOvrvObjectDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        objectShapeComboBox = new QComboBox(SysOvrvObjectDialog);
        objectShapeComboBox->setObjectName(QStringLiteral("objectShapeComboBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, objectShapeComboBox);

        label_3 = new QLabel(SysOvrvObjectDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        ObjectColorLE = new QLineEdit(SysOvrvObjectDialog);
        ObjectColorLE->setObjectName(QStringLiteral("ObjectColorLE"));

        horizontalLayout_2->addWidget(ObjectColorLE);

        OpenColorPicker = new QPushButton(SysOvrvObjectDialog);
        OpenColorPicker->setObjectName(QStringLiteral("OpenColorPicker"));

        horizontalLayout_2->addWidget(OpenColorPicker);

        transparencyLbl = new QLabel(SysOvrvObjectDialog);
        transparencyLbl->setObjectName(QStringLiteral("transparencyLbl"));

        horizontalLayout_2->addWidget(transparencyLbl);

        transparencySpinBox = new QDoubleSpinBox(SysOvrvObjectDialog);
        transparencySpinBox->setObjectName(QStringLiteral("transparencySpinBox"));
        transparencySpinBox->setWrapping(false);
        transparencySpinBox->setFrame(true);
        transparencySpinBox->setProperty("showGroupSeparator", QVariant(false));
        transparencySpinBox->setMaximum(100);
        transparencySpinBox->setValue(100);

        horizontalLayout_2->addWidget(transparencySpinBox);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);


        verticalLayout_2->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        objectVisualizerGraphicsView = new QGraphicsView(SysOvrvObjectDialog);
        objectVisualizerGraphicsView->setObjectName(QStringLiteral("objectVisualizerGraphicsView"));

        horizontalLayout->addWidget(objectVisualizerGraphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        addPropertyBtn = new QPushButton(SysOvrvObjectDialog);
        addPropertyBtn->setObjectName(QStringLiteral("addPropertyBtn"));

        verticalLayout->addWidget(addPropertyBtn);

        rmvPropertyBtn = new QPushButton(SysOvrvObjectDialog);
        rmvPropertyBtn->setObjectName(QStringLiteral("rmvPropertyBtn"));

        verticalLayout->addWidget(rmvPropertyBtn);

        edtPropertyBtn = new QPushButton(SysOvrvObjectDialog);
        edtPropertyBtn->setObjectName(QStringLiteral("edtPropertyBtn"));

        verticalLayout->addWidget(edtPropertyBtn);

        pushButton = new QPushButton(SysOvrvObjectDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        edtTriggerBtn = new QPushButton(SysOvrvObjectDialog);
        edtTriggerBtn->setObjectName(QStringLiteral("edtTriggerBtn"));

        verticalLayout->addWidget(edtTriggerBtn);

        addLblBtn = new QPushButton(SysOvrvObjectDialog);
        addLblBtn->setObjectName(QStringLiteral("addLblBtn"));

        verticalLayout->addWidget(addLblBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(SysOvrvObjectDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Open|QDialogButtonBox::Reset|QDialogButtonBox::Save);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(SysOvrvObjectDialog);

        QMetaObject::connectSlotsByName(SysOvrvObjectDialog);
    } // setupUi

    void retranslateUi(QDialog *SysOvrvObjectDialog)
    {
        SysOvrvObjectDialog->setWindowTitle(QApplication::translate("SysOvrvObjectDialog", "Dialog", 0));
        label->setText(QApplication::translate("SysOvrvObjectDialog", "Object Name:", 0));
        label_2->setText(QApplication::translate("SysOvrvObjectDialog", "Object Shape:", 0));
        label_3->setText(QApplication::translate("SysOvrvObjectDialog", "Object Color:", 0));
        OpenColorPicker->setText(QApplication::translate("SysOvrvObjectDialog", "Color picker", 0));
        transparencyLbl->setText(QApplication::translate("SysOvrvObjectDialog", "Transparency:", 0));
        addPropertyBtn->setText(QApplication::translate("SysOvrvObjectDialog", "Add Object", 0));
        rmvPropertyBtn->setText(QApplication::translate("SysOvrvObjectDialog", "Remove Object", 0));
        edtPropertyBtn->setText(QApplication::translate("SysOvrvObjectDialog", "Edit Object", 0));
        pushButton->setText(QApplication::translate("SysOvrvObjectDialog", "Duplicate Object", 0));
        edtTriggerBtn->setText(QApplication::translate("SysOvrvObjectDialog", "Edit Object Trigger", 0));
        addLblBtn->setText(QApplication::translate("SysOvrvObjectDialog", "Add Label", 0));
    } // retranslateUi

};

namespace Ui {
    class SysOvrvObjectDialog: public Ui_SysOvrvObjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSOVRVOBJECTDIALOG_H
