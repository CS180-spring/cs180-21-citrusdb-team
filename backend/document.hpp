#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::ordered_json;

class Document {
public:
    // constructors
    Document();
    Document(string filepath);

    // CRUD
    void createObject(string objectID, json object);
    void deleteObject(string objectID);
    void updateDocument();

    // Retrieves a JSON object with the given ID from the document
    json getObject(string objectID);

    // returns a vector of all object IDs in the document
    vector<string> listObjectIDs();


    // returns the current content of the document
    json getContent();

    void loadFile();
    void saveFile();
    void clearContent();

private:
    string filepath;
};