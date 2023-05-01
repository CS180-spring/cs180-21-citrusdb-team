#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP
#include <string>


struct Attribute{
    
    virtual std::string toJSON() const = 0;
};

struct Int: public Attribute{
    int data;
    Int(int n): data(data) {}
    std::string toJSON() const;
};

#endif