#ifndef ENTRY_HPP
#define ENTRY_HPP
#include <string>
#include <vector>
#include <variant>
#include <iostream>
#include "attribute.hpp"

using namespace std;


class Entry
{
    // See UML Document
private:
    string id;
    /// @brief TODO: Explain what this code is
    vector<int> attributes;

public:
    /// @brief Constructor
    // Entry(const string &id, vector<variant<int, double, std::string, Entry *,
    //                                        vector<variant<int, double, std::string, Entry *>>>> &attributes) : id(id), attributes(attributes) {}
    Entry(const string &id, vector<int> attributes); 
    
    /// @brief Logically equivalent to []-accessor
    /// @param i integer index
    /// @return int, double, string, Entry pointer, or a vector of the preceding types
    // variant<int, double, std::string, Entry *, vector<variant<int, double, std::string, Entry *>>>
    // getElement(const int i) const { return attributes[i]; }
    int getElement (const size_t i) const;
    string getId() const;
};
#endif