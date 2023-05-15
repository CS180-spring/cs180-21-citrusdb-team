#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

class Collection;
class Document;

class UserDatabase{
    private:
        //stores filename of folder for userDatabase
        //filepath should be just the username of the user with access to this database
        std::string databaseName;

        //tracks names of collections within the userDatabase
        //sorted alphabetically, in order to speed up search at the expense of insertion
        std::vector<Collection> collections;

    public:
        //only takes filepath in as input, all ofther information gathered from metadata file within the userDatabase
        //metadata file is also named after the username, stores username, password, email of user
            //also stores sorted list of all collections within the database
        UserDatabase(std::string databaseName);

        //add a collection to a userDatabase, inserts folder to database structure, metadata file, and collections vector
        int createCollection(std::string collectionName, std::string jsonTemplate);

        //delete a collection from a user database, should delete all documents from within the collection prior to deleting the collection
        int deleteCollection(std::string collectionName);

        //renames a collection, should also rename the folder in the file structure and metadata file of collection
        int renameCollection(std::string oldCollectionName, std::string newCollectionName);

        //return specific Colelction opbject, helper function for trnsporting calls to a specific function
        Collection getCollection(std::string collectionName);

        //basic getter
        std::string getDatabaseName();

        //basic getter
        std::vector<Collection> getCollections();


        //start functions that are passthroughs to Collection

        int createDocument();

        int deleteDocument();

        int renameDocument();

        int replaceDocument();

        Document getDocument();

        std::vector<Document> getDocuments();

        //start functions that are passthroughs to Document

        int createObject();

        int deleteObject();

        int updateDocument();

        std::string getObject();

        std::string listObjectIDs();

        std::string getObjectID();

        std::string getDocumentContent();
};