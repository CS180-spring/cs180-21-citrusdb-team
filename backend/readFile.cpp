#include "readFile.hpp"
#include <iostream>
#include <map>

using namespace std;

// This will keep track of database
// Key should be filename 
// Value is file location
// Example
// people.json => .\database\people.json
map<string, string> database;

bool isInDatabase(const string filename) {
    if (database.find(filename) == database.end()) {
        return false;
    }
    else {
        return true;
    }
}

string readFile(const string filename){
    if (isInDatabase(filename)) {
        cout << "File in database!" << endl;
        
        // Read file
        string filePath = database.at(filename);
        ifstream input;
        input.open(filePath);
        ostringstream sstr;
        sstr << input.rdbuf();
        return sstr.str();
    }
    else {
        return "File not in database!";
    }
}

int main(int argc, char** argv) {
    // Try people.json when running the file

    if (argc != 2){
        cout << "Improper number of arguments. Send the filename" << endl;
        return 1;
    }

    // Temp hard code
    // Pretend that people.json has already been inserted into DB
    database["people.json"] = ".\\database\\people.json";

    // Print out database
    for(map<string,string>::const_iterator it = database.begin(); it != database.end(); ++it) {
        cout << it->first << " : " << it->second << endl;
    }

    cout << readFile(argv[1]) << endl;
    return 0;
}