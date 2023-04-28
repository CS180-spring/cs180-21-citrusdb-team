#include "attribute.hpp"

std::string Int::toJSON() const
{
    return std::to_string(data);
}