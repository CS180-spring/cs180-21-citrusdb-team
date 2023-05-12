#include "databaseEngine.hpp"
#include <iostream>

/// @brief Creates the Database Engine populating with the users listed in the metadata file
DatabaseEngine::DatabaseEngine()
{
    using json = nlohmann::json;
    json j_file = json::parse(readFile("../database/_metaDB.json"));
    json j_users = j_file["users"];
    for (json j_user : j_users ){
        std::cout<< j_user["username"] << std::endl;
    }
}

bool DatabaseEngine::createUser(const std::string &username, const std::string &email, const std::string &password, const std::string &collectionsAccess)
{
    return false;
}

bool DatabaseEngine::loginCheck(const std::string &username, const std::string &password) const
{
    return false;
}

bool DatabaseEngine::resetPassword(const std::string &username, const std::string &newPassword)
{
    return false;
}

UserDatabase DatabaseEngine::getUser(const std::string &username)
{
    return this->users[0];
}

bool DatabaseEngine::deleteUser(const std::string &username)
{
    return false;
}

/// @brief Testing only
/// @return 
int main(){
    DatabaseEngine dbe;

    return 0;
}