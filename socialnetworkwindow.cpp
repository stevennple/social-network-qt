#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include "network.h"
#include "user.h"
#include <QMessageBox>
#include <QString>
#include <QTableWidgetItem>
#include <QDebug>

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{
    ui->setupUi(this);

    // Load data from files
    network.readUsers("users.txt");
    network.readPosts("posts.txt");

    // Initial state
    ui->profileWidget->setVisible(false);

    // Connect login button
    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkWindow::handleLogin);

    // Connect friend suggestions table
    connect(ui->friendSuggestionsTable, &QTableWidget::cellClicked, this, &SocialNetworkWindow::handleFriendRequest);

    // Connect friends list table
    connect(ui->friendsTable, &QTableWidget::cellClicked, this, &SocialNetworkWindow::viewFriendProfile);

    // Connected the add friend button to the slot
    connect(ui->addFriendButton, &QPushButton::clicked, this, &SocialNetworkWindow::onAddFriendButtonClicked);

    // Connect back button
    connect(ui->backButton, &QPushButton::clicked, [this]() {
        currentUser = loggedInUser;
        displayProfile();
    });
}

SocialNetworkWindow::~SocialNetworkWindow() {
    delete ui;
    network.writeUsers("users.txt");
    network.writePosts("posts.txt");
}

void SocialNetworkWindow::handleLogin() {
    // Get the entered username from the login text edit
    QString name = ui->loginTextEdit->toPlainText();

    // Retrieve the user ID based on the eneted username
    int userId = network.getId(name.toStdString());

    // Check if the user ID is valid
    if (userId != -1) {
        loggedInUser = network.getUser(userId);
        currentUser = loggedInUser;
        ui->loginWidget->setVisible(false);
        ui->profileWidget->setVisible(true);
        displayProfile();
    }
    else {
        // Display warning box indicating login failure
        QMessageBox::warning(this, "Login Failed", "User not found. Please try again.");
    }
}

void SocialNetworkWindow::displayProfile() {
    if (currentUser->getId() == loggedInUser->getId()) {
        // User is viewing their own profile
        ui->profileLabel->setText("My Profile");
        ui->friendSuggestionsTable->setVisible(true);
        ui->backButton->setVisible(false);
        ui->addFriendButton->setVisible(false);  // Hide the Add Friend button on the user's own profile
    }
    else {
        // User is viewing someone else's profile
        ui->profileLabel->setText(QString::fromStdString(currentUser->getName()) + "'s Profile");
        ui->friendSuggestionsTable->setVisible(false);
        ui->backButton->setVisible(true);

        // Check if the currentUser is already a friend of loggedInUser
        bool isFriend = loggedInUser->isFriend(currentUser->getId());
        ui->addFriendButton->setVisible(!isFriend);  // Show the Add Friend button only if they are not friends
    }

    loadFriendList();
    loadRecentPosts();

    if (currentUser->getId() == loggedInUser->getId()) {
        loadFriendSuggestions();
    }
}

void SocialNetworkWindow::loadFriendList() {
    ui->friendsTable->clear();
    ui->friendsTable->setRowCount(0);
    ui->friendsTable->setColumnCount(1);
    ui->friendsTable->setHorizontalHeaderLabels(QStringList() << "Friends");

    // Retrieve the list of friends for the current user
    const auto& friends = currentUser->getFriends();

    int row = 0;

    // Interate over each friend ID in the list
    for (int friendId : friends) {
        User* friendUser = network.getUser(friendId); // Get User object for each friend ID

        if (friendUser) {
            ui->friendsTable->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(friendUser->getName()));
            ui->friendsTable->setItem(row, 0, item); // Set item in 1st column of table
            row++; // Move to next row
        }
    }
}

void SocialNetworkWindow::loadRecentPosts() {
    ui->postsLabel->clear();

    bool showOnlyPublic = (currentUser->getId() != loggedInUser->getId()); // Show only public posts if viewing another user's profile

    std::string posts = currentUser->getPostsString(5, showOnlyPublic); // Get recent posts as a string

    ui->postsLabel->setText(QString::fromStdString(posts)); // Display the posts in the label
}

void SocialNetworkWindow::loadFriendSuggestions() {
    int score;
    std::vector<int> suggestions = network.suggestFriends(loggedInUser->getId(), score);

    ui->friendSuggestionsTable->clear();
    ui->friendSuggestionsTable->setRowCount(0);
    ui->friendSuggestionsTable->setColumnCount(1);
    ui->friendSuggestionsTable->setHorizontalHeaderLabels(QStringList() << "Friend Suggestions");

    int row = 0;

    for (int userId : suggestions) {
        User* suggestedUser = network.getUser(userId); // Get User object for each suggested ID

        if (suggestedUser) {
            ui->friendSuggestionsTable->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(suggestedUser->getName())); // Create a table with suggested user's name
            item->setData(Qt::UserRole, userId); // Store friend ID in UserRole
            ui->friendSuggestionsTable->setItem(row, 0, item);
            row++;
        }
    }
}

void SocialNetworkWindow::handleFriendRequest(int row, int column) {
    QString friendName = ui->friendSuggestionsTable->item(row, column)->text(); // Get friend name from the table

    int friendId = network.getId(friendName.toStdString()); // Get friend ID using the name

    if (friendId != -1) {
        loggedInUser->addFriend(friendId);
        network.getUser(friendId)->addFriend(loggedInUser->getId()); // Add friend to logged-in user's friends list
        network.writeUsers("users.txt"); // Update the file
        displayProfile(); // Refresh the profile to reflect new changes
    }
}

void SocialNetworkWindow::viewFriendProfile(int row, int column) {
    QString friendName = ui->friendsTable->item(row, column)->text();

    int friendId = network.getId(friendName.toStdString());

    if (friendId != -1) {
        currentUser = network.getUser(friendId);
        displayProfile(); // Refresh the profile view for the selected friend
    }
}

void SocialNetworkWindow::addFriend(int friendId) {
    if (loggedInUser && network.getUser(friendId)) {
        // Add friend to both users
        loggedInUser->addFriend(friendId);
        network.getUser(friendId)->addFriend(loggedInUser->getId());

        // Update file
        updateUsersFile();

        // Refresh profile to reflect the new friend in the friend's list
        displayProfile();
    }
}

void SocialNetworkWindow::onAddFriendButtonClicked() {
    if (currentUser && (currentUser->getId() != loggedInUser->getId())) {
        addFriend(currentUser->getId()); // Add the currently viewed user as a friend
    }
}

void SocialNetworkWindow::updateFriendOfFriendList(User* friendUser) {
    if (!friendUser) return;

    // Clear the current contents of the friend suggestions table to display a fresh list of the friends of the friendUser
    ui->friendSuggestionsTable->clear();

    // Get the list of friends (friend IDs) for the provided friendUser.
    auto friendsOfFriend = friendUser->getFriends();

    int row = 0;

    for (int fofId : friendsOfFriend) {
        User* fofUser = network.getUser(fofId);
        if (fofUser) {
            ui->friendSuggestionsTable->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(fofUser->getName().c_str());
            item->setData(Qt::UserRole, fofId); // Store friend ID in UserRole
            ui->friendSuggestionsTable->setItem(row, 0, item);
            row++;
        }
    }
}

void SocialNetworkWindow::updateUsersFile() {
    // Check if there are any users in the network before writing
    if (network.numUsers() > 0) {
        network.writeUsers("users.txt"); // Write users data to "users.txt"
    }
}

void SocialNetworkWindow::updatePostsFile() {
    if (network.numUsers() > 0) {
        network.writePosts("posts.txt");
    }
}
