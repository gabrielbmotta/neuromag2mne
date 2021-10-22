
#include "commandlineoption.hpp"

CommandlineOption::CommandlineOption()
: flagsList(std::vector<std::string>()),
  helpString(std::vector<std::string>()),
  type(CommandlineOption::WITHOUT_VALUE),
  isSet(false)
{
}

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags)
: name(name),
  flagsList(flags),
  helpString(std::vector<std::string>()),
  type(CommandlineOption::WITHOUT_VALUE),
  isSet(false)
{ }

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags,
                  const std::vector<std::string>& helpLine)
: name(name),
  flagsList(flags),
  helpString(helpLine),
  type(CommandlineOption::WITHOUT_VALUE),
  isSet(false)
{ }

CommandlineOption::CommandlineOption(const std::string& name,
                                     const std::vector<std::string>& flags,
                                     const std::vector<std::string>& helpLine,
                                     commandlineOptionType type)
: name(name),
  flagsList(flags),
  helpString(helpLine),
  type(type),
  isSet(false)
{ }

bool CommandlineOption::hasFlag(const std::string& flag) const
{
  std::vector<std::string>::const_iterator it;
  for ( it = flagsList.begin(); it != flagsList.end() ; it++)
    {
        if ( *it == flag)
        {
            return true;
        }
    }
    return false;
}



