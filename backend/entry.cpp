#include "readFile.hpp"
#include "../rapidjson/document.h"
#include <iostream>



using namespace rapidjson;

// int main(){
//     Document document;
//     document.Parse(readFile("../database/patients.json").c_str());
//     for (auto& i document.MemberBegin(): document){

//     }
//     const Value& patients = document["patients"].GetArray();
//     for (size_t i = 0; i < patients.Size(); i++){
//         const Value& patient = patients[i];
//         std::cout << patient["First name"].GetString() << endl;
//     }
// }

