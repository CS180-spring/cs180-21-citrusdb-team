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
    void writeToFile(const nlohmann::json& content) const;
    public:
    // DatabaseEngine Dealing with users

    DatabaseEngine();
    int createUser(const std::string& username, const std::string& email, const std::string& password);
    bool loginCheck(const std::string& username, const std::string& password) const;
    bool resetPassword(const std::string& username, const std::string& email) const;
    bool updatePassword(const std::string& username, const std::string& newPassword) const;
    UserDatabase* getUser(const std::string& username);
    bool deleteUser(const std::string& username);

    // Access underlying data beneath UserDatabase
    // Collections
    int createCollection(const std::string& username, const std::string& collection);
    int deleteCollection(const std::string& username, const std::string& collection);
    int renameCollection(const std::string& username, const std::string& oldName, const std::string& newName);
    Collection* getCollection(const std::string& username, const std::string& collection);
    std::unordered_map<std::string, Collection>* getCollections(const std::string& username);

    // Documents
    int createDocument(const std::string& username, const std::string& collection, const std::string& document);
    int deleteDocument(const std::string& username, const std::string& collection, const std::string& document);
    int renameDocument(const std::string& username, const std::string& collection, const std::string& oldDoc, const std::string& newDoc);
    // Check if parameters make sense
    int replaceDocument(const std::string& username, const std::string& collection, const std::string& fromDoc, const std::string& toDoc);
    Document* getDocument(const std::string& username, const std::string& collection, const std::string& document);
    std::map<std::string, Document>* getDocuments(const std::string& username, const std::string& collection);
    
    // Objects 
    nlohmann::json getContent(const std::string& username, const std::string& collection, const std::string& document);
    int createObject(const std::string& username, const std::string& collection, const std::string& document, nlohmann::json object);
    int deleteObject(const std::string& username, const std::string& collection, const std::string& document, const std::string& objectID);
    // replace contents with new nlohmann object
    int updateDocument(const std::string& username, const std::string& collection, const std::string& document, nlohmann::json object);
    nlohmann::json getObject(const std::string& username, const std::string& collection, const std::string& document, const std::string& objectID);
    std::vector<std::string> listObjectIDs(const std::string& username, const std::string& collection, const std::string& document);

};

#endif