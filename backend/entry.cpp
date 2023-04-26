#include "entry.hpp"


Entry::Entry(const string &id, vector<variant<int, double>> attributes):
    id(id), attributes(attributes)
{}

variant<int, double> Entry::getElement (const size_t i) const
{
    return attributes[i];
}

string Entry::getId() const
{
    return id;
}

int main (){
    vector<variant<int, double>> v = {1, 2, 3, 4, 5, 6};
    Entry en("1234", v);
    cout << en.getElement(0) << endl;
    return 0;
}
