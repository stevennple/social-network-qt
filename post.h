#ifndef POST_H
#define POST_H

#include <string>

// Post class
// Represents a post on a social media platform
class Post {
private:
    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;

public:
    
    // Default constructor
    // Pre: none
    // Post: initialized to default/arbitrary values
    Post();

    // Primary constructor
    // Pre: messageId, ownerId, message, and likes must be valid
    // Post: messageId, ownerId, message, and likes are initialized to the values provided
    Post(int messageId, int ownerId, const std::string &message, int likes);

    // Virtual destructor
    // Pre: none
    // Post: none
    virtual ~Post();

    // toString() method
    // pre: none
    // Post: Returns a string representation of the post   
    virtual std::string toString() const;

    // Getter methods
    // Pre: none
    // Post: Returns the messageId of the post
    int getMessageId() const;

    // Pre: none
    // Post: Returns the ownerId of the post
    int getOwnerId() const;

    // Pre: none
    // Post: Returns the message of the post
    std::string getMessage() const;

    // Pre: none
    // Post: Returns the likes of the post
    int getLikes() const;

    // Virtual methods
    // Pre: none
    // Post: Returns the author of the post
    virtual std::string getAuthor() const;

    // Pre: none
    // Post: Returns whether the post is public
    virtual bool getIsPublic() const;
};

// IncomingPost class
// Represents a post that has been received from another user
// Inherits from Post
class IncomingPost : public Post {
private:
    // Pre: none
    // Post: Returns the author of the post
    std::string author_;

    // Pre: none
    // Post: Returns whether the post is public
    bool isPublic_;

public: 
    // Default constructor
    // Pre: none
    // Post: initialized to default/arbitrary values
    IncomingPost();

    // Primary constructor
    // Pre: messageId, ownerId, message, and likes must be valid
    // Post: messageId, ownerId, message, and likes are initialized to the values provided
    IncomingPost(int messageId, int ownerId, const std::string &message,
                int likes, bool isPublic, const std::string &author);

    // Destructor
    // Pre: none
    // Post: none
    ~IncomingPost();

    // Public methods
    // Pre: none
    // Post: Returns the author of the post
    std::string getAuthor() const override;

    // Pre: none
    // Post: Returns whether the post is public
    bool getIsPublic() const override;

    // Pre: none
    // Post: Returns a string representation of the post
    std::string toString() const;
};

#endif