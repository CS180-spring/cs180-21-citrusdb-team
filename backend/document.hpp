#ifndef _DOCUMENT_HPP_
#define _DOCUMENT_HPP_

#include <string>
#include <fstream>
#include <./nlohmann/json.hpp>
using json = nlohmann::ordered_json;

class Document{
private:
    //stored filename and extension - "[name].json"
    std::string fileName;
    
public:
    //basic constructor used to recreate a file if the server goes down.
    Document(std::string fileName);

    //constructor used when a file is actually being created in the database
    Document(std::string fileName, std::string filePath ,json content);

    //renames the document in the file structure, updates fileName variable
    int renameDocument(std::string filepath, std::string newName);

    //adds an object to the document.
    //if object ID provided already exists in the database, existing object is overwritten, functioning as update.
    //object structure is as follows:
    /*
    "provided by function call":
    {
        "_id": "provided by function call"
        "_originFile": "this->fileName"
        any other relevant values
    }
    */
    int createObject(std::string filepath, json object);
    
    //deletes an object with a given id from the document
    int deleteObject(std::string filepath, std::string objectID);

    //checks if an object exists within the json document with given objectID.
    //returns 0 if object is not present, 1 if object is present.
    bool checkObject(std::string filepath, std::string objectID);

    //returns object with a given id.
    //if object exists, will return properly, otherwise will have unknown behavior.
    json getObject(std::string filepath, std::string objectID);

    //basic getter
    std::string getFileName();

    //basic setter
    void setFileName(std::string newFileName);

    //basic getter, returns full content of json document
    json getContent(std::string filepath);

    //stores json input back into document in filesystem
    int storeContent(std::string filepath, json content);
};

#endif