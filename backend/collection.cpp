#include "collection.hpp"

Collection::Collection(std::string filepath, std::string collectionName){
    
}

Collection::Collection(std::string filepath, std::string collectionName, std::string templateVariables){

}

int Collection::createDocument(std::string filepath, std::string documentName, json content){


}
int Collection::deleteDocument(std::string filepath, std::string documentName){

}

int Collection::replaceDocument(std::string filepath, std::string documentName, json content){

}

int Collection::checkDocument(std::string documentName){
    if(this->getDocuments()->find(documentName) != this->getDocuments()->end()){
        return 1;
    }
    else{
        return -1;
    }
}

Document Collection::getDocument(std::string documentName){
    return (*this->getDocuments())[documentName];
}

std::string Collection::getCollectionName(){
    return this->collectionName;
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
            if(this->getDocument(oldDocumentName).renameDocument(workingPath, newDocumentName) == 1){
                json content;

                fin >> content;

                content.erase(oldDocumentName);
                content[newDocumentName] = newDocumentName;

                std::ofstream fout;
                fout.open(metaPath, std::ofstream::trunc);

                fout << content;

                Document temp = this->getDocument(oldDocumentName);
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
    if(this->checkDocument(documentName) == 1){
        std::string workingPath = filepath + "/" + this->getCollectionName();

        return this->getDocument(documentName).createObject(workingPath, objectID, object);
    }
    else{
        return -1;
    }
}

int Collection::deleteObject(std::string filepath, std::string documentName, std::string objectID){
    if(this->checkDocument(documentName) == 1){
        std::string workingPath = filepath + "/" + this->getCollectionName();

        return this->getDocument(documentName).deleteObject(workingPath, objectID);
    }
    else{
        return -1;
    }
}

int Collection::checkObject(std::string filepath, std::string documentName, std::string objectID){
    if(this->checkDocument(documentName) == 1){
        std::string workingPath = filepath + "/" + this->getCollectionName();

        return this->getDocument(documentName).checkObject(workingPath, objectID);
    }
    else{
        return -1;
    }
}

json Collection::getObject(std::string filepath, std::string documentName, std::string objectID){
    if(this->checkDocument(documentName) == 1){
        std::string workingPath = filepath + "/" + this->getCollectionName();

        return this->getDocument(documentName).getObject(workingPath, objectID);
    }
    else{
        return -1;
    }
}