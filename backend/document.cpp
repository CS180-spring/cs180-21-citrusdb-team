#include "document.hpp"

Document::Document(std::string fileName): fileName(fileName) {}

Document::Document(std::string fileName, std::string filePath ,json content): fileName(fileName) {
    std::string workingPath = filePath + "/" + fileName;

    std::ofstream fout(workingPath);

    fout << content;
}

int Document::renameDocument(std::string filepath, std::string newName){
    std::string currentPath = filepath + "/" + this->getFileName();
    std::string newPath = filepath + "/" + this->getFileName();

    char cPath[currentPath.size() + 1];
    char nPath[newPath.size() + 1];

    std::strcpy(cPath, currentPath.c_str());
    std::strcpy(nPath, newPath.c_str());

    if(std::rename(cPath, nPath) == 0){
        this->setFileName(newName);
        return -1;
    }
    else{
        return 1;
    }
}

int Document::createObject(std::string filepath, std::string objectID, json object){
    std::string workingPath = filepath + "/" + this->getFileName();
    json content;

    std::ifstream fin;
    fin.open(workingPath);

    if(!fin){
        return -1;
    }

    fin >> content;
    fin.close();

    content[objectID] = object;
    content[objectID]["id"] = objectID;
    content[objectID]["originFile"] = this->getFileName();

    std::ofstream fout;
    fout.open(workingPath, std::ofstream::trunc);

    if(!fout){
        return -2;
    }

    fout << content;

    fout.close();

    return 1;
}
    
int Document::deleteObject(std::string filepath, std::string objectID){
    std::string workingPath = filepath + "/" + this->getFileName();
    json content;

    std::ifstream fin;
    fin.open(workingPath);

    if(!fin){
        return -1;
    }

    fin >> content;
    fin.close();

    content.erase(objectID);

    std::ofstream fout;
    fout.open(workingPath, std::ofstream::trunc);

    if(!fout){
        return -2;
    }

    fout << content;

    return 1;
}

int Document::checkObject(std::string filepath, std::string objectID){
    std::string workingPath = filepath + "/" + this->getFileName();

    json content = this->getContent(workingPath);

    if(content.find(objectID) == content.end()){
        return -1;
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