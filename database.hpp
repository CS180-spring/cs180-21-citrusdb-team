#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>

class Database{
    private:
        std::map<std::string, std::string> data;

    public:

    bool deleteDocument(const std::string filepath);

    bool isInDatabase(const std::string filename);

    std::string readFile(const std::string filepath);

    //@brief Upload a file that is stored in the upload folder into the database folder
        //Assumes that file to be uploaded is present in the upload folder.
    //@param filename of the file to be uploaded from upload to database.
    //@return true if file was able to be successfully opened and transferred, false if there was an error opening either file. 
    bool uploadFile(const std::string filename);

};