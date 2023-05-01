#include "deleteFile.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool isinDatabase(const string filepath) {
    // placeholder
    return true;
}

bool deleteDocument(const string filepath) {
    if (!isinDatabase(filepath)) {
        cout << "Error: Database file not found" << endl;
        return false;
    }
    remove(filepath.c_str());
   // cout << "Document " << filepath << " has been deleted" << endl;
    return true;
}