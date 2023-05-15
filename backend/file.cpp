#include "file.hpp"

using namespace std;

// This will keep track of database
// Key should be filename 
// Value is file location
// Example
// people.json => .\database\people.json
map<string, string> database;

bool isInDatabase(const string fileName) {
    if (database.find(fileName) == database.end()) {
        return false;
    }
    else {
        return true;
    }
}

bool uploadFile(const std::string filename){
    std::string line;

    std::string inputPath = ".\\upload\\" + filename;
    std::string outputPath = ".\\database\\" + filename;

    std::ifstream fin(inputPath);
    std::ofstream fout(outputPath);

    if(fin && fout){
        while(std::getline(fin, line)){
            fout << line << "\n";
        }
        return true;
    }
    else{
        return false;
    }

    return true;
}

//Commenting out this function because it's not necessary for this class specifically; this class is purely for checking whether a file exists in the database 
string readFile(const string filepath){
    ifstream input;
    input.open(filepath);
    ostringstream sstr;
    sstr << input.rdbuf();
    return sstr.str();
}

bool deleteDocument(const string filepath) {
    // if (!isInDatabase(filepath)) {
    //     cout << "Error: Database file not found" << endl;
    //     return false;
    // }
    remove(filepath.c_str());
   // cout << "Document " << filepath << " has been deleted" << endl;
    return true;
}

