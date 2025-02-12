#include <string>
#include <set>
#include <vector>
#include "user.h"
#include "post.h"

// Default constructor (no arguments, initializes fields with arbitrary values)
User::User() : id_(0), name_("default"), year_(0), zip_(0), friends_() {}

// Primary constructor (with arguments to initialize the fields)
User::User(int id, const std::string& name, int year, int zip, const std::set<int>& friends) : 
            id_(id), name_(name), year_(year), zip_(zip), friends_(friends) {}

// Method to return the ID of the user
int User::getId() const {
    return id_;
}

// Setter for id
void User::setId(int id) {
    id_ = id;
}

// Method to return the name of the user
std::string User::getName() const {
    return name_;
}

// Method to return the year (DOB) of the user
int User::getYear() const {
    return year_;
}

// Method to return the zip code of the user
int User::getZip() const {
    return zip_;
}

// Method to return a set of the user's friends (by reference)
std::set<int>& User::getFriends() {
    return friends_;
}

// Method to accept the ID of a user to add as a friend
// If the user is already a friend, the method does nothing
void User::addFriend(int id) {
    friends_.insert(id);
}

// Method to accept the ID of a user to delete as a friend
// If the user is not a friend, the method does nothing
void User::deleteFriend(int id) {
    friends_.erase(id);
}

// Method to return the number of friends the user has
void User::addPost(Post* post) {
    messages_.push_back(post);
}

// Method to return the user's messages
std::vector<Post*> User::getPosts() const{
    return messages_;
}

// Method to return a string representation of the user's recent posts
std::string User::getPostsString(int howMany, bool showOnlyPublic) const {
    std::string result;

    // Get the total number of posts the user has
    int postCount = messages_.size();

    // Determine the actual number of posts to display (minimum of howMany and postCount)
    int count = std::min(howMany, postCount);

    // Iterate through posts in reverse order to show the most recent posts first
    for (int i = postCount - 1; i >= postCount - count; --i) {
        Post* post = messages_[i]; // Access each post by pointer

        // If showOnlyPublic is true and the post is not public, skip it
        if (showOnlyPublic && !post->getIsPublic()) {
            continue;
        }

        // Append the post's string representation to the result, followed by two newlines
        result += post->toString() + "\n\n";
    }

    // Remove the last two newlines if the result is not empty
    if (!result.empty()) {
        result.erase(result.size() - 2);
    }

    return result;
}

// Method to check if a given user ID is already a friend of this user
bool User::isFriend(int friendId) const {
    for (int id : friends_) {
        // If friend ID is found in the list, return true
        if (id == friendId) {
            return true;
        }
    }
    // Return false if not found in list
    return false;
}
