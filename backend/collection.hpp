#ifndef COLLECTION_HPP 
#define COLLECTION_HPP 
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <filesystem>
#include "./nlohmann/json.hpp"
#include "document.hpp"
using json = nlohmann::json;


class Collection {
private:
    std::string collectionName;
    std::unordered_map<std::string, Document> documents;

public:

    Collection() {}
    
    //basic constructor to recreate collection if server goes down
    Collection(std::string filepath, std::string collectionName);
    
    //constructor used when a collection is actually being created within the database.
    Collection(std::string filepath, std::string collectionName, std::string templateVariables);

    //renames collection in file directory, updates collectionName variable
    int renameCollection(std::string filepath, std::string oldCollectionName, std::string newCollectionName);
    
    //creates document in file directory, cannot create an empty document. Updates documents map
    int createDocument(std::string filepath, std::string documentName, json content);
    
    //deletes document rom file directory, updaates documents map
    int deleteDocument(std::string filepath, std::string documentName);
    
    //replaces content of a file, cannot replace with an empty document
    int replaceDocument(std::string filepath, std::string documentName, json content);

    //gathers content of each document in the collection, returns as one object
    json displayObjects(std::string filepath);

    //gathers all content that matches the query
    json filterDisplay(std::string filepath, json query);

    //returns collection template as a json object
    json getTemplate(std::string filepath);
    
    //returns 1 if document is present in the map, 0 if it is not
    bool checkDocument(std::string documentName);
    
    //basic getter
    Document* getDocument(std::string documentName);
    
    //basic getter
    std::string getCollectionName();
    
    //basic setter
    void setCollectionName(std::string newCollectionName);
    
    //basic getter
    std::unordered_map<std::string, Document>* getDocuments();

    //start passthrough function calls to Document

    int renameDocument(std::string filepath, std::string oldDocumentName, std::string newDocumentName);
    
    int createObject(std::string filepath,std::string documentName, json object);
    
    int deleteObject(std::string filepath, std::string documentName, std::string objectID);
};
#endif