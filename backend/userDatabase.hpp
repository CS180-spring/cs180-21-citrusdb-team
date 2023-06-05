#ifndef _USERDATABASE_HPP_ 
#define _USERDATABASE_HPP_ 

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include "./nlohmann/json.hpp"

#include "collection.hpp"
#include "document.hpp"

using json = nlohmann::json;

class UserDatabase{
    private:
        //stores filename of folder for userDatabase
        //filepath should be just the database/username of the user with access to this database
        std::string databaseName;

        //tracks names of collections within the userDatabase
        std::unordered_map<std::string, Collection> collections;

    public:

        UserDatabase() {}
        
        //only takes databaseName in as input, all ofther information gathered from metadata file within the userDatabase
        UserDatabase(std::string databaseName);

        //add a collection to a userDatabase, inserts folder to database structure, metadata file, and collections vector
        int createCollection(std::string collectionName, std::string displayTemplate);

        //delete a collection from a user database, should delete all documents from within the collection prior to deleting the collection
        int deleteCollection(std::string collectionName);

        //return 1 if collection id in database, 0 if not
        bool checkCollection(std::string collectionName);

        //return json object containing names for all collections within userDatabase
        json displayCollection();

        //return json object containing names for all collection containing requested substrings in the name
        json filterDisplay(std::string query);

        //return specific Collection opbject, helper function for transporting calls to a specific function
        Collection* getCollection(std::string collectionName);

        //basic getter
        std::string getDatabaseName();

        //basic getter
        std::unordered_map<std::string, Collection>* getCollections();


        //start functions that are passthroughs to Collection
        int renameCollection(std::string oldCollectionName, std::string newCollectionName);

        int createDocument(std::string collectionName, std::string documentName, std::string content);

        int deleteDocument(std::string collectionName, std::string documentName);

        int replaceDocument(std::string collectionName, std::string documentName, std::string content);

        json displayObjects(std::string collectionName);
        
        json filterDisplay(std::string collectionName, std::string query);
        
        json getTemplate(std::string collectionName);

        //start functions that are passthroughs to Document

        int renameDocument(std::string collectionName, std::string oldDocumentName, std::string newDocumentName);

        int createObject(std::string collectionName,std::string documentName, std::string object);

        int deleteObject(std::string collectionName, std::string documentName, std::string objectID);
};

#endif