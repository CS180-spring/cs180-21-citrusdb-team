#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <./nlohmann/json.hpp>
#include "document.hpp"
using json = nlohmann::ordered_json;


class Collection {
private:
    std::string collectionName;
    std::unordered_map<std::string, Document> documents;

public:
    //basic constructor to recreate collection if server goes down
    Collection(std::string filepath, std::string collectionName);
    
    //constructor used when a collection is actually being created within the database.
    Collection(std::string filepath, std::string collectionName, std::string templateVariables);

    int createDocument(std::string filepath, std::string documentName, json content);
    int renameDocument(std::string filepath, std::string oldDocumentName, std::string newDocumentName);
    int deleteDocument(std::string filepath, std::string documentName);
    int replaceDocument(std::string filepath, std::string documentName, json content);
    int checkDocument(std::string documentName);
    Document getDocument(std::string documentName);
    std::string getCollectionName();
    std::unordered_map<std::string, Document>* getDocuments();

    //start passthrough to Document
    int renameDocument(std::string filepath, std::string oldDocumentName, std::string newDocumentName);
    int createObject(std::string filepath,std::string documentName, std::string objectID, json object);
    int deleteObject(std::string filepath, std::string documentName, std::string objectID);
    int checkObject(std::string filepath, std::string documentName, std::string objectID);
    json getObject(std::string filepath, std::string documentName, std::string objectID);
};