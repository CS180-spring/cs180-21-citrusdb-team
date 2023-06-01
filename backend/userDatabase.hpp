#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include <./nlohmann/json.hpp>

#include "collection.hpp"
#include "document.hpp"

using json = nlohmann::ordered_json;

class UserDatabase{
    private:
        //stores filename of folder for userDatabase
        //filepath should be just the database/username of the user with access to this database
        std::string databaseName;

        //tracks names of collections within the userDatabase
        std::map<std::string, Collection> collections;

    public:
        //only takes databaseName in as input, all ofther information gathered from metadata file within the userDatabase
        UserDatabase(std::string databaseName);

        //add a collection to a userDatabase, inserts folder to database structure, metadata file, and collections vector
        int createCollection(std::string collectionName, std::string displayTemplate);

        //delete a collection from a user database, should delete all documents from within the collection prior to deleting the collection
        int deleteCollection(std::string collectionName);

        int checkCollection(std::string collectionName);

        //return specific Collection opbject, helper function for transporting calls to a specific function
        Collection* getCollection(std::string collectionName);

        //basic getter
        std::string getDatabaseName();

        //basic getter
        std::map<std::string, Collection>* getCollections();


        //start functions that are passthroughs to Collection
        int renameCollection(std::string oldCollectionName, std::string newCollectionName);

        int createDocument(std::string collectionName, std::string documentName, json content);

        int deleteDocument(std::string collectionName, std::string documentName);

        int replaceDocument(std::string collectionName, std::string documentName, json content);

        //start functions that are passthroughs to Document

        int renameDocument(std::string collectionName, std::string oldDocumentName, std::string newDocumentName);

        int createObject(std::string collectionName,std::string documentName, std::string objectID, json object);

        int deleteObject(std::string collectionName, std::string documentName, std::string objectID);
};