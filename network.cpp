#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
#include "network.h"
#include "post.h"

// Helper function to compare posts by messageId
static bool comparePostsById(const Post* p1, const Post* p2) {
    return p1->getMessageId() < p2->getMessageId();
}

// Default constructor (no arguments, initializes an empty Network with no users)
Network::Network() : nextMessageId_(0), nextUserId_(0) {
}

// Primary constructor (with arguments to initialize the fields)
Network::Network(std::vector<User*> users) : users_(users), nextMessageId_(0), nextUserId_(0) {}

// Destructor
Network::~Network() {
    for (User* user : users_) {
        delete user;  // Delete each User object
    }
    users_.clear();
}

// Getter for users
// Iterates through the users_ vector and returns a pointer to the user with the given ID
// Returns nullptr if the user does not exist
User* Network::getUser(int id) {
    for (size_t i = 0; i < users_.size(); i++) {
        if (users_[i]->getId() == id) {
            return users_[i];
        }
    }
    return nullptr;
}

// Get the ID of a user given their name
// Takes a string in the "firstname lastname" format representing the user's name
// Iterates through the list of users to find a match by name
// Returns the ID of the user if found, or -1 if the user does not exist
int Network::getId(const std::string& name) {
    for (size_t i = 0; i < users_.size(); i++) {
        if (users_[i]->getName() == name) {
            return users_[i]->getId();
        }
    }
    return -1;
}

// Accept a pointer to a user object and add it to the network database
// Takes a string for the name, an int for the year, and an int for the zip code
// Adds a user to the users_ vector
void Network::addUser(User* user) {
    users_.push_back(user);
}

void Network::addUser(const std::string& name, int year, int zip) {
    User* user = new User(nextUserId_++, name, year, zip, std::set<int>());
    users_.push_back(user);
}

// Add connection between two users in the network graph
// Takes 2 strings in the "firstname lastname" format for the 2 users
// Adds an edge (friend connection) if it does not already exist
// Returns -1 if either user is invalid, 0 otherwise
int Network::addConnection(const std::string& s1, const std::string& s2) {
    int id1 = getId(s1);
    int id2 = getId(s2);

    // Check if either user is invalid or if they are the same
    if (id1 == -1 || id2 == -1 || id1 == id2) {
        return -1;
    }

    // Get the user objects for the two users
    User* user1 = getUser(id1);
    User* user2 = getUser(id2);

    // Check if the users are already friends
    // If the edge already exists, there is nothing to add
    if (user1->getFriends().find(id2) != user1->getFriends().end()) {
        return -1;
    }

    // Add the edge between the two users
    user1->addFriend(id2); // Add edge from user1 to user2
    user2->addFriend(id1); // Add edge from user2 to user1
    return 0;
}

// Remove connection between two users in the network graph
// Takes 2 strings in the "firstname lastname" format representing the names of 2 users
// Removes an edge (friend connection) if it exists
// Returns -1 if either user is invalid, 0 otherwise
int Network::deleteConnection(const std::string& s1, const std::string& s2) {
    int id1 = getId(s1);
    int id2 = getId(s2);
    
    // Check if either user is invalid
    if (id1 == -1 || id2 == -1) {
        return -1;
    }

    // Get the user objects for the two users
    User* user1 = getUser(id1);
    User* user2 = getUser(id2);

    // Check if the users are not friends
    // If the edge does not exist, there is nothing to remove
    if (user1->getFriends().find(id2) == user1->getFriends().end()) {
        return -1;
    }

    // Remove the edge between the two users if it exists
    user1->deleteFriend(id2); // Remove edge from user1 to user2
    user2->deleteFriend(id1); // Remove edge from user2 to user1
    return 0;
    
}

// Get the number of users in the network
// Returns the number of users in the network
int Network::numUsers() {
    return users_.size();
}

// Read users from a file
// Takes a char* fname representing the file name
// Reads the data from the file and adds the users to the network
int Network::readUsers(const char* fname) {
    std::ifstream infile(fname); // Open the file for reading

    // Check if the file was opened successfully
    if (!infile) {
        std::cout << "Error opening file: " << fname << '\n';
        return -1;
    }

    int numUsers;
    infile >> numUsers;
    infile.ignore(); // Ignore the newline character after the number of users

    int maxUserId = -1; // Initialize to track the maximum user ID

    for (int i = 0; i < numUsers; ++i) {
        // Initialize variables to store new user data from the file
        int id;
        std::string name;
        int year;
        int zip;
        std::set<int> friends;

        // Read user data from the file
        infile >> id;
        infile.ignore(); // Ignore the newline character after the ID

        // Read the user's name (may contain spaces)
        std::getline(infile, name);
        if (!name.empty() && name[0] == '\t') {
            name = name.substr(1); // Remove the leading tab character
        }

        infile >> year;
        infile.ignore(); // Ignore the newline character after the year

        infile >> zip;
        infile.ignore(); // Ignore the newline character after the zip code

        // Read the user's friends
        // The list of friends is a space-separated list of IDs
        std::string friendList;
        std::getline(infile, friendList);

        // Check if friendList is not empty before calling substr(1)
        if (!friendList.empty() && friendList[0] == '\t') {
            friendList = friendList.substr(1); // Remove the leading tab character from the friend list
        }

        std::istringstream friendStream(friendList);
        int friendId;

        while (friendStream >> friendId) { // Read each friend ID
            friends.insert(friendId);
        }

        // Create a new user object and add it to the network
        User* user = new User(id, name, year, zip, friends);
        addUser(user);

        // Update maxUserId
        if (id > maxUserId) {
            maxUserId = id;
        }
    }
    // Close the file
    infile.close();

    // Set nextUserId_ to be one greater than the maximum user ID found
    nextUserId_ = maxUserId + 1;

    return 0;
}

// Write users to a file
// Takes a char* fname representing the file name
// Writes the data of all users in the network to the file
void Network::writeUsers(const char* fname) {
    std::ofstream outfile(fname); // Open the file for writing

    // Check if the file was opened successfully
    if (!outfile) {
        std::cout << "Error opening file: " << fname << '\n';
        return;
    }

    // Write the number of users to the file
    outfile << users_.size() << '\n';

    // Write the data of each user to the file
    // Iterate through the list of users and write each user's data to the file
    // \t is used to separate the user data fields
    for (User* user : users_) {
        outfile << user->getId() << '\n'; 
        outfile << "\t" << user->getName() << '\n';
        outfile << "\t" << user->getYear() << '\n';
        outfile << "\t" << user->getZip() << '\n';

        // Write the list of friends for the user
        // The list of friends is a space-separated list of IDs
        std::set<int> friends = user->getFriends();
        outfile << "\t";

        // Write each friend ID to the file
        for (int friendId : friends) { 
            outfile << friendId << " ";
        }
        outfile << '\n'; 
    }
    // Close the file
    outfile.close();
}

// Helper function for BFS to find the shortest path
// Takes the IDs of two users and returns the shortest path between them
// Returns an empty vector if no path is found
// Returns an empty vector if either user is invalid
std::vector<int> Network::bfsShortestPath(int from, int to) {
    std::queue<int> q;
    std::vector<int> prev(users_.size(), -1);
    std::set<int> visited;

    q.push(from);
    visited.insert(from);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Check if the destination user has been reached
        // If the destination user has been reached, reconstruct the path by backtracking from the destination to the source
        if (current == to) {
            std::vector<int> path;
            for (int at = to; at != -1; at = prev[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        User* user = getUser(current);
        for (int friendId : user->getFriends()) {
            if (visited.find(friendId) == visited.end()) {
                q.push(friendId);
                visited.insert(friendId);
                prev[friendId] = current;
            }
        }
    }
    return std::vector<int>(); // Return empty vector if no path found
}

// Method to compute the shortest path between two users
// Takes the IDs of two users and returns the shortest path between them
// Returns an empty vector if no path is found
// Returns an empty vector if either user is invalid
std::vector<int> Network::shortestPath(int from, int to) {
    if (getUser(from) == nullptr || getUser(to) == nullptr) {
        return std::vector<int>(); // Return empty vector if either user is invalid
    }
    return bfsShortestPath(from, to);
}

// Method to find a user whose relational distance from the given user exactly matches the distance
// Takes the ID of the user to start from, a reference to the ID of the user to find, and the distance to search for
// Returns a vector of user IDs representing the path from the starting user to the user at the specified distance
std::vector<int> Network::distanceUser(int from, int& to, int distance) {
    std::queue<int> q;
    std::vector<int> prev(users_.size(), -1);
    std::vector<int> dist(users_.size(), -1);
    std::set<int> visited;

    q.push(from);
    visited.insert(from);
    dist[from] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (dist[current] == distance) {
            to = current;
            std::vector<int> path;
            for (int at = current; at != -1; at = prev[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Iterate through the friends of the current user
        // Add the friends to the queue if they have not been visited
        // Update the distance and previous node for each friend
        User* user = getUser(current);
        for (int friendId : user->getFriends()) {
            if (visited.find(friendId) == visited.end()) {
                q.push(friendId);
                visited.insert(friendId);
                prev[friendId] = current;
                dist[friendId] = dist[current] + 1;
            }
        }
    }

    to = -1;
    return std::vector<int>(); // Return empty vector if no user found at the specified distance
}

// Method to suggest friends for a user based on common friends
std::vector<int> Network::suggestFriends(int who, int& score) {
    User* user = getUser(who);
    if (!user) {
        score = 0;
        return std::vector<int>(); // Return empty vector if user is invalid
    }

    std::set<int> friends = user->getFriends();
    std::map<int, int> potentialFriends; // Map to store potential friends and their scores

    // Iterate through the friends of the user
    // For each friend, iterate through their friends
    // Increment the score for each friend of a friend that is not already a friend
    for (int friendId : friends) {
        User* friendUser = getUser(friendId);
        for (int friendOfFriendId : friendUser->getFriends()) {
            if (friendOfFriendId != who && friends.find(friendOfFriendId) == friends.end()) {
                potentialFriends[friendOfFriendId]++;
            }
        }
    }

    // Find the user(s) with the highest score
    std::vector<int> suggestions;
    score = 0;

    // Iterate through the potential friends and find the user(s) with the highest score
    for (const auto& entry : potentialFriends) {
        if (entry.second > score) {
            score = entry.second;
            suggestions.clear();
            suggestions.push_back(entry.first);
        }
        else if (entry.second == score) {
            suggestions.push_back(entry.first);
        }
    }
    return suggestions;
}

// Helper function for DFS to find all nodes in a connected component
void Network::dfs(int start, std::vector<bool>& visited, std::vector<int>& component) {
    std::stack<int> stack;
    stack.push(start);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        if (!visited[current]) {
            visited[current] = true;
            component.push_back(current);

            User* user = getUser(current);
            for (int friendId : user->getFriends()) {
                if (!visited[friendId]) {
                    stack.push(friendId);
                }
            }
        }
    }
}

// Method to compute the connected components of the network
std::vector<std::vector<int>> Network::groups() {
    std::vector<std::vector<int>> components;
    std::vector<bool> visited(users_.size(), false);

    for (size_t i = 0; i < users_.size(); ++i) {
        if (!visited[i]) {
            std::vector<int> component;
            dfs(i, visited, component);
            components.push_back(component);
        }
    }

    return components;
}

// Method to add a post to a user's messages in the network
void Network::addPost(int ownerId, const std::string &message, int likes, bool isIncoming, const std::string &authorName, bool isPublic) {
    // Find the user with the given ID
    User* user = getUser(ownerId);
    if (!user) {
        std::cerr << "User with ID " << ownerId << " not found.\n";
        return; // Return if the user is invalid
    }

    // Assign the next global message ID
    int messageId = nextMessageId_++; // Increment the global message ID counter

    // Create a new Post or IncomingPost object based on isIncoming
    Post* newPost;
    if (isIncoming) {
        newPost = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
    }
    else {
        newPost = new Post(messageId, ownerId, message, likes);
    }

    // Add the post to the user's messages
    user-> addPost(newPost);
}

// Method to retrieve a string of the most recent posts from a user
std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic) {

    // Find the user by ownerId
    User* user = getUser(ownerId);
    if (!user) {
        std::cerr << "User with ID " << ownerId << " not found.\n";
        return ""; // Return empty string if the user is invalid
    }
    
    // Call the getPostsString method of the User class
    return user->getPostsString(howMany, showOnlyPublic);
}

int Network::readPosts(const char* fname) {
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        return -1; // Return -1 if the file could not be opened
    }  

    int numPosts;
    infile >> numPosts;
    infile.ignore(); // Ignore the newline character

    for (int i = 0; i < numPosts; ++i) {
        int messageId;
        std::string message;
        int ownerId;
        int likes;
        std::string privacy; // "public", "private", or empty
        std::string author;  // Author name or empty

        infile >> messageId;
        infile.ignore(); // Ignore the newline character

        // Read message
        std::getline(infile, message);
        message = message.substr(1); // Remove leading tab

        infile >> ownerId;
        infile.ignore();

        infile >> likes;
        infile.ignore();

        // Read privacy line
        std::getline(infile, privacy);
        if (!privacy.empty()) {
            privacy = privacy.substr(1); // Remove leading tab
        }

        // Read author line
        std::getline(infile, author);
        if (!author.empty()) {
            author = author.substr(1); // Remove leading tab
        }

        bool isIncoming = !author.empty();
        bool isPublic = (privacy == "public");

        // Create Post of IncomingPost with messageId from the file
        Post* newPost;
        if (isIncoming) {
            newPost = new IncomingPost(messageId, ownerId, message, likes, isPublic, author);
        }
        else {
            newPost = new Post(messageId, ownerId, message, likes);
        }

        // Find the user with ownerId
        User* user = getUser(ownerId);
        if (!user) {
            std::cerr << "User with ID " << ownerId << " not found.\n";
            delete newPost; 
            continue;
        }

        // Add the post to the user's messages
        user->addPost(newPost);

        // Update nextMessageId_
        if (messageId >= nextMessageId_) {
            nextMessageId_ = messageId + 1;
        }
    }

    infile.close();
    return 0; // Return 0 if the posts were read successfully
}

// Method to write posts to a file
int Network::writePosts(const char* fname) {
    std::ofstream outfile(fname);
    if (!outfile.is_open()) {
        return -1; // Return -1 if the file could not be opened
    }

    // Collect all posts from all users
    std::vector<Post*> allPosts;
    for (User* user : users_) {
        // Append the posts to the allPosts vector
        std::vector<Post*> userPosts = user->getPosts();
        allPosts.insert(allPosts.end(), userPosts.begin(), userPosts.end());
    }

    // Sort the posts by messageId
    std::sort(allPosts.begin(), allPosts.end(), comparePostsById);

    // Write the number of posts at the top of the file
    outfile << allPosts.size() << '\n';


    for (Post* post : allPosts) {
        outfile << post->getMessageId() << '\n';
        outfile << '\t' << post->getMessage() << '\n';
        outfile << '\t' << post->getOwnerId() << '\n';
        outfile << '\t' << post->getLikes() << '\n';

        if (!post->getAuthor().empty()) {

            // Cast the Post pointer to an IncomingPost pointer
            outfile << '\t' << (post->getIsPublic() ? "public" : "private") << '\n';
            outfile << '\t' << post->getAuthor() << '\n';
        }
        else {
            // Write a newline character for the author and privacy fields
            outfile << '\t' << '\n';
            outfile << '\t' << '\n';
        }
    }

    outfile.close();
    return 0; // Return 0 if the posts were written successfully
}
