/********************************************************************************
** Form generated from reading UI file 'selectdevicedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDEVICEDIALOG_H
#define UI_SELECTDEVICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectDeviceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SelectDeviceDialog)
    {
        if (SelectDeviceDialog->objectName().isEmpty())
            SelectDeviceDialog->setObjectName(QStringLiteral("SelectDeviceDialog"));
        SelectDeviceDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(SelectDeviceDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(SelectDeviceDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        scrollArea = new QScrollArea(SelectDeviceDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 380, 216));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        buttonBox = new QDialogButtonBox(SelectDeviceDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SelectDeviceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SelectDeviceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SelectDeviceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SelectDeviceDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDeviceDialog)
    {
        SelectDeviceDialog->setWindowTitle(QApplication::translate("SelectDeviceDialog", "Select Device", 0));
        label->setText(QApplication::translate("SelectDeviceDialog", "Select device from list:", 0));
    } // retranslateUi

};

namespace Ui {
    class SelectDeviceDialog: public Ui_SelectDeviceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDEVICEDIALOG_H
