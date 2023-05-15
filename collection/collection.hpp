#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

class Document;

using namespace std;

class Collection {
private:
    string filePath;
    
    vector<Document> documents;
    
public:
    Collection(string filePath);
    
    int createDocument(string documentName, string jsonTemplate);

    int deleteDocument(string documentName);

    int renameDocument(string oldDocumentName, string newDocumentName);

    int replaceDocument(string originalDocumentName, string newDocumentName);

    Document getDocument(string documentName);

    vector<Document> getDocuments();
    
    int createObject();

    int deleteObject();

    int updateDocument();

    string getObject();

    string listObjectIDs();

    string getObjectID();

    string getDocumentContent();
};
