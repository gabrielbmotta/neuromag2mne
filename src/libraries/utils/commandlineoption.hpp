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
    std::string mName;
    std::vector<std::string> mFlagsList;
    std::vector<std::string> mHelpString;
    commandlineOptionType mType;
    bool isSet;
    std::string mValue;
    
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
