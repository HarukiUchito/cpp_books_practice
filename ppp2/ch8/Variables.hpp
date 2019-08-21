#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include <string>
#include <map>

class Variables {
public:
    double get_value(const std::string name);
    double change_value(const std::string name, const double value);
    double store_value(const std::string name, const double value, const std::string type);
private:
    std::map<std::string, double> variables;
    std::map<std::string, double> constants;
};

#endif