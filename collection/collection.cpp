#include "collection.hpp"

using namespace std;

Collection::Collection() {}

Collection::Collection(string filepath) {
    this->filepath = filepath;
}

int Collection::createDocument(string documentName, string jsonTemplate) {
    
}

int Collection::deleteDocument(string documentName) {
    vector<Document> documents = getDocuments();
    documents.erase(documentName);
}

int Collection::renameDocument(string oldDocumentName, string newDocumentName) {
    
}

int Collection::replaceDocument(string originalDocumentName, string newDocumentName) {
    
}

Document Collection::getDocument(string documentName) {
    vector<Documents> documents = getDocuments();
    for(int i = 0; i < documents.size(); i++) {
        //search for doc with name 
    }
}

vector<Document> Collection::getDocuments() {
    return documents;
}

void Collection::createObject(string objectID, json object) {

}

void Collection::deleteObject(string objectID) {

}

void Collection::updateDocument() {

}

json Collection::getObject(string objectID) {

}

vector<string> Collection::listObjectIDs() {

}

json Collection::getContent() {

}
