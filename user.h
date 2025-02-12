#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <vector>
#include "post.h"

class User {
private:
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;
    std::vector<Post*> messages_;   

public:
    // Default constructor
    // Pre: none
    // Post: initialized to default/arbitrary values
    User();

    // Primary constructor
    // Pre: id, name, year, zip, and friends must be valid
    // Post: id, name, year, zip, and friends are initialized to the values provided
    User(int id, const std::string& name, int year, int zip, const std::set<int>& friends);

    // Getter for id
    // Pre: none
    // Post: Returns the id of the user
    int getId() const;

    // Setter for id
    // Pre: id must be valid
    // Post: Sets the id of the user
    void setId(int id);

    // Getter for name
    // Pre: none
    // Post: Returns the name of the user
    std::string getName() const;

    // Getter for year
    // Pre: none
    // Post: Returns the year (DOB) user
    int getYear() const;

    // Getter for zip
    // Pre: none
    // Post: Returns the zip code of the user
    int getZip() const;

    // Getter for friends
    // Pre: none
    // Post: Returns a set of the user's friends
    std::set<int>& getFriends();

    // Method to accept the ID of a user to add as a friend
    // If the user is already a friend, the method does nothing
    // Pre: none
    // Post: Accepts the ID of a user to add as a friend
    void addFriend(int id);

    // Method to accept the ID of a user to delete as a friend
    // If the user is not a friend, the method does nothing
    // Pre: none
    // Post: Accepts the ID of a user to delete as a friend
    void deleteFriend(int id);

    // Method to add a post to the user's messages
    // Pre: none
    // Post: Adds a post to the user's messages
    void addPost(Post* post);

    // Method to return the user's messages
    // Pre: none
    // Post: Returns the user's messages
    std::vector<Post*> getPosts() const;

    // Method to return the user's messages as a string
    // Pre: none
    // Post: Returns the user's messages as a string
    std::string getPostsString(int howMany, bool showOnlyPublic) const;

    // Method to check if specific user ID is friends with current user
    // Pre: user id is valid
    // Post: Returns true or false if specified user is friends with current user
    bool isFriend(int friendId) const;
};

#endif
