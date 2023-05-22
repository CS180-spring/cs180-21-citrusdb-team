#ifndef DATABASENGINE_HPP
#define DATABASENGINE_HPP
#include <unordered_map>
#include <map>
#include <string>
#include "../nlohmann/json.hpp"
#include "file.hpp"
#include "userDatabase.hpp"

class DatabaseEngine{
    private:
    // map between username <-> userDatabase
    std::unordered_map<std::string, UserDatabase> users;
    void writeToFile() const;
    public:
    DatabaseEngine();
    int createUser(const std::string& username, const std::string& email, const std::string& password);
    bool loginCheck(const std::string& username, const std::string& password);
    bool resetPassword(const std::string& username, const std::string& email);
    bool updatePassword(const std::string& username, const std::string& newPassword);
    UserDatabase getUser(const std::string& username);
    bool deleteUser(const std::string& username);
};

#endif