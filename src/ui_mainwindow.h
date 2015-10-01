/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionAdd_Command;
    QAction *actionSave_Settings;
    QAction *actionConnect_to_device;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QPushButton *waveCH1Button;
    QPushButton *waveCH2Button;
    QPushButton *spectrumCH1Button;
    QPushButton *spectrumCH2Button;
    QFrame *line;
    QCustomPlot *customPlot;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCommands;
    QMenu *menuDelete_command;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(869, 554);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAdd_Command = new QAction(MainWindow);
        actionAdd_Command->setObjectName(QStringLiteral("actionAdd_Command"));
        actionAdd_Command->setCheckable(false);
        actionSave_Settings = new QAction(MainWindow);
        actionSave_Settings->setObjectName(QStringLiteral("actionSave_Settings"));
        actionConnect_to_device = new QAction(MainWindow);
        actionConnect_to_device->setObjectName(QStringLiteral("actionConnect_to_device"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy);
        scrollArea_2->setMaximumSize(QSize(16777215, 70));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 849, 68));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        waveCH1Button = new QPushButton(scrollAreaWidgetContents);
        waveCH1Button->setObjectName(QStringLiteral("waveCH1Button"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(waveCH1Button->sizePolicy().hasHeightForWidth());
        waveCH1Button->setSizePolicy(sizePolicy1);
        waveCH1Button->setFocusPolicy(Qt::StrongFocus);
        waveCH1Button->setLayoutDirection(Qt::LeftToRight);
        waveCH1Button->setText(QStringLiteral("Wave CH1"));

        horizontalLayout->addWidget(waveCH1Button);

        waveCH2Button = new QPushButton(scrollAreaWidgetContents);
        waveCH2Button->setObjectName(QStringLiteral("waveCH2Button"));
        waveCH2Button->setEnabled(true);

        horizontalLayout->addWidget(waveCH2Button);

        spectrumCH1Button = new QPushButton(scrollAreaWidgetContents);
        spectrumCH1Button->setObjectName(QStringLiteral("spectrumCH1Button"));

        horizontalLayout->addWidget(spectrumCH1Button);

        spectrumCH2Button = new QPushButton(scrollAreaWidgetContents);
        spectrumCH2Button->setObjectName(QStringLiteral("spectrumCH2Button"));

        horizontalLayout->addWidget(spectrumCH2Button);

        scrollArea_2->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea_2);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        line->setMaximumSize(QSize(16777215, 10));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));

        verticalLayout->addWidget(customPlot);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 869, 27));
        menuBar->setNativeMenuBar(false);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuCommands = new QMenu(menuBar);
        menuCommands->setObjectName(QStringLiteral("menuCommands"));
        menuDelete_command = new QMenu(menuCommands);
        menuDelete_command->setObjectName(QStringLiteral("menuDelete_command"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCommands->menuAction());
        menuFile->addAction(actionExit);
        menuCommands->addAction(actionAdd_Command);
        menuCommands->addAction(menuDelete_command->menuAction());
        menuCommands->addAction(actionSave_Settings);
        menuCommands->addAction(actionConnect_to_device);
        menuDelete_command->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SiglScope", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionAdd_Command->setText(QApplication::translate("MainWindow", "Add Command", 0));
        actionSave_Settings->setText(QApplication::translate("MainWindow", "Save Settings", 0));
        actionConnect_to_device->setText(QApplication::translate("MainWindow", "Connect to device", 0));
#ifndef QT_NO_TOOLTIP
        actionConnect_to_device->setToolTip(QApplication::translate("MainWindow", "Select device to connect", 0));
#endif // QT_NO_TOOLTIP
        waveCH2Button->setText(QApplication::translate("MainWindow", "Wave CH2", 0));
        spectrumCH1Button->setText(QApplication::translate("MainWindow", "Spect CH1", 0));
        spectrumCH2Button->setText(QApplication::translate("MainWindow", "Spect CH2", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuCommands->setTitle(QApplication::translate("MainWindow", "Config", 0));
        menuDelete_command->setTitle(QApplication::translate("MainWindow", "Delete command", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
