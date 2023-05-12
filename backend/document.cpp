#include <string>
#include "document.hpp"
using namespace std;

Document::Document() {}

Document::Document(string filepath) {
    this->filepath = filepath;
    loadFile();
}

void Document::createObject(string objectID, json object) {
    content[objectID] = object;
}

void Document::deleteObject(string objectID) {
    content.erase(objectID);
}

void Document::updateDocument() {
    saveFile();
}

json Document::getObject(string objectID) {
    if (content.contains(objectID)) {
        return content[objectID];
    }
    return json();
}

vector<string> Document::listObjectIDs() {
    vector<string> objectIDs;
    for (auto& [key, value] : content.items()) {
        objectIDs.push_back(key);
    }
    return objectIDs;
}

json Document::getContent() {
    return content;
}

void Document::loadFile() {
    ifstream inFile(filepath);
    if (inFile.good()) {
        inFile >> content;
        inFile.close();
    }
}

void Document::saveFile() {
    ofstream outFile(filepath);
    outFile << content.dump(4);
    outFile.close();
}

void Document::clearContent() {
    content.clear();
}