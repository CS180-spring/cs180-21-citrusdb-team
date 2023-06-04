#include "databaseEngine.hpp"

void DatabaseEngine::writeToFile(const nlohmann::json &content) const
{
    using json = nlohmann::json;
    using namespace std;
    ofstream output;
    output.open("database/_metaDB.json");
    output << content.dump(4);
    output.close();
}

/// @brief Creates the Database Engine populating with the users listed in the metadata file
DatabaseEngine::DatabaseEngine()
{
    using json = nlohmann::json;
    json j_file = json::parse(readFile("database/_metaDB.json"));
    json j_users = j_file["users"];

    for (json &j_user : j_users)
    {
        std::string username = to_string(j_user["username"]);
        username = username.substr(1, username.size() - 2);
        users[username] = UserDatabase(username);
    }
}

/// @brief Create a new UserDatabase. If the username already exists, return -3. If the email already exists, return -1.
/// If the password is invalid, return -2. If the user was successfully created, return 1.
/// @param username
/// @param email
/// @param password
/// @return
int DatabaseEngine::createUser(const std::string &username, const std::string &email, const std::string &password)
{
    namespace fs = std::filesystem;
    if (users.contains(username))
        return -3;
    json j_file = json::parse(readFile("database/_metaDB.json"));
    for (const json &j_user : j_file["users"])
    {
        std::string existingEmail = to_string(j_user["email"]);
        existingEmail = existingEmail.substr(1, existingEmail.size() - 2);
        if (existingEmail == email)
        {
            return -1;
        }
    }
    // could implement other password checks
    if (password.size() < 3)
        return -2;
    // all "checks" are complete; good to create user
    // fs::current_path(fs::temp_directory_path());
    // if (!fs::create_directory("database/" + username)){
    //     // failed to create a directory
    //     return -1;
    // }
    users[username] = UserDatabase(username);
    writeToFile(j_file);
    
    return 1;
}

/// @brief Is the password entered valid?
/// @param username
/// @param password
/// @return a bool whether the username and password combination is valid
bool DatabaseEngine::loginCheck(const std::string &username, const std::string &password) const
{

    if (users.contains(username))
    {
        json j_file = json::parse(readFile("database/_metaDB.json"));
        for (const json &j_user : j_file["users"])
        {
            std::string existingUsername = to_string(j_user["username"]);
            existingUsername = existingUsername.substr(1, existingUsername.size() - 2);
            if (existingUsername == username)
            {
                std::string existingPassword = to_string(j_user["password"]);
                existingPassword = existingPassword.substr(1, existingPassword.size() - 2);
                if (existingPassword == password)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        // something went really wrong if reached here
        return false;
    }
    else
    {
        return false;
    }
}

/// @brief If associated username and email are found, return true; return false if otherwise.
/// Does not do much else
/// @param username
/// @param email
/// @return
bool DatabaseEngine::resetPassword(const std::string &username, const std::string &email) const
{
    if (users.contains(username))
    {
        json j_file = json::parse(readFile("database/_metaDB.json"));
        for (const json &j_user : j_file["users"])
        {
            std::string existingUsername = to_string(j_user["username"]);
            existingUsername = existingUsername.substr(1, existingUsername.size() - 2);
            if (existingUsername == username)
            {
                std::string existingEmail = to_string(j_user["email"]);
                existingEmail = existingEmail.substr(1, existingEmail.size() - 2);
                if (existingEmail == email)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}

/// @brief Set a new password for a username. Return true if done successfully. Return false if
/// username is not found or if password does not meet requirements
/// @param username
/// @param newPassword
/// @return
bool DatabaseEngine::updatePassword(const std::string &username, const std::string &newPassword) const
{
    if (users.contains(username))
    {
        json j_file = json::parse(readFile("database/_metaDB.json"));
        for (json &j_user : j_file["users"])
        {
            std::string existingUsername = to_string(j_user["username"]);
            existingUsername = existingUsername.substr(1, existingUsername.size() - 2);
            if (existingUsername == username)
            {
                j_user["password"] = newPassword;
                writeToFile(j_file);
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}

/// @brief Gets the user. Does not check if such username actually exists. Does not update file
/// @param username
/// @return
UserDatabase *DatabaseEngine::getUser(const std::string &username)
{
    return &users[username];
}

/// @brief Delete the associated user database. Return true if done. Return false if not.
/// @param username
/// @return
bool DatabaseEngine::deleteUser(const std::string &username)
{
    if (users.contains(username))
    {
        json j_file = json::parse(readFile("database/_metaDB.json"));
        for (json &j_user : j_file["users"])
        {
            std::string existingUsername = to_string(j_user["username"]);
            existingUsername = existingUsername.substr(1, existingUsername.size() - 2);
            if (existingUsername == username)
            {
                j_file["users"].erase(j_user);
                users.erase(username);
                if (!std::filesystem::remove_all("database/"+username)){
                    // could not delete the folder or the folder does not exist
                    return false;
                }
                writeToFile(j_file);
                return true;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}

int DatabaseEngine::createCollection(const std::string &username, const std::string &collection, const std::string& labels)
{
    return users[username].createCollection(collection, labels);
}

int DatabaseEngine::deleteCollection(const std::string &username, const std::string &collection)
{
    return users[username].deleteCollection(collection);
}

int DatabaseEngine::renameCollection(const std::string &username, const std::string &oldName, const std::string &newName)
{
    return users[username].renameCollection(oldName, newName);
}

Collection *DatabaseEngine::getCollection(const std::string &username, const std::string &collection)
{
    return users[username].getCollection(collection);
}

std::unordered_map<std::string, Collection> *DatabaseEngine::getCollections(const std::string &username)
{
    return users[username].getCollections();
}

int DatabaseEngine::createDocument(const std::string &username, const std::string &collection, const std::string &document)
{
    return users[username].createDocument(collection, document);
}

int DatabaseEngine::deleteDocument(const std::string &username, const std::string &collection, const std::string &document)
{
    return users[username].deleteDocument(collection, document);
}

int DatabaseEngine::renameDocument(const std::string &username, const std::string &collection, const std::string &oldDoc, const std::string &newDoc)
{
    return users[username].renameDocument(collection, oldDoc, newDoc);
}

int DatabaseEngine::replaceDocument(const std::string &username, const std::string &collection, const std::string &document, nlohmann::json object)
{
    return users[username].replaceDocument(collection, document, object);
}

// should be fixed
nlohmann::json DatabaseEngine::getContent(const std::string &username, const std::string &collection, const std::string &document)
{
    return users[username].getContent(collection, document);
}

int DatabaseEngine::createObject(const std::string &username, const std::string &collection, const std::string &document, nlohmann::json object)
{
    return users[username].createObject(collection, document, object);
}

int DatabaseEngine::deleteObject(const std::string &username, const std::string &collection, const std::string &document, const std::string &objectID)
{
    return users[username].deleteObject(collection, document, objectID);
}

int DatabaseEngine::updateDocument(const std::string &username, const std::string &collection, const std::string &document, nlohmann::json object)
{
    return users[username].updateDocument(collection, document, object);
}
