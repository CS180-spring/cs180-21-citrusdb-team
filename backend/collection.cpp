#include "collection.hpp"

Collection::Collection(std::string filepath, std::string collectionName){

}

Collection::Collection(std::string filepath, std::string collectionName, std::string templateVariables){

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
            if(this->getDocument(oldDocumentName).renameDocument(filepath, newDocumentName) == 1){
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