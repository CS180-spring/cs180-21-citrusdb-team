#include "entry.hpp"


Entry::Entry(const string &id, vector<int> attributes):
    id(id), attributes(attributes)
{}

int Entry::getElement (const size_t i) const
{
    return attributes[i];
}

string Entry::getId() const
{
    return id;
}

