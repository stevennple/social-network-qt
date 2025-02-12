#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include "network.h"
#include "user.h"
#include "ui_socialnetworkwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkWindow;
}
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor for initializing the SocialNetworkWindow, setting up the UI and loading data
    explicit SocialNetworkWindow(QWidget *parent = nullptr);

    // Destructor to clean up resources and save data back to files
    ~SocialNetworkWindow();

private slots:
    // Slot function to handle the login button click
    void handleLogin();

    // Slot function to display the profile of the logged-in user or a selected friend
    void displayProfile();

    // Slot function to handle friend requests from the friend suggestions table
    void handleFriendRequest(int row, int column);

    // Slot function to view a friend's profile when their name is clicked in the friends list
    void viewFriendProfile(int row, int column);

    // Slot function to handle the click event for adding a friend
    void onAddFriendButtonClicked();

private:
    Ui::SocialNetworkWindow *ui; // Pointer to the UI elements created by Qt Designer
    Network network;             // Network object to manage users, connections, and posts
    User* loggedInUser;          // Pointer to the currently logged-in user
    User* currentUser;           // Pointer to the user whose profile is currently being displayed

    void loadFriendList();
    void loadRecentPosts();
    void loadFriendSuggestions();
    void addFriend(int friendId);
    void updateFriendsList();
    void updateFriendOfFriendList(User* friendUser);
    void updateUsersFile();
    void updatePostsFile();
};

#endif
