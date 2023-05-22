#include "collection.hpp"
#include <algorithm>

using namespace std;

Collection::Collection() {}

Collection::Collection(string filepath) {
    this->filepath = filepath;
    //create metadata file; one metadata file for each collection; ensure user doc doesn't match meta data file name
    //metadata file stores name of json doc and what columns are being displayed on frontend in respective collection
    //standard stream
}

int Collection::createDocument(string documentName, json jsonTemplate) {
    //creates json doc and stores it in the file path
    //standard stream
}

int Collection::deleteDocument(string documentName) {
    map<string, Document> documents = getMap();
    if(documents.find(documentName) != documents.end()) {
        documents.erase(documentName);
        cout << "Document found and deleted." << endl;
        return 0;
    }
    cout << "Document with name not found, please try again." << endl;
    return -1;
}

int Collection::renameDocument(string oldDocumentName, string newDocumentName) {
    map<string, Document> documents = getMap();
    if(documents.find(oldDocumentName) != documents.end()) {
        auto nodeHandler = documents.extract(oldDocumentName);
        nodeHandler.key() = newDocumentName;
        documents.insert(move(nodeHandler));
        documents[newDocumentName].setName(newDocumentName);
        cout << "Document found and renamed." << endl;
        return 0;
    }
    cout << "Document with name not found, please try again." << endl;
    return -1;
}

int Collection::replaceDocument(string originalDocumentName, string newDocumentName, Document newDocument) {
    map<string, Document> documents = getMap();
    if(documents.find(oldDocumentName) != documents.end()) {
        auto nodeHandler = documents.extract(oldDocumentName);
        nodeHandler.key() = newDocumentName;
        documents.insert(move(nodeHandler));
        map<string, Document>::iterator it = documents.find(newDocumentName);
        if(it != documents.end()) {
            it->second = newDocument;
        }
        cout << "Document found and replaced." << endl;
        return 0;
    }
    cout << "Document with name not found, please try again." << endl;
    return -1;
}

Document Collection::getDocument(string documentName) {
    map<string, Document> documents = getMap();
    if(documents.find(documentName) != documents.end()) {
        cout << "Document found and returned." << endl;
        return documents[documentName];
    }
    cout << "Document with name not found, please try again." << endl;
    return;
}

vector<Document> Collection::getDocuments() {
    map<string, Document> map = getMap();
    vector<Document> values;
    for(auto it = map.begin(); it != map.end(); it++) {
        values.push_back(it->first);
    }
    return values;
}

map<string, Document> Collection::getMap() {
    return documents;
}

void Collection::createObject(string objectID, json object, string documentName) {
    map<string, Document> documents = getMap();
    documents[documentName].createObject(objectID, object);
}

void Collection::deleteObject(string objectID, string documentName) {
    map<string, Document> documents = getMap();
    documents[documentName].deleteObject(objectID);
    //this->getMap()[documentName].deleteObject(objectID);
}

void Collection::updateDocument(string documentName) {
    map<string, Document> documents = getMap();
    documents[documentName].updateDocument();
}

json Collection::getObject(string objectID, string documentName) {
    map<string, Document> documents = getMap();
    return documents[documentName].getObject(objectID);
}

vector<string> Collection::listObjectIDs(string documentName) {
    map<string, Document> documents = getMap();
    return documents[documentName].listObjectIDs();
}

json Collection::getContent(string documentName) {
    map<string, Document> documents = getMap();
    return documents[documentName].getContent();
}
