#include "collection.hpp"

Collection::Collection(std::string filepath, std::string collectionName): collectionName(collectionName){
    std::string metaPath = filepath + "/" + collectionName +"/_meta.json";
    json content;

    std::ifstream fin(metaPath);
    fin >> content;

    for(json::iterator i = content.begin() + 1; i != content.end(); i++){
        (*this->getDocuments()).emplace(i.value(), Document(i.value()));
    }
}

Collection::Collection(std::string filepath, std::string collectionName, std::string templateVariables): collectionName(collectionName){
    json metaContent;
    std::istringstream sin(templateVariables);

    while(!sin.eof()){
        std::string temp = "";

        std::getline(sin, temp);

        metaContent[temp] = temp;
    }
    json content;

    content["_meta.json"] = metaContent;

    std::string metaPath = filepath + "/" + collectionName + "/_meta.json";

    std::ofstream fout(metaPath);
    fout << content;
}

int Collection::renameCollection(std::string filepath, std::string oldCollectionName, std::string newCollectionName){
    std::string currentPath = filepath + "/" + oldCollectionName;
    std::string newPath = filepath + "/" + newCollectionName;

    char cPath[currentPath.size() + 1];
    char nPath[newPath.size() + 1];

    std::strcpy(cPath, currentPath.c_str());
    std::strcpy(nPath, newPath.c_str());if(std::rename(cPath, nPath) == 0){
        this->setCollectionName(newCollectionName);
        return 1;
    }
    else{
        return -1;
    }
}

int Collection::createDocument(std::string filepath, std::string documentName, json content){
    std::string workingPath = filepath + "/" + this->getCollectionName();

    if(this->checkDocument(documentName) == 1){
        return -1;
    }
    else{
        std::string metaPath = workingPath + "/_meta.json";
        json templateInfo;
        std::ifstream fin(metaPath);

        fin >> templateInfo;

        templateInfo = templateInfo["_meta.json"];

        if(!content.empty()){
            for(json::iterator i = content.begin(); i != content.end(); i++){
                if(!(i.value().contains("_id") && i.value().contains("_originFile"))){
                    return -2;
                }

                for(json::iterator j = templateInfo.begin(); j != templateInfo.end(); j++){
                    if(!i.value().contains(j.key())){
                        return -2;
                    }
                }
            }
        }
        
        this->getDocuments()->emplace(documentName, Document(documentName, workingPath, content));
    }
}
int Collection::deleteDocument(std::string filepath, std::string documentName){ 
    if(this->getDocuments()->find(collectionName) != this->getDocuments()->end()){
        std::string workingPath = filepath + "/" + this->getCollectionName() + "/" + documentName;

        std::filesystem::remove(workingPath);

        this->getDocuments()->erase(documentName);

        std::string metaPath = filepath + "/" = this->getCollectionName() + "/_meta.json";
        json content;

        std::ifstream fin(metaPath);

        fin >> content;

        content.erase(documentName);

        std::ofstream fout;
        fout.open(metaPath, std::ofstream::trunc);

        fout << content;

        return 1;
    }
    else{
        return -1;
    }
}

int Collection::replaceDocument(std::string filepath, std::string documentName, json content){
    if(this->getDocuments()->find(documentName) != this->getDocuments()->end()){
        std::string workingPath = filepath + "/" + this->getCollectionName() + "/" + documentName;

        if(!content.empty()){
            std::string metaPath = filepath + "/" + this->getCollectionName() + "/_meta.json";
            json templateInfo;
            std::ifstream fin(metaPath);

            fin >> templateInfo;

            templateInfo = templateInfo["_meta.json"];
            
            for(json::iterator i = content.begin(); i != content.end(); i++){
                if(!(i.value().contains("_id") && i.value().contains("_originFile"))){
                    return -2;
                }

                for(json::iterator j = templateInfo.begin(); j != templateInfo.end(); j++){
                    if(!i.value().contains(j.key())){
                        return -2;
                    }
                }
            }
        }

        std::ofstream fout;
        fout.open(workingPath, std::ofstream::trunc);

        if(fout){
            fout << content;

            return 1;
        }
        else{
            return -3;
        }
    }
    else{
        return -1;
    }
}

int Collection::checkDocument(std::string documentName){
    if(this->getDocuments()->find(documentName) != this->getDocuments()->end()){
        return 1;
    }
    else{
        return -1;
    }
}

Document* Collection::getDocument(std::string documentName){
    return &(*this->getDocuments())[documentName];
}

std::string Collection::getCollectionName(){
    return this->collectionName;
}

void Collection::setCollectionName(std::string newCollectionName){
    this->collectionName = newCollectionName;
}

std::unordered_map<std::string, Document>* Collection::getDocuments(){
    return &this->documents;
}

//start passthrough functions to Document

int Collection::renameDocument(std::string filepath, std::string oldDocumentName, std::string newDocumentName){
    if(this->checkDocument(oldDocumentName) == 1 && this->checkDocument(newDocumentName) != 1){
        std::string workingPath = filepath + "/" + this->getCollectionName();
        std::string metaPath = filepath + "/_meta.json";

        std::ifstream fin(metaPath);

        if(!fin){
            return -3;
        }
        else{
            if(this->getDocument(oldDocumentName)->renameDocument(workingPath, newDocumentName) == 1){
                json content;

                fin >> content;

                content.erase(oldDocumentName);
                content[newDocumentName] = newDocumentName;

                std::ofstream fout;
                fout.open(metaPath, std::ofstream::trunc);

                fout << content;

                Document temp = *this->getDocument(oldDocumentName);
                this->getDocuments()->erase(oldDocumentName);
                this->getDocuments()->emplace(newDocumentName, temp);

                return 1;
            }
            else{
                return -2;
            }
        }


    }
    else{
        return -1;
    }
}

int Collection::createObject(std::string filepath,std::string documentName, std::string objectID, json object){
    if(!object.empty()){
        std::string metaPath = filepath + "/" + this->getCollectionName() + "/_meta.json";
        json templateInfo;
        std::ifstream fin(metaPath);

        fin >> templateInfo;

        templateInfo = templateInfo["_meta.json"];
            
        for(json::iterator i = object.begin(); i != object.end(); i++){
            for(json::iterator j = templateInfo.begin(); j != templateInfo.end(); j++){
                if(!i.value().contains(j.key())){
                    return -2;
                }
            }
        }
    }
    else{
        return -1;
    }

    if(this->checkDocument(documentName) == 1){
        std::string workingPath = filepath + "/" + this->getCollectionName();

        return this->getDocument(documentName)->createObject(workingPath, objectID, object);
    }
    else{
        json temp;
        temp[objectID] = object;
        temp[objectID]["_id"] = objectID;
        temp[objectID]["_originFIle"] = documentName;
        this->createDocument(filepath, documentName, temp);
    }
}

int Collection::deleteObject(std::string filepath, std::string documentName, std::string objectID){
    if(this->checkDocument(documentName) == 1){
        std::string workingPath = filepath + "/" + this->getCollectionName();

        return this->getDocument(documentName)->deleteObject(workingPath, objectID);
    }
    else{
        return -1;
    }
}