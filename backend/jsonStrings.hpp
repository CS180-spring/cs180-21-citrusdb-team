#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

template<typename T>
struct Attribute {
    string name;
    T value;
};

template<typename T>
struct Entry {
    string id;
    vector<Attribute<T>> attributes;
};

void jsonStrings(const string& inputFile, vector<Entry<string>>& entries);