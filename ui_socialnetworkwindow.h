/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworkWindow
{
public:
    QWidget *centralwidget;
    QWidget *loginWidget;
    QLabel *loginLabel;
    QPushButton *loginButton;
    QTextEdit *loginTextEdit;
    QWidget *profileWidget;
    QLabel *profileLabel;
    QTableWidget *friendsTable;
    QLabel *postsLabel;
    QTableWidget *friendSuggestionsTable;
    QPushButton *backButton;
    QPushButton *addFriendButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->resize(800, 600);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        loginWidget = new QWidget(centralwidget);
        loginWidget->setObjectName("loginWidget");
        loginWidget->setGeometry(QRect(220, 230, 341, 101));
        loginLabel = new QLabel(loginWidget);
        loginLabel->setObjectName("loginLabel");
        loginLabel->setGeometry(QRect(30, 10, 91, 16));
        loginButton = new QPushButton(loginWidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(30, 60, 256, 24));
        loginTextEdit = new QTextEdit(loginWidget);
        loginTextEdit->setObjectName("loginTextEdit");
        loginTextEdit->setGeometry(QRect(30, 33, 256, 21));
        loginTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        loginTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        profileWidget = new QWidget(centralwidget);
        profileWidget->setObjectName("profileWidget");
        profileWidget->setEnabled(true);
        profileWidget->setGeometry(QRect(10, 0, 781, 571));
        profileLabel = new QLabel(profileWidget);
        profileLabel->setObjectName("profileLabel");
        profileLabel->setEnabled(true);
        profileLabel->setGeometry(QRect(10, 10, 281, 16));
        friendsTable = new QTableWidget(profileWidget);
        if (friendsTable->columnCount() < 1)
            friendsTable->setColumnCount(1);
        friendsTable->setObjectName("friendsTable");
        friendsTable->setGeometry(QRect(600, 10, 171, 351));
        friendsTable->setSortingEnabled(false);
        friendsTable->setWordWrap(true);
        friendsTable->setCornerButtonEnabled(true);
        friendsTable->setRowCount(0);
        friendsTable->setColumnCount(1);
        friendsTable->horizontalHeader()->setVisible(true);
        friendsTable->horizontalHeader()->setCascadingSectionResizes(false);
        friendsTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        friendsTable->horizontalHeader()->setStretchLastSection(true);
        friendsTable->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        friendsTable->verticalHeader()->setStretchLastSection(false);
        postsLabel = new QLabel(profileWidget);
        postsLabel->setObjectName("postsLabel");
        postsLabel->setGeometry(QRect(10, 70, 581, 451));
        postsLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        friendSuggestionsTable = new QTableWidget(profileWidget);
        if (friendSuggestionsTable->columnCount() < 1)
            friendSuggestionsTable->setColumnCount(1);
        friendSuggestionsTable->setObjectName("friendSuggestionsTable");
        friendSuggestionsTable->setEnabled(true);
        friendSuggestionsTable->setGeometry(QRect(600, 370, 171, 181));
        friendSuggestionsTable->setColumnCount(1);
        friendSuggestionsTable->horizontalHeader()->setStretchLastSection(true);
        backButton = new QPushButton(profileWidget);
        backButton->setObjectName("backButton");
        backButton->setEnabled(true);
        backButton->setGeometry(QRect(10, 30, 161, 24));
        addFriendButton = new QPushButton(profileWidget);
        addFriendButton->setObjectName("addFriendButton");
        addFriendButton->setGeometry(QRect(180, 30, 111, 24));
        SocialNetworkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        SocialNetworkWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkWindow);

        QMetaObject::connectSlotsByName(SocialNetworkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkWindow)
    {
        SocialNetworkWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkWindow", "SocialNetworkWindow", nullptr));
        loginLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter your name", nullptr));
        loginButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Login", nullptr));
        profileLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Profile Name", nullptr));
        postsLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "User posts", nullptr));
        backButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Back to My Profile", nullptr));
        addFriendButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add Friend", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkWindow: public Ui_SocialNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
