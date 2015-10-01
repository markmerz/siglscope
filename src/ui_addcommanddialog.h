/********************************************************************************
** Form generated from reading UI file 'addcommanddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOMMANDDIALOG_H
#define UI_ADDCOMMANDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddCommandDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *labelText;
    QLabel *label;
    QLineEdit *tooltipText;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *usbtmccommandText;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *expectNoReply;
    QRadioButton *expectOneLiner;
    QRadioButton *expectSeparateWindow;

    void setupUi(QDialog *AddCommandDialog)
    {
        if (AddCommandDialog->objectName().isEmpty())
            AddCommandDialog->setObjectName(QStringLiteral("AddCommandDialog"));
        AddCommandDialog->resize(401, 291);
        buttonBox = new QDialogButtonBox(AddCommandDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelText = new QLineEdit(AddCommandDialog);
        labelText->setObjectName(QStringLiteral("labelText"));
        labelText->setGeometry(QRect(170, 20, 221, 33));
        labelText->setClearButtonEnabled(false);
        label = new QLabel(AddCommandDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 20, 67, 21));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tooltipText = new QLineEdit(AddCommandDialog);
        tooltipText->setObjectName(QStringLiteral("tooltipText"));
        tooltipText->setGeometry(QRect(170, 60, 221, 33));
        label_2 = new QLabel(AddCommandDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 60, 67, 21));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(AddCommandDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 100, 151, 21));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        usbtmccommandText = new QLineEdit(AddCommandDialog);
        usbtmccommandText->setObjectName(QStringLiteral("usbtmccommandText"));
        usbtmccommandText->setGeometry(QRect(170, 100, 221, 33));
        groupBox = new QGroupBox(AddCommandDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(80, 140, 301, 94));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        expectNoReply = new QRadioButton(groupBox);
        expectNoReply->setObjectName(QStringLiteral("expectNoReply"));
        expectNoReply->setFocusPolicy(Qt::NoFocus);
        expectNoReply->setChecked(true);

        verticalLayout->addWidget(expectNoReply);

        expectOneLiner = new QRadioButton(groupBox);
        expectOneLiner->setObjectName(QStringLiteral("expectOneLiner"));
        expectOneLiner->setFocusPolicy(Qt::NoFocus);

        verticalLayout->addWidget(expectOneLiner);

        expectSeparateWindow = new QRadioButton(groupBox);
        expectSeparateWindow->setObjectName(QStringLiteral("expectSeparateWindow"));
        expectSeparateWindow->setFocusPolicy(Qt::NoFocus);

        verticalLayout->addWidget(expectSeparateWindow);


        retranslateUi(AddCommandDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddCommandDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddCommandDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddCommandDialog);
    } // setupUi

    void retranslateUi(QDialog *AddCommandDialog)
    {
        AddCommandDialog->setWindowTitle(QApplication::translate("AddCommandDialog", "Configure Command", 0));
        label->setText(QApplication::translate("AddCommandDialog", "Label:", 0));
        label_2->setText(QApplication::translate("AddCommandDialog", "Tooltip:", 0));
        label_3->setText(QApplication::translate("AddCommandDialog", "USBTMC Command:", 0));
        groupBox->setTitle(QString());
        expectNoReply->setText(QApplication::translate("AddCommandDialog", "Expect no reply", 0));
        expectOneLiner->setText(QApplication::translate("AddCommandDialog", "Expect oneliner in status bar", 0));
        expectSeparateWindow->setText(QApplication::translate("AddCommandDialog", "Expect long reply in separate window", 0));
    } // retranslateUi

};

namespace Ui {
    class AddCommandDialog: public Ui_AddCommandDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOMMANDDIALOG_H
