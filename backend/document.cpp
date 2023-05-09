#include <string>
#include "document.hpp"
using namespace std;

Document::Document() {

}

Document::Document(string filepath) {
    this->filepath = filepath;
}

void Document::createObject(string objectID, json object) {

}

void Document::deleteObject(string objectID) {

}

void Document::updateDocument() {

}

json Document::getObject(string objectID) {

}

vector<string> Document::listObjectIDs() {

}

json Document::getContent() {

}

void Document::loadFile() {

}

void Document::saveFile() {

}

void Document::clearContent() {

}