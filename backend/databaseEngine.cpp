#include "databaseEngine.hpp"
#include <iostream>

/// @brief Creates the Database Engine populating with the users listed in the metadata file
DatabaseEngine::DatabaseEngine()
{
    using json = nlohmann::json;
    json j_file = json::parse(readFile("../database/_metaDB.json"));
    json j_users = j_file["users"];

    for (json j_user : j_users ){
        std::string username = to_string(j_user["username"]);
        username = username.substr(1, username.size() - 2);
        std::string email = to_string(j_user["email"]);
        email = email.substr(1, email.size() - 2);
        std::string password = to_string(j_user["password"]);
        password = password.substr(1, password.size() - 2);
        users[username] = UserDatabase(username, email, password);
    }
}

/// @brief Create a new UserDatabase. If the username already exists, return 0. If the email already exists, return -1.
/// If the password is invalid, return -2. If the user was successfully created, return 1.
/// @param username 
/// @param email 
/// @param password 
/// @return 
int DatabaseEngine::createUser(const std::string &username, const std::string &email, const std::string &password)
{
    if (!users.contains(username))
        return 0;
    for (auto userDB: users){
        // found existing email
        if (email == userDB.second.getEmail())
            return -1;
    }
    // could implement other password checks
    if (password.size() < 4)
        return -2;
    // all "checks" are complete; good to create user
    users[username] = UserDatabase(username, email, password);
    return 1;
}

/// @brief Is the password entered valid?
/// @param username 
/// @param password 
/// @return a bool whether the username and password combination is valid
bool DatabaseEngine::loginCheck(const std::string &username, const std::string &password) const
{
    if (users.contains(username)){
        
        if (users[username].getPassword() == password){
            return true;
        }
        else {
            return false;
        }
    }
    else{
        return false;
    }
}

bool DatabaseEngine::resetPassword(const std::string &username)
{
    return false;
}

bool DatabaseEngine::updatePassword(const std::string &username, const std::string &newPassword)
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