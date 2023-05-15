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
    
    int createDocument();

    int deleteDocument();

    int renameDocument();

    int replaceDocument();

    Document getDocument();

    vector<Document> getDocuments();
    
    int createObject();

    int deleteObject();

    int updateDocument();

    string getObject();

    string listObjectIDs();

    string getObjectID();

    string getDocumentContent();
};
