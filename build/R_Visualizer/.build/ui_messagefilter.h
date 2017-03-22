/********************************************************************************
** Form generated from reading UI file 'messagefilter.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEFILTER_H
#define UI_MESSAGEFILTER_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessageFilter
{
public:
    QGridLayout *gridLayout;
    QGroupBox *idGrb;
    QGridLayout *gridLayout_2;
    QPushButton *rmvFilterIDPushButton;
    QPushButton *addFilterIDPushButton;
    QSpacerItem *idHorzSpcr;
    QListView *idFilterlistView;
    QCheckBox *enableIDFilterCheckBox;
    QPushButton *filterIDSaveBtn;
    QPushButton *filterIDLoadBtn;
    QGroupBox *tmstmpGrb;
    QFormLayout *formLayout;
    QLabel *fromLbl;
    QHBoxLayout *fromHorzL;
    QDateTimeEdit *filterTimeStampFromDateTimeEdit;
    QCheckBox *enableTimestampFromFilterCheckBox;
    QSpacerItem *fromHrzSpcr;
    QLabel *toLbl;
    QHBoxLayout *toHorzL;
    QDateTimeEdit *filterTimeStampToDateTimeEdit;
    QCheckBox *enableTimestampToFilterCheckBox;
    QSpacerItem *toHorzSpcr;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *filterTimestampSaveBtn;
    QPushButton *filterTimestampLoadBtn;
    QGroupBox *codeGrb;
    QGridLayout *gridLayout_3;
    QListView *codeFilterlistView;
    QPushButton *addFilterCodePushButton;
    QPushButton *rmvFilterCodePushButton;
    QSpacerItem *codeHorzSpcr;
    QCheckBox *enableCodeFilterCheckBox;
    QPushButton *filterCodeSaveBtn;
    QPushButton *filterCodeLoadBtn;

    void setupUi(QWidget *MessageFilter)
    {
        if (MessageFilter->objectName().isEmpty())
            MessageFilter->setObjectName(QStringLiteral("MessageFilter"));
        MessageFilter->resize(582, 544);
        gridLayout = new QGridLayout(MessageFilter);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        idGrb = new QGroupBox(MessageFilter);
        idGrb->setObjectName(QStringLiteral("idGrb"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(idGrb->sizePolicy().hasHeightForWidth());
        idGrb->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(idGrb);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        rmvFilterIDPushButton = new QPushButton(idGrb);
        rmvFilterIDPushButton->setObjectName(QStringLiteral("rmvFilterIDPushButton"));

        gridLayout_2->addWidget(rmvFilterIDPushButton, 2, 3, 1, 1);

        addFilterIDPushButton = new QPushButton(idGrb);
        addFilterIDPushButton->setObjectName(QStringLiteral("addFilterIDPushButton"));

        gridLayout_2->addWidget(addFilterIDPushButton, 2, 2, 1, 1);

        idHorzSpcr = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(idHorzSpcr, 2, 1, 1, 1);

        idFilterlistView = new QListView(idGrb);
        idFilterlistView->setObjectName(QStringLiteral("idFilterlistView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(idFilterlistView->sizePolicy().hasHeightForWidth());
        idFilterlistView->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(idFilterlistView, 1, 0, 1, 4);

        enableIDFilterCheckBox = new QCheckBox(idGrb);
        enableIDFilterCheckBox->setObjectName(QStringLiteral("enableIDFilterCheckBox"));

        gridLayout_2->addWidget(enableIDFilterCheckBox, 2, 0, 1, 1);

        filterIDSaveBtn = new QPushButton(idGrb);
        filterIDSaveBtn->setObjectName(QStringLiteral("filterIDSaveBtn"));

        gridLayout_2->addWidget(filterIDSaveBtn, 3, 2, 1, 1);

        filterIDLoadBtn = new QPushButton(idGrb);
        filterIDLoadBtn->setObjectName(QStringLiteral("filterIDLoadBtn"));

        gridLayout_2->addWidget(filterIDLoadBtn, 3, 3, 1, 1);


        gridLayout->addWidget(idGrb, 0, 0, 1, 1);

        tmstmpGrb = new QGroupBox(MessageFilter);
        tmstmpGrb->setObjectName(QStringLiteral("tmstmpGrb"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tmstmpGrb->sizePolicy().hasHeightForWidth());
        tmstmpGrb->setSizePolicy(sizePolicy2);
        tmstmpGrb->setMinimumSize(QSize(0, 0));
        formLayout = new QFormLayout(tmstmpGrb);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        fromLbl = new QLabel(tmstmpGrb);
        fromLbl->setObjectName(QStringLiteral("fromLbl"));

        formLayout->setWidget(1, QFormLayout::LabelRole, fromLbl);

        fromHorzL = new QHBoxLayout();
        fromHorzL->setObjectName(QStringLiteral("fromHorzL"));
        filterTimeStampFromDateTimeEdit = new QDateTimeEdit(tmstmpGrb);
        filterTimeStampFromDateTimeEdit->setObjectName(QStringLiteral("filterTimeStampFromDateTimeEdit"));
        sizePolicy2.setHeightForWidth(filterTimeStampFromDateTimeEdit->sizePolicy().hasHeightForWidth());
        filterTimeStampFromDateTimeEdit->setSizePolicy(sizePolicy2);
        filterTimeStampFromDateTimeEdit->setMinimumSize(QSize(0, 20));
        filterTimeStampFromDateTimeEdit->setMaximumDate(QDate(7999, 12, 31));

        fromHorzL->addWidget(filterTimeStampFromDateTimeEdit);

        enableTimestampFromFilterCheckBox = new QCheckBox(tmstmpGrb);
        enableTimestampFromFilterCheckBox->setObjectName(QStringLiteral("enableTimestampFromFilterCheckBox"));

        fromHorzL->addWidget(enableTimestampFromFilterCheckBox);

        fromHrzSpcr = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        fromHorzL->addItem(fromHrzSpcr);


        formLayout->setLayout(1, QFormLayout::FieldRole, fromHorzL);

        toLbl = new QLabel(tmstmpGrb);
        toLbl->setObjectName(QStringLiteral("toLbl"));

        formLayout->setWidget(4, QFormLayout::LabelRole, toLbl);

        toHorzL = new QHBoxLayout();
        toHorzL->setObjectName(QStringLiteral("toHorzL"));
        filterTimeStampToDateTimeEdit = new QDateTimeEdit(tmstmpGrb);
        filterTimeStampToDateTimeEdit->setObjectName(QStringLiteral("filterTimeStampToDateTimeEdit"));
        sizePolicy2.setHeightForWidth(filterTimeStampToDateTimeEdit->sizePolicy().hasHeightForWidth());
        filterTimeStampToDateTimeEdit->setSizePolicy(sizePolicy2);
        filterTimeStampToDateTimeEdit->setMinimumSize(QSize(0, 20));

        toHorzL->addWidget(filterTimeStampToDateTimeEdit);

        enableTimestampToFilterCheckBox = new QCheckBox(tmstmpGrb);
        enableTimestampToFilterCheckBox->setObjectName(QStringLiteral("enableTimestampToFilterCheckBox"));

        toHorzL->addWidget(enableTimestampToFilterCheckBox);

        toHorzSpcr = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        toHorzL->addItem(toHorzSpcr);


        formLayout->setLayout(4, QFormLayout::FieldRole, toHorzL);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        filterTimestampSaveBtn = new QPushButton(tmstmpGrb);
        filterTimestampSaveBtn->setObjectName(QStringLiteral("filterTimestampSaveBtn"));

        horizontalLayout_2->addWidget(filterTimestampSaveBtn);

        filterTimestampLoadBtn = new QPushButton(tmstmpGrb);
        filterTimestampLoadBtn->setObjectName(QStringLiteral("filterTimestampLoadBtn"));

        horizontalLayout_2->addWidget(filterTimestampLoadBtn);


        formLayout->setLayout(6, QFormLayout::FieldRole, horizontalLayout_2);


        gridLayout->addWidget(tmstmpGrb, 1, 0, 1, 3);

        codeGrb = new QGroupBox(MessageFilter);
        codeGrb->setObjectName(QStringLiteral("codeGrb"));
        sizePolicy.setHeightForWidth(codeGrb->sizePolicy().hasHeightForWidth());
        codeGrb->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(codeGrb);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        codeFilterlistView = new QListView(codeGrb);
        codeFilterlistView->setObjectName(QStringLiteral("codeFilterlistView"));
        sizePolicy1.setHeightForWidth(codeFilterlistView->sizePolicy().hasHeightForWidth());
        codeFilterlistView->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(codeFilterlistView, 0, 0, 1, 4);

        addFilterCodePushButton = new QPushButton(codeGrb);
        addFilterCodePushButton->setObjectName(QStringLiteral("addFilterCodePushButton"));

        gridLayout_3->addWidget(addFilterCodePushButton, 1, 2, 1, 1);

        rmvFilterCodePushButton = new QPushButton(codeGrb);
        rmvFilterCodePushButton->setObjectName(QStringLiteral("rmvFilterCodePushButton"));

        gridLayout_3->addWidget(rmvFilterCodePushButton, 1, 3, 1, 1);

        codeHorzSpcr = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(codeHorzSpcr, 1, 1, 1, 1);

        enableCodeFilterCheckBox = new QCheckBox(codeGrb);
        enableCodeFilterCheckBox->setObjectName(QStringLiteral("enableCodeFilterCheckBox"));

        gridLayout_3->addWidget(enableCodeFilterCheckBox, 1, 0, 1, 1);

        filterCodeSaveBtn = new QPushButton(codeGrb);
        filterCodeSaveBtn->setObjectName(QStringLiteral("filterCodeSaveBtn"));

        gridLayout_3->addWidget(filterCodeSaveBtn, 2, 2, 1, 1);

        filterCodeLoadBtn = new QPushButton(codeGrb);
        filterCodeLoadBtn->setObjectName(QStringLiteral("filterCodeLoadBtn"));

        gridLayout_3->addWidget(filterCodeLoadBtn, 2, 3, 1, 1);


        gridLayout->addWidget(codeGrb, 0, 1, 1, 1);


        retranslateUi(MessageFilter);

        QMetaObject::connectSlotsByName(MessageFilter);
    } // setupUi

    void retranslateUi(QWidget *MessageFilter)
    {
        MessageFilter->setWindowTitle(QApplication::translate("MessageFilter", "Form", 0));
        idGrb->setTitle(QApplication::translate("MessageFilter", "Message ID/Name", 0));
        rmvFilterIDPushButton->setText(QApplication::translate("MessageFilter", "Remove", 0));
        addFilterIDPushButton->setText(QApplication::translate("MessageFilter", "Add", 0));
        enableIDFilterCheckBox->setText(QApplication::translate("MessageFilter", "Enabled", 0));
        filterIDSaveBtn->setText(QApplication::translate("MessageFilter", "Save", 0));
        filterIDLoadBtn->setText(QApplication::translate("MessageFilter", "Load", 0));
        tmstmpGrb->setTitle(QApplication::translate("MessageFilter", "Message Timestamp", 0));
        fromLbl->setText(QApplication::translate("MessageFilter", "From", 0));
        filterTimeStampFromDateTimeEdit->setDisplayFormat(QApplication::translate("MessageFilter", "dd.MM.yyyy HH:mm:ss.zzz", 0));
        enableTimestampFromFilterCheckBox->setText(QApplication::translate("MessageFilter", "Enabled", 0));
        toLbl->setText(QApplication::translate("MessageFilter", "To", 0));
        filterTimeStampToDateTimeEdit->setDisplayFormat(QApplication::translate("MessageFilter", "dd.MM.yyyy HH:mm:ss.zzz", 0));
        enableTimestampToFilterCheckBox->setText(QApplication::translate("MessageFilter", "Enabled", 0));
        filterTimestampSaveBtn->setText(QApplication::translate("MessageFilter", "Save", 0));
        filterTimestampLoadBtn->setText(QApplication::translate("MessageFilter", "Load", 0));
        codeGrb->setTitle(QApplication::translate("MessageFilter", "Message Code", 0));
        addFilterCodePushButton->setText(QApplication::translate("MessageFilter", "Add", 0));
        rmvFilterCodePushButton->setText(QApplication::translate("MessageFilter", "Remove", 0));
        enableCodeFilterCheckBox->setText(QApplication::translate("MessageFilter", "Enabled", 0));
        filterCodeSaveBtn->setText(QApplication::translate("MessageFilter", "Save", 0));
        filterCodeLoadBtn->setText(QApplication::translate("MessageFilter", "Load", 0));
    } // retranslateUi

};

namespace Ui {
    class MessageFilter: public Ui_MessageFilter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEFILTER_H
