#include "readFile.hpp"

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

//Commenting out this function because it's not necessary for this class specifically; this class is purely for checking whether a file exists in the database 
string readFile(const string filepath){
    ifstream input;
    input.open(filepath);
    ostringstream sstr;
    sstr << input.rdbuf();
    return sstr.str();
}

// int main(int argc, char** argv) {
//     // Try people.json when running the file

//     if (argc != 2){
//         cout << "Improper number of arguments. Send the filename" << endl;
//         return 1;
//     }

//     // Temp hard code
//     // Pretend that people.json has already been inserted into DB
//     database["people.json"] = ".\\database\\people.json";

//     // Print out database
//     for(map<string,string>::const_iterator it = database.begin(); it != database.end(); ++it) {
//         cout << it->first << " : " << it->second << endl;
//     }
    
//     bool fileExists = isInDatabase(argv[1]);
//     if(fileExists) {
//     	cout << "File Exists: true" << endl;
//     }
//     else {
//     	cout << "File Exists: false" << endl;
//     } 
//     return 0;
// }

