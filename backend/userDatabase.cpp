#include "userDatabase.hpp"

UserDatabase::UserDatabase(std::string databaseName) : databaseName(databaseName){
    std::string workingPath = "./database/" + databaseName; //workingPath = ./database/[username]
    std::string metaPath = "./database/" + databaseName + "/_meta.json"; //metaPath = ./database/[username]/_meta.json
    json content;

    //check if this is a recreation or actual new user
    if(std::filesystem::exists(workingPath)){
        //start recreation branch
        std::ifstream fin(metaPath);
        content = json::parse(fin);

        for(json::iterator i = content.begin() + 1; i != content.end(); i++){
            (*this->getCollections()).emplace(i.value(), Collection(workingPath, i.value()));
        }
    }
    else{
        //start actual new user branch
        std::filesystem::create_directory(workingPath);

        content["_meta.json"] = "_meta.json";

        std::ofstream fout(metaPath);

        fout << content;
    }
}

int UserDatabase::createCollection(std::string collectionName, std::string displayTemplate){
    if(this->checkCollection(collectionName) == 1){
        return -1;
    }

    std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
    std::string metaPath = "./database/" + this->getDatabaseName() + "/_meta.json"; //metaPath = ./database/[username]/_meta.json
    
    //read in metadata info to content
    std::ifstream fin(metaPath);
    json content = json::parse(fin);
    fin.close();

    //add collection to metadaata
    content[collectionName] = collectionName;

    //store metadata into metadata file
    std::ofstream fout(metaPath);
    fout << content;

    //add collection to unordered map
    this->getCollections()->emplace(collectionName, Collection(workingPath, collectionName, displayTemplate));

    return 1;
}

int UserDatabase::deleteCollection(std::string collectionName){
    //make sure collection is actually in the database
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName() + "/" + collectionName; //workingPath = ./database/[username]/[collectionName]

        //delete folder and all documents in folder form file directory
        std::filesystem::remove_all(workingPath);

        //erase collection form unordered_map
        this->getCollections()->erase(collectionName);

        std::string metaPath = "./database/" + this->getDatabaseName() + "/_meta.json"; //metaPath = ./database/[username]/_meta.json
        std::ifstream fin(metaPath);
        json content = json::parse(fin);
        fin.close();

        //update metadata info
        content.erase(collectionName);

        //store metadata info to metadata file
        std::ofstream fout;
        fout.open(metaPath, std::ofstream::trunc);

        fout << content;

        return 1;
    }
    else{
        return -1;
    }
}

bool UserDatabase::checkCollection(std::string collectionName){
    if(this->getCollections()->find(collectionName) != this->getCollections()->end()){
        return 1;
    }
    else{
        return 0;
    }
}

json UserDatabase::displayCollection(){
    json output;

    //iterate through all collections and add them to json object
    for(auto i: *this->getCollections()){
        output[i.first] = i.first;
    }

    return output;
}

json UserDatabase::filterDisplay(std::string query){
    json output;

    //iterate through all collections and output all collections containing requested substring
    for(auto i: *this->getCollections()){
        if(i.first.find(query) != std::string::npos){
            output[i.first] = i.first;
        }
    }

    return output;
}

Collection* UserDatabase::getCollection(std::string collectionName){
    return &this->collections[collectionName];
}

std::string UserDatabase::getDatabaseName(){
    return this->databaseName;
}

std::unordered_map<std::string, Collection>* UserDatabase::getCollections(){
    return &this->collections;
}

int UserDatabase::renameCollection(std::string oldCollectionName, std::string newCollectionName){
    //make sure oldcollectionname is present in the databse and the newcollectionname is not in the database
    if(this->checkCollection(oldCollectionName) == 1 && this->checkCollection(newCollectionName) != 1){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        std::string metaPath = workingPath + "/_meta.json"; //metaPath = //metaPath = ./database/[username]/_meta.json

        std::ifstream fin(metaPath);

        if(!fin){
            return -2;
        }

        //call funciton to rename the folder in file directory
        if(this->getCollection(oldCollectionName)->renameCollection(workingPath, oldCollectionName, newCollectionName) == 1){
            json content = json::parse(fin);

            //update metadata json object
            content.erase(oldCollectionName);
            content[newCollectionName] = newCollectionName;

            //store metadata file in file directory
            std::ofstream fout;
            fout.open(metaPath, std::ofstream::trunc);
            fout << content;

            //update collection map
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

int UserDatabase::createDocument(std::string collectionName, std::string documentName, std::string content){
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        return (*this->getCollections())[collectionName].createDocument(workingPath, documentName, json::parse(content));
    }
    else{
        return -1;
    }

}

int UserDatabase::deleteDocument(std::string collectionName, std::string documentName){
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        return (*this->getCollections())[collectionName].deleteDocument(workingPath, documentName);
    }
    else{
        return -1;
    }

}

int UserDatabase::replaceDocument(std::string collectionName, std::string documentName, std::string content){
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        return (*this->getCollections())[collectionName].replaceDocument(workingPath, documentName, json::parse(content));
    }
    else{
        return -1;
    }
}

json UserDatabase::displayObjects(std::string collectionName){
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        return (*this->getCollections())[collectionName].displayObjects(workingPath);
    }
    else{
        return -1;
    }
}
        
json UserDatabase::filterDisplay(std::string collectionName, json query){
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        return (*this->getCollections())[collectionName].filterDisplay(workingPath, query);
    }
    else{
        return -1;
    }
}
        
json UserDatabase::getTemplate(std::string collectionName){
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        return (*this->getCollections())[collectionName].getTemplate(workingPath);
    }
    else{
        return -1;
    }
}

int UserDatabase::renameDocument(std::string collectionName, std::string oldDocumentName, std::string newDocumentName){
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        return (*this->getCollections())[collectionName].renameDocument(workingPath, oldDocumentName, newDocumentName);
    }
    else{
        return -1;
    }
}

int UserDatabase::createObject(std::string collectionName,std::string documentName, std::string object){
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        return (*this->getCollections())[collectionName].createObject(workingPath, documentName, json::parse(object));
    }
    else{
        return -1;
    }
}

int UserDatabase::deleteObject(std::string collectionName, std::string documentName, std::string objectID){
    if(this->checkCollection(collectionName)){
        std::string workingPath = "./database/" + this->getDatabaseName(); //workingPath = ./database/[username]
        return (*this->getCollections())[collectionName].deleteObject(workingPath, documentName, objectID);
    }
    else{
        return -1;
    }
}