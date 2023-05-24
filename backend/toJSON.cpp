#include "toJSON.hpp"
#include <string>
#include <iostream>

using namespace std;

string toJSON(const string attribute, const string value) {
     string jsonFormat = "\"" + attribute + "\": \"" + value + "\"";
     return jsonFormat;    		
}

int main(int argc, char** argv) {
     //userID will be the test attribute and 12345 will be the test value
     string testAttribute = "userID";
     string testValue = "12345";

     cout << toJSON(testAttribute, testValue) << endl;
     return 0;
}
