#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <./nlohmann/json.hpp>
using namespace std;
using json = nlohmann::ordered_json;

class Document {
public:
    // constructors
    Document(string filepath, string filename);
    Document(string filepath, string filename, json initialContent);

    void setName(const string& newfilename);
    string getName() const;

    // CRUD
    int createObject(string objectID, json object);
    int deleteObject(string objectID);
    int updateDocument(json object);

    // Retrieves a JSON object with the given ID from the document
    json getObject(string objectID);

    // returns a vector of all object IDs in the document
    json listObjectIDs();

    // returns the current content of the document
    json getContent();

private:
    string filepath;
    string filename;
};