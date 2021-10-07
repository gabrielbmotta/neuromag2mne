
#include "commandlineoption.hpp"


CommandlineOption::CommandlineOption()
: name(""),
  flagsList(std::vector<std::string>()),
  helpString(std::vector<std::string>()),
  type(defaultOptionType),
  isSet(false),
  value("")
{
}

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags)
: name(name),
  flagsList(flags),
  helpString(std::vector<std::string>()),
  type(defaultOptionType),
  isSet(false),
  value("")
{
}

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags,
                  const std::vector<std::string>& helpLine)
: name(name),
  flagsList(flags),
  helpString(helpLine),
  type(defaultOptionType),
  isSet(false),
  value("")
{
}

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags,
                  const std::vector<std::string>& helpLine,
                  CommandlineOptionType type)
: name(name),
  flagsList(flags),
  helpString(helpLine),
  type(type),
  isSet(false),
  value("")
{
}

bool CommandlineOption::hasFlag(const std::string& flag) const
{
    for ( int i = 0; i < flagsList.size(); ++i )
    {
        if ( flagsList[i] == flag)
        {
            return true;
        }
    }
    return false;
}



