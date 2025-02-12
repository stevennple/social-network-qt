#include "post.h"

// Default constructor (no arguments, initializes fields with arbitrary values)
Post::Post() : messageId_(0), ownerId_(0), message_(""), likes_(0) {}

// Parameterized constructor (with arguments to initialize the fields)
Post::Post(int messageId, int ownerId, const std::string &message, int likes) : 
            messageId_(messageId), ownerId_(ownerId), message_(message), likes_(likes) {}

// Virtual destructor
Post::~Post() {}

// toString() method
std::string Post::toString() const {
    return message_ + " Liked by " + std::to_string(likes_) + " people.";
}

// Method to return the ID of the post
int Post::getMessageId() const {
    return messageId_;
}

// Method to return the ID of the owner of the post
int Post::getOwnerId() const {
    return ownerId_;
}

// Method to return the message of the post
std::string Post::getMessage() const {
    return message_;
}

// Method to return the number of likes on the post
int Post::getLikes() const {
    return likes_;
}

// Virtual methods
// Method to return the author of the post
std::string Post::getAuthor() const {
    return "";
}

// Method to return whether the post is public
bool Post::getIsPublic() const {
    return true;
}

// Default constructor (no arguments, initializes fields with arbitrary values)
IncomingPost::IncomingPost() : Post(), author_(""), isPublic_(true) {}

// Parameterized constructor (with arguments to initialize the fields)
IncomingPost::IncomingPost(int messageId, int ownerId, const std::string &message,
                            int likes, bool isPublic, const std::string &author) : 
                    Post(messageId, ownerId, message, likes), author_(author), isPublic_(isPublic) {}

// Virtual destructor
IncomingPost::~IncomingPost() {}

// Method to return whether the post is public
std::string IncomingPost::getAuthor() const {
    return author_;
}

// Method to return whether the post is public
bool IncomingPost::getIsPublic() const {
    return isPublic_;
}

// Method to return a string representation of the post (including author and privacy)
std::string IncomingPost::toString() const {
    std::string privacy = isPublic_ ? "" : " (private)";
    return author_ + " wrote" + privacy + ": " + Post::toString();
}