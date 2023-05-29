#include "userDatabase.hpp"

UserDatabase::UserDatabase(std::string databaseName) : databaseName(databaseName){

}

int UserDatabase::createCollection(std::string collectionName, json displayTemplate){
    auto iterator = this->getCollections()->find(collectionName);

    if(iterator == this->getCollections()->end()){
        std::string filepath = "./database/" + this->getDatabaseName() + "/" + collectionName;

        if(std::filesystem::create_directory(filepath)){
            return 1;
        }
        else{
            return -2;
        }

        this->collections.emplace(collectionName, /*Collection(collectionName, displayTemplate)*/ Collection()); //commented section should be re-instituted upon collection implementation
    }
    else{
        return -1;
    }
}

int UserDatabase::deleteCollection(std::string collectionName){
    auto iterator = this->getCollections()->find(collectionName);

    if(iterator != this->getCollections()->end()){
        std::string filepath = "./database/" + this->getDatabaseName() + "/" + collectionName;

        if(std::filesystem::remove_all(filepath)){
            return 1;
        }
        else{
            return -2;
        }
        
        this->collections.erase(collectionName);
    }
    else{
        return -1;
    }
}

int UserDatabase::renameCollection(std::string collectionName, std::string newCollectionName){
    auto iterator = this->getCollections()->find(collectionName);

    if(iterator != this->getCollections()->end()){
        auto handler = this->collections.extract(collectionName);
        handler.key() = newCollectionName;
        this->collections.insert(std::move(handler));
        
        std::string oldFilepath = "./database/" + this->getDatabaseName() + "/" + collectionName;
        std::string newFilepath = "./database/" + this->getDatabaseName() + "/" + newCollectionName;

        std::filesystem::rename(oldFilepath, newFilepath);
        
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

