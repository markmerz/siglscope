/********************************************************************************
** Form generated from reading UI file 'commandreplydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMANDREPLYDIALOG_H
#define UI_COMMANDREPLYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommandReplyDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;

    void setupUi(QDialog *CommandReplyDialog)
    {
        if (CommandReplyDialog->objectName().isEmpty())
            CommandReplyDialog->setObjectName(QStringLiteral("CommandReplyDialog"));
        CommandReplyDialog->resize(434, 344);
        verticalLayout_2 = new QVBoxLayout(CommandReplyDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        scrollArea = new QScrollArea(CommandReplyDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 414, 287));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textBrowser = new QTextBrowser(scrollAreaWidgetContents);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setReadOnly(true);

        verticalLayout->addWidget(textBrowser);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        pushButton = new QPushButton(CommandReplyDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMaximumSize(QSize(100, 16777215));
        pushButton->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_2->addWidget(pushButton);


        retranslateUi(CommandReplyDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), CommandReplyDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(CommandReplyDialog);
    } // setupUi

    void retranslateUi(QDialog *CommandReplyDialog)
    {
        CommandReplyDialog->setWindowTitle(QApplication::translate("CommandReplyDialog", "Reply from  scope", 0));
        pushButton->setText(QApplication::translate("CommandReplyDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class CommandReplyDialog: public Ui_CommandReplyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMANDREPLYDIALOG_H
