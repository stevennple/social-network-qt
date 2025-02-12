#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include "user.h"

class Network {
private: 
    // Vector to store the users in the network
    std::vector<User*> users_;

    // Helper function for BFS to find the shortest path between two users
    std::vector<int> bfsShortestPath(int from, int to);

    // Helper function for DFS to find all nodes in a connected component
    void dfs(int start, std::vector<bool>& visited, std::vector<int>& component);

    // Global message ID counter for the network
    int nextMessageId_;

    int nextUserId_;

public:
    // Default constructor (no arguments, initializes an empty Network with no users)
    // Pre: none
    // Post: Initializes an empty Network with no users
    Network();

    // Primary constructor (with arguments to initialize the fields)
    // Pre: users must be valid
    // Post: Initializes a Network with the given users
    Network(std::vector<User*> users);

    // Destructor
    // Pre: none
    // Post: Deletes all users in the network
    ~Network();

    // Getter for users
    // Pre: none
    // Post: Returns a pointer to the user with the given ID
    User* getUser(int id);

    // Get the ID of a user given their name
    // Pre: name must be valid
    // Post: Takes a string in the [firstname] [lastname] format
    // Returns the ID of the user or -1 if the user does not exist
    int getId(const std::string& name);

    // Add a user to the network database
    // Pre: name, year, and zip must be valid
    // Post: Takes a string for the name, an int for the year, and an int for the zip code
    void addUser(User* user);
    void addUser(const std::string& name, int year, int zip);

    // Add a connection between two users
    // Pre: s1 and s2 must be valid
    // Post: Takes 2 strings in the [firstname] [lastname] format and the names of 2 users
    // Adds a friend connection if it does not already exist. Return -1 if either user is invalid, 0 otherwise
    int addConnection(const std::string& s1, const std::string& s2);

    // Remove a connection between two users
    // Pre: s1 and s2 must be valid
    // Post: Takes 2 strings in the [firstname] [lastname] format and the names of 2 users
    // Removes a friend connection if it exists. Return -1 if either user is invalid, 0 otherwise
    int deleteConnection(const std::string& s1, const std::string& s2);

    // Get the number of users in the network
    // Pre: none
    // Post: Returns the number of users in the network
    int numUsers();

    // Read users from a file
    // Pre: fname must be valid
    // Post: Reads the data from the file and adds the users to the network
    int readUsers(const char* fname);

    // Write users to a file
    // Pre: fname must be valid
    // Post: Writes the data from the network to the file
    void writeUsers(const char* fname);

    // Find the shortest path between two users
    // Pre: int from and int to must be valid
    // Post: Returns a vector of integers representing the shortest path between two users
    std::vector<int> shortestPath(int from, int to);

    // Find a user whose relational distance from the given user exactly matches the given distance
    // Pre: int from, int& to, and int distance must be valid
    // Post: Returns a vector of integers representing the user whose relational distance from sthe given user exactly matches the given distance
    std::vector<int> distanceUser(int from, int& to, int distance);

    // Suggest friends for a user based on mutual friends
    // Pre: int who and int& score must be valid
    // Post: Returns a vector of integers representing the IDs of users who have the highest score
    std::vector<int> suggestFriends(int who, int& score);

    // Compute the conected components of the network
    // Pre: none
    // Post: Returns a vector of vectors, where each inner vector contains the IDs of users in one connected component
    std::vector<std::vector<int>> groups();

    // Add a post to the user's messages
    // Pre: int ownerId, const std::string& message, int likes, bool isIncoming, const std::string& authorName, bool isPublic must be valid
    // Post: Adds a post to the user's messages
    void addPost(int ownerId, const std::string &message, int likes, bool isIncoming, const std::string &authorName, bool isPublic);

    // Retrieve a string containing the most recent posts for a user
    // Pre: int ownerId, int howMany, bool showOnlyPublic must be valid
    // Post: Returns a string containing the most recent posts for a user
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

    // Read posts from a file
    // Pre: char* fname must be valid
    // Post: Reads the data from the file and adds the posts to the network
    int readPosts(const char* fname);

    // Write posts to a file
    // Pre: char* fname must be valid
    // Post: Writes the data from the network to the file
    int writePosts(const char* fname);
};

#endif
