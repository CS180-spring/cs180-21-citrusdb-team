#include "document.hpp"

Document::Document(std::string fileName): fileName(fileName) {}

Document::Document(std::string fileName, std::string filePath ,json content): fileName(fileName) {
    std::string workingPath = filePath + "/" + fileName; //working path = ./database/[username]/[collectionName]/[filename]

    std::ofstream fout(workingPath); 

    fout << content; //store data without any additional formatting
}

int Document::renameDocument(std::string filepath, std::string newName){
    std::string currentPath = filepath + "/" + this->getFileName(); //currentpath = ./database/[username]/[collectionName]/[filename]
    std::string newPath = filepath + "/" + this->getFileName(); //newpath = ./database/[username]/[collectionName]/[newName]

    std::filesystem::rename(currentPath, newPath); //unable to check if operation was conducted, return type is void. Must check if operation is possible at collection level.
    this->setFileName(newName);

    //begin iterating through content of document to update "_originFile" variable.
    json content = this->getContent(filepath);

    for(json::iterator i = content.begin(); i != content.end(); i++){
        i.value()["_originFile"] = newName;
    }

    //store content back into file
    if(this->storeContent(filepath, content)){
        return 1;
    }
    else{
        return -2;
    }
}

int Document::createObject(std::string filepath, json object){
    std::string workingPath = filepath + "/" + this->getFileName(); //working path = ./database/[username]/[collectionName]/[filename]

    //read in content of file into content variable
    json content = this->getContent(filepath);

    //store object into content of docuent
    content[object["_objectID"]] = object;

    //store content back into file
    if(this->storeContent(filepath, content)){
        return 1;
    }
    else{
        return -2;
    }
}
    
int Document::deleteObject(std::string filepath, std::string objectID){
    std::string workingPath = filepath + "/" + this->getFileName(); //working path = ./database/[username]/[collectionName]/[filename]

    //read in file info
    json content = this->getContent(filepath);

    //check if object is actually in document
    if(this->checkObject(filepath, objectID) == 1){
        //deletion operation
        content.erase(objectID);
    }
    else{
        return -1;
    }
    //store content back into file
    if(this->storeContent(filepath, content)){
        return 1;
    }
    else{
        return -2;
    }
}

bool Document::checkObject(std::string filepath, std::string objectID){
    std::string workingPath = filepath + "/" + this->getFileName();

    json content = this->getContent(workingPath);

    if(content.find(objectID) == content.end()){
        return 0;
    }
    else{
        return 1;
    }
}

json Document::getObject(std::string filepath, std::string objectID){
    std::string workingPath = filepath + "/" + this->getFileName();

    return this->getContent(workingPath)[objectID];
}

std::string Document::getFileName(){
    return this->fileName;
}

void Document::setFileName(std::string newFileName){
    this->fileName = newFileName;
}

json Document::getContent(std::string filepath){
    std::string workingPath = filepath + "/" + this->getFileName();

    std::ifstream fin(workingPath);

    return json::parse(workingPath);
}

int Document::storeContent(std::string filepath, json content){
    std::string workingPath = filepath + "/" + this->getFileName();

    std::ofstream fout(workingPath, std::ofstream::trunc);

    if(!fout){
        return 0;
    }
    
    fout << content;

    return 1;
}