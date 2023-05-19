#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <./nlohmann/json.hpp>

class Document;

using json = nlohmann::ordered_json;
using namespace std;

class Collection {
private:
    string filePath;
    
    map<string, Document> documents;
    
public:
    Collection(string filePath);
    
    int createDocument(string documentName, string jsonTemplate);

    int deleteDocument(string documentName);

    int renameDocument(string oldDocumentName, string newDocumentName);

    int replaceDocument(string originalDocumentName, string newDocumentName, Document newDocument);

    Document getDocument(string documentName);
    
    vector<Document> getDocuments();
    
    map<string, Document> getMap();
    
    int createObject();

    int deleteObject();

    int updateDocument();

    string getObject();

    string listObjectIDs();

    string getObjectID();

    string getDocumentContent();
};
