#include <string>
#include <fstream>
#include <iostream>
#include <./nlohmann/json.hpp>
using json = nlohmann::ordered_json;

class Document {
private:
    std::string filepath;
    
public:
    // constructors
    Document();
    Document(std::string filepath);

    // CRUD
    void createObject(std::string objectID, json object);
    void deleteObject(std::string objectID);
    void updateDocument();

    // Retrieves a JSON object with the given ID from the document
    json getObject(std::string objectID);

    // returns a vector of all object IDs in the document
    std::vector<std::string> listObjectIDs();


    // returns the current content of the document
    json getContent();

    void loadFile();
    void saveFile();
    void clearContent();
};