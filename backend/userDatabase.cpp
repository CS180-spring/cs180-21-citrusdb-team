#include "userDatabase.hpp"

UserDatabase::UserDatabase(std::string databaseName) : databaseName(databaseName){
    std::string workingPath = "./database/" + databaseName;
    std::string metaPath = "./database/" + databaseName + "/_meta.json";
    json content;

    std::ifstream fin(metaPath);
    fin >> content;

    for(json::iterator i = content.begin(); i != content.end(); i++){
        (*this->getCollections()).emplace(i.value(), Collection(workingPath, i.value()));
    }
}

int UserDatabase::createCollection(std::string collectionName, std::string displayTemplate){
    if(this->checkCollection(collectionName) == 1){
        return -1;
    }
    else{
        std::string workingPath = "./database/" + this->getDatabaseName();
        std::string metaPath = "./database/" + this->getDatabaseName() + "/_meta.json";
        json content;

        std::ifstream fin(metaPath);

        fin >> content;

        content[collectionName] = collectionName;

        this->getCollections()->emplace(collectionName, Collection(workingPath, collectionName, displayTemplate));

        return 1;
    }
}

int UserDatabase::deleteCollection(std::string collectionName){
    if(this->checkCollection(collectionName) == 1){
        std::string workingPath = "./database/" + this->getDatabaseName() + "/" + collectionName;

        std::filesystem::remove_all(workingPath);

        this->getCollections()->erase(collectionName);

        std::string metaPath = "./database/" + this->getDatabaseName() + "/_meta.json";
        json content;

        std::ifstream fin(metaPath);

        fin >> content;

        content.erase(collectionName);

        std::ofstream fout;
        fout.open(metaPath, std::ofstream::trunc);

        fout << content;

        return 1;
    }
    else{
        return -1;
    }
}

int UserDatabase::checkCollection(std::string collectionName){
    if(this->getCollections()->find(collectionName) != this->getCollections()->end()){
        return 1;
    }
    else{
        return -1;
    }
}

Collection* UserDatabase::getCollection(std::string collectionName){
    return &this->collections[collectionName];
}

std::string UserDatabase::getDatabaseName(){
    return this->databaseName;
}

std::map<std::string, Collection>* UserDatabase::getCollections(){
    return &this->collections;
}

int UserDatabase::renameCollection(std::string oldCollectionName, std::string newCollectionName){
    if(this->checkCollection(oldCollectionName) == 1 && this->checkCollection(newCollectionName) != 1){
        std::string workingPath = "./database/" + this->getDatabaseName();
        std::string metaPath = workingPath + "/_meta.json";

        std::ifstream fin(metaPath);

        if(!fin){
            return -2;
        }

        if(this->getCollection(oldCollectionName)->renameCollection(workingPath, oldCollectionName, newCollectionName) == 1){
            json content;

            fin >> content;

            content.erase(oldCollectionName);
            content[newCollectionName] = newCollectionName;

            std::ofstream fout;
            fout.open(metaPath, std::ofstream::trunc);

            fout << content;

            Collection temp = *this->getCollection(oldCollectionName);

            this->getCollections()->erase(oldCollectionName);
            this->getCollections()->emplace(newCollectionName, temp);

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

int UserDatabase::createDocument(std::string collectionName, std::string documentName, json content){
    if(this->checkCollection(collectionName) == 1){
        std::string workingPath = "./database/" + this->getDatabaseName();
        return (*this->getCollections())[collectionName].createDocument(workingPath, documentName, content);
    }
    else{
        return -1;
    }

}

int UserDatabase::deleteDocument(std::string collectionName, std::string documentName){
    if(this->checkCollection(collectionName) == 1){
        std::string workingPath = "./database/" + this->getDatabaseName();
        return (*this->getCollections())[collectionName].deleteDocument(workingPath, documentName);
    }
    else{
        return -1;
    }

}

int UserDatabase::replaceDocument(std::string collectionName, std::string documentName, json content){
    if(this->checkCollection(collectionName) == 1){
        std::string workingPath = "./database/" + this->getDatabaseName();
        return (*this->getCollections())[collectionName].replaceDocument(workingPath, documentName, content);
    }
    else{
        return -1;
    }
}

int UserDatabase::renameDocument(std::string collectionName, std::string oldDocumentName, std::string newDocumentName){
    if(this->checkCollection(collectionName) == 1){
        std::string workingPath = "./database/" + this->getDatabaseName();
        return (*this->getCollections())[collectionName].renameDocument(workingPath, oldDocumentName, newDocumentName);
    }
    else{
        return -1;
    }
}

int UserDatabase::createObject(std::string collectionName,std::string documentName, std::string objectID, json object){
    if(this->checkCollection(collectionName) == 1){
        std::string workingPath = "./database/" + this->getDatabaseName();
        return (*this->getCollections())[collectionName].createObject(workingPath, documentName, objectID, object);
    }
    else{
        return -1;
    }
}

int UserDatabase::deleteObject(std::string collectionName, std::string documentName, std::string objectID){
    if(this->checkCollection(collectionName) == 1){
        std::string workingPath = "./database/" + this->getDatabaseName();
        return (*this->getCollections())[collectionName].deleteObject(workingPath, documentName, objectID);
    }
    else{
        return -1;
    }
}