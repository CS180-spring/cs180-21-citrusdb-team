#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>

class Database{
    private:
        std::map<std::string, std::string> data;

    public:
    
    Database();
    
    ~Database();

    bool deleteDocument(const std::string filename);

    bool isInDatabase(const std::string filename);

    std::string readFile(const std::string filepath);

    bool uploadFile(const std::string filename);

};