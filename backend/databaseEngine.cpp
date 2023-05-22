#include "databaseEngine.hpp"

void DatabaseEngine::writeToFile() const
{
    using json = nlohmann::json;
    using namespace std;
    json j_users;
    vector<map<string, string>> list;
    for (const auto i:users){
        map<string, string>  account = {
                {"username", i.second.getUsername()},
                {"email", i.second.getEmail()},
                {"password", i.second.getPassword()}
            };
        list.emplace_back(account);
    }
    j_users["users"] = list;
    ofstream output;
    output.open("_metaDB.json");
    output << j_users.dump(4);
    output.close();
}


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
    if (users.contains(username))
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
    writeToFile();
    return 1;
}

/// @brief Is the password entered valid?
/// @param username 
/// @param password 
/// @return a bool whether the username and password combination is valid
bool DatabaseEngine::loginCheck(const std::string &username, const std::string &password) 
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

/// @brief If associated username and email are found, return true; return false if otherwise
/// @param username 
/// @param email 
/// @return 
bool DatabaseEngine::resetPassword(const std::string &username, const std::string& email)
{
    if (users.contains(username)){
        if (users[username].getEmail() == email){
            // TODO: 
            // reset password email to be implemented
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

/// @brief Set a new password for a username. Return true if done successfully. Return false if 
/// username is not found or if password does not meet requirements
/// @param username 
/// @param newPassword 
/// @return 
bool DatabaseEngine::updatePassword(const std::string &username, const std::string &newPassword)
{
    if (users.contains(username)){
        if (newPassword.size() <= 4){
            return false;
        }
        users[username].setPassword(newPassword);
        writeToFile();
        return true;
    }
    else{
        return false;
    }
}

/// @brief Gets the user. Does not check if such username actually exists. Does not update file
/// @param username 
/// @return 
UserDatabase DatabaseEngine::getUser(const std::string &username)
{
    return users[username];
}

/// @brief Delete the associated user database. Return true if done. Return false if not.
/// @param username 
/// @return 
bool DatabaseEngine::deleteUser(const std::string &username)
{
    if (users.contains(username)){
        users.erase(username);
        writeToFile();
        return true;
    }
    else{
        return false;
    }
}

int main(){
    DatabaseEngine dbe;
    dbe.createUser("user", "poppler@gmail.com", "password2");
    dbe.deleteUser("alice");
    return 0;
}
