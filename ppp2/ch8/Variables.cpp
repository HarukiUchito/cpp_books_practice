#include "Variables.hpp"
#include "Constants.hpp"

#include <exception>
#include <stdexcept>

double Variables::get_value(const std::string name)
{
    if (variables.count(name))
        return variables[name];
    if (constants.count(name))
        return constants[name];
    throw std::runtime_error("the variable is not defined");
}

double Variables::change_value(const std::string name, const double value)
{
    if (constants.count(name))
        throw std::runtime_error("constant value cannot be changed");
    if (variables.count(name) == 0)
        throw std::runtime_error("change value: the variable is not defined");
    return variables[name] = value;
}

double Variables::store_value(const std::string name, const double value, const std::string type)
{
    if (variables.count(name) or constants.count(name))
        throw std::runtime_error("store value: the variable is already defined");
    if (type == decl_key)
        return variables[name] = value;
    else if (type == cons_key)
        return constants[name] = value;
    else
        throw std::runtime_error("store value: unknown type");
}
