#ifndef NEUROMAG2MNE_COMMANDLINEOPTION_HPP
#define NEUROMAG2MNE_COMMANDLINEOPTION_HPP

#include <iostream>
#include <string>
#include <vector>

#include "utils_global.hpp"

class CommandlineOption
{
public:
    enum commandlineOptionType
    {
        WITH_VALUE,
        WITHOUT_VALUE
    };
    std::string name;
    std::vector<std::string> flagsList;
    std::vector<std::string> helpString;
    commandlineOptionType type;
    bool isSet;
    std::string value;
    
    CommandlineOption();

    CommandlineOption(const std::string& name, 
                      const std::vector<std::string>& flags);

    CommandlineOption(const std::string& name, 
                      const std::vector<std::string>& flags, 
                      const std::vector<std::string>& helpLine);

    CommandlineOption(const std::string& name,
                      const std::vector<std::string>& flags,
                      const std::vector<std::string>& helpLine,
                      commandlineOptionType type);

    bool hasFlag(const std::string& flag) const;

};


#endif // NEUROMAG2MNE_COMMANDLINEOPTION_HPP
