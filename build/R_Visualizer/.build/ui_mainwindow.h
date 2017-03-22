/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionConnect;
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionSwitch_User_Role;
    QAction *actionOpen_Error_Log;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTabWidget *configTabWidget;
    QWidget *tab_toolConfig;
    QPushButton *TestPB_1;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTrace;
    QMenu *menuUser;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1040, 791);
        QIcon icon;
        icon.addFile(QStringLiteral(":/GUI/Icons/Icons/AppICON.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/GUI/Icons/Icons/Add-New-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/GUI/Icons/Icons/Open-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/GUI/Icons/Icons/Save-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/GUI/Icons/Icons/Network-01-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon4);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/GUI/Icons/Icons/Check-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon5);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/GUI/Icons/Icons/Delete-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon6);
        actionSwitch_User_Role = new QAction(MainWindow);
        actionSwitch_User_Role->setObjectName(QStringLiteral("actionSwitch_User_Role"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/GUI/Icons/Icons/UserNormal-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QStringLiteral(":/GUI/Icons/Icons/UserAdmin-32.png"), QSize(), QIcon::Normal, QIcon::On);
        actionSwitch_User_Role->setIcon(icon7);
        actionOpen_Error_Log = new QAction(MainWindow);
        actionOpen_Error_Log->setObjectName(QStringLiteral("actionOpen_Error_Log"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        configTabWidget = new QTabWidget(splitter);
        configTabWidget->setObjectName(QStringLiteral("configTabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(configTabWidget->sizePolicy().hasHeightForWidth());
        configTabWidget->setSizePolicy(sizePolicy);
        configTabWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        tab_toolConfig = new QWidget();
        tab_toolConfig->setObjectName(QStringLiteral("tab_toolConfig"));
        tab_toolConfig->setToolTipDuration(-1);
        TestPB_1 = new QPushButton(tab_toolConfig);
        TestPB_1->setObjectName(QStringLiteral("TestPB_1"));
        TestPB_1->setGeometry(QRect(80, 50, 80, 21));
        configTabWidget->addTab(tab_toolConfig, QString());
        splitter->addWidget(configTabWidget);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1040, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTrace = new QMenu(menuBar);
        menuTrace->setObjectName(QStringLiteral("menuTrace"));
        menuUser = new QMenu(menuBar);
        menuUser->setObjectName(QStringLiteral("menuUser"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTrace->menuAction());
        menuBar->addAction(menuUser->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen_Error_Log);
        menuTrace->addAction(actionConnect);
        menuTrace->addAction(actionStart);
        menuTrace->addAction(actionStop);
        menuUser->addAction(actionSwitch_User_Role);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionStart);
        mainToolBar->addAction(actionStop);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSwitch_User_Role);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionOpen_Error_Log);

        retranslateUi(MainWindow);

        configTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "R_Visualizer", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "Create a new file", 0));
#endif // QT_NO_TOOLTIP
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open an existing file", 0));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "Save current data to a file", 0));
#endif // QT_NO_TOOLTIP
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        actionStart->setText(QApplication::translate("MainWindow", "Start", 0));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", 0));
        actionSwitch_User_Role->setText(QApplication::translate("MainWindow", "Switch to Admin Role", 0));
#ifndef QT_NO_TOOLTIP
        actionSwitch_User_Role->setToolTip(QApplication::translate("MainWindow", "Switch the Role of the user", 0));
#endif // QT_NO_TOOLTIP
        actionOpen_Error_Log->setText(QApplication::translate("MainWindow", "Open Error Log", 0));
#ifndef QT_NO_TOOLTIP
        configTabWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        TestPB_1->setText(QApplication::translate("MainWindow", "Test_1", 0));
        configTabWidget->setTabText(configTabWidget->indexOf(tab_toolConfig), QApplication::translate("MainWindow", "Tool config", 0));
        configTabWidget->setTabToolTip(configTabWidget->indexOf(tab_toolConfig), QApplication::translate("MainWindow", "Configure the tool itself", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuTrace->setTitle(QApplication::translate("MainWindow", "Trace", 0));
        menuUser->setTitle(QApplication::translate("MainWindow", "User", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
