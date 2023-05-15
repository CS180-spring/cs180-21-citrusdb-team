#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "jsonStrings.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using namespace std;

void jsonStrings(const string& inputFile, vector<Entry<string>>& entries) {
    ifstream inFile(inputFile);
    json data;
    inFile >> data;

    json people = data["science fiction authors"];

    for (auto& person: people) {
        Entry<string> newEntry;
        newEntry.id = person["_id"];

        vector<Attribute<string>> attributes;
        for (auto it = person.begin(); it != person.end(); ++it) {
            string key = it.key();
            string value = it.value().dump();
            attributes.push_back({key, value});
        }

        newEntry.attributes = attributes;
        entries.push_back(newEntry);
    }
}