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

        //basic constructor, should not be used
        UserDatabase();

        //only takes filepath in as input, all ofther information gathered from metadata file within the userDatabase
        //metadata file is also named after the username, stores username, password, email of user
            //also stores sorted list of all collections within the database
        UserDatabase(std::string databaseName);

        //add a collection to a userDatabase, inserts folder to database structure, metadata file, and collections vector
        int createCollection(std::string collectionName, json displayTemplate);

        //delete a collection from a user database, should delete all documents from within the collection prior to deleting the collection
        int deleteCollection(std::string collectionName);

        //renames a collection, should also rename the folder in the file structure and metadata file of collection
        int renameCollection(std::string collectionName, std::string newCollectionName);

        //return specific Collection opbject, helper function for transporting calls to a specific function
        Collection* getCollection(std::string collectionName);

        //basic getter
        std::string getDatabaseName();

        //basic getter
        std::map<std::string, Collection>* getCollections();


        //start functions that are passthroughs to Collection

        int createDocument();

        int deleteDocument();

        int renameDocument();

        int replaceDocument();

        Document getDocument();

        std::map<std::string, Document> getDocuments();

        //start functions that are passthroughs to Document

        int createObject(int collectionIndex, int documentIndex, std::string objectID, json object);

        int deleteObject(int collectionIndex, int documentIndex, std::string objectID);

        int updateDocument(int collectionIndex, int documentIndex, std::string newDocument);

        json getObject(int collectionIndex, int documentIndex, std::string objectID);

        std::string listObjectIDs();

        std::string getObjectID();

        json getDocumentContent(int collectionIndex, int documentIndex);
};