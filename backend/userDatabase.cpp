#include "userDatabase.hpp"

UserDatabase::UserDatabase(std::string databaseName) : databaseName(databaseName){

}

int UserDatabase::createCollection(std::string collectionName, json displayTempleate){
    auto iterator = this->collections.find(collectionName);

    if(iterator == this->collections.end()){
        this->collections.emplace(collectionName, /*Collection(collectionName, displayTempleate)*/ Collection()); //commented section should be re-instituted upon collection implementation

        return 1;
    }
    else{
        return -1;
    }
}

int UserDatabase::deleteCollection(std::string collectionName){
    auto iterator = this->collections.find(collectionName);

    if(iterator != this->collections.end()){
        this->collections.erase(collectionName);
    }
    else{
        return -1;
    }
}

int UserDatabase::renameCollection(std::string collectionName, std::string newCollectionName){
    auto iterator = this->collections.find(collectionName);

    if(iterator != this->collections.end()){
        auto handler = this->collections.extract(collectionName);
        handler.key() = newCollectionName;
        this->collections.insert(std::move(handler));
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

