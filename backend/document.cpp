#include <string>
#include <fstream>
#include "document.hpp"

Document::Document(string filepath, string filename) {
    this->filepath = filepath;
    this->filename = filename;
}

Document::Document(string filepath, string filename, json initialContent) {
    this->filepath = filepath;
    this->filename = filename;
    updateDocument(initialContent);
}

void Document::setName(const string& newfilename) {
    filename = newfilename;
}

string Document::getName() const {
    return filename;
}

int Document::createObject(string objectID, json object) {
    json content = getContent();
    content[objectID] = object;
    updateDocument(content);

    return 0;
}

int Document::deleteObject(string objectID) {
    json content = getContent();
    if (content.contains(objectID)) {
        content.erase(objectID);
        ofstream outFile(filepath);
        outFile << content.dump(4);
        outFile.close();
        return 0;
    }
    cout << "Error: File not found" << endl;
    return -1;
}

int Document::updateDocument(json newContent) {
    ofstream outFile(filepath);
    if (outFile.good()) {
        outFile << newContent.dump(4);
        outFile.close();
        return 0;
    }  
    cout << "Error: File not found" << endl;
    return -1; 
}

json Document::getObject(string objectID) {
    json content = getContent();
    if (content.contains(objectID)) {
        return content[objectID];
    }
    return json();
}

json Document::listObjectIDs() {
    json content = getContent();
    json objectIDs = json::array();
    for (auto& [key, value] : content.items()) {
        objectIDs.push_back(key);
    }
    return objectIDs;
}

json Document::getContent() {
    json content;
    ifstream inFile(filepath);
    if (inFile.good()) {
        inFile >> content;
        inFile.close();
    }
    else {
        cout << "Error: File not found" << endl;
        return json();
    }
    
    return content;
}