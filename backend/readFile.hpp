#ifndef READFILE_HPP
#define READFILE_HPP
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

bool isInDatabase(const std::string filepath);
std::string readFile(const std::string filepath);
#endif