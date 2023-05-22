#ifndef DATABASENGINE_HPP
#define DATABASENGINE_HPP
#include <unordered_map>
#include <map>
#include <string>
#include "../nlohmann/json.hpp"
#include "file.hpp"
#include "userDatabase.hpp"
#include "collection.hpp"
#include "document.hpp"

class DatabaseEngine{
    private:
    // map between username <-> userDatabase
    std::unordered_map<std::string, UserDatabase> users;
    void writeToFile() const;
    public:
    // DatabaseEngine Dealing with users

    DatabaseEngine();
    int createUser(const std::string& username, const std::string& email, const std::string& password);
    bool loginCheck(const std::string& username, const std::string& password);
    bool resetPassword(const std::string& username, const std::string& email);
    bool updatePassword(const std::string& username, const std::string& newPassword);
    UserDatabase getUser(const std::string& username);
    bool deleteUser(const std::string& username);

    // Access underlying data beneath UserDatabase

    int createCollection(const std::string& username, const std::string& collection);
    int deleteCollection(const std::string& username, const std::string& collection);

    int renameDocument(const std::string& username, const std::string& collection, const std::string& document);
    // Check if parameters make sense
    int replaceDocument(const std::string& username, const std::string& collection, const std::string& document);
    Document getDocument(const std::string& username, const std::string& collection, const std::string& document);
    // also check if parameters make sense
    std::string getDocumentIds(const std::string& username, const std::string& collection, const std::string& document);
    std::string getContent(const std::string& username, const std::string& collection, const std::string& document);
    int createObject(const std::string& username, const std::string& collection, const std::string& document, const std::string& object);
    int deleteObject(const std::string& username, const std::string& collection, const std::string& document, const std::string& object);
    int updateDocument(const std::string& username, const std::string& collection, const std::string& document, nlohmann::json object);
    nlohmann::json getObject(const std::string& username, const std::string& collection, const std::string& document, const std::string& object);
    std::string listObjectID(const std::string& username, const std::string& collection, const std::string& document, const std::string& object);

};

#endif