#ifndef DATABASENGINE_HPP
#define DATABASENGINE_HPP
#include <vector>
#include <string>
#include "../nlohmann/json.hpp"
#include "file.hpp"
#include "userDatabase.hpp"

class DatabaseEngine{
    private:
    std::vector<UserDatabase> users;
    public:
    DatabaseEngine();
    bool createUser(const std::string& username, const std::string& email, const std::string& password, const std::string& collectionsAccess);
    bool loginCheck(const std::string& username, const std::string& password) const;
    bool resetPassword(const std::string& username, const std::string& newPassword);
    UserDatabase getUser(const std::string& username);
    bool deleteUser(const std::string& username);
};

#endif