#ifndef COMMANDLINEOPTION
#define COMMANDLINEOPTION

#include <iostream>
#include <string>
#include <vector>

enum CommandlineOptionType
{
    withValue,
    withoutValue
};

class CommandlineOption
{
public:
    std::string name;
    std::vector<std::string> flagsList;
    std::vector<std::string> helpString;
    CommandlineOptionType type;
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
                      CommandlineOptionType type);

    bool hasFlag(const std::string& flag) const;

};


#endif // COMMANDLINEOPTION
