#ifndef FILE_HPP
#define FILE_HPP
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

bool isInDatabase(const std::string filepath);
std::string readFile(const std::string filepath);
bool uploadFile(const std::string filename);
bool deleteDocument(const std::string filepath);
#endif