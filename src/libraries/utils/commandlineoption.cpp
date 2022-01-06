
#include "commandlineoption.hpp"

CommandlineOption::CommandlineOption()
: mFlagsList(std::vector<std::string>()),
  mHelpString(std::vector<std::string>()),
  mType(CommandlineOption::WITHOUT_VALUE),
  isSet(false)
{
}

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags)
: mName(name),
  mFlagsList(flags),
  mHelpString(std::vector<std::string>()),
  mType(CommandlineOption::WITHOUT_VALUE),
  isSet(false)
{ }

CommandlineOption::CommandlineOption(const std::string& name,
                  const std::vector<std::string>& flags,
                  const std::vector<std::string>& helpLine)
: mName(name),
  mFlagsList(flags),
  mHelpString(helpLine),
  mType(CommandlineOption::WITHOUT_VALUE),
  isSet(false)
{ }

CommandlineOption::CommandlineOption(const std::string& name,
                                     const std::vector<std::string>& flags,
                                     const std::vector<std::string>& helpLine,
                                     commandlineOptionType type)
: mName(name),
  mFlagsList(flags),
  mHelpString(helpLine),
  mType(type),
  isSet(false)
{ }

bool CommandlineOption::hasFlag(const std::string& flag) const
{
  std::vector<std::string>::const_iterator it;
  for ( it = mFlagsList.begin(); it != mFlagsList.end() ; it++)
    {
        if ( *it == flag)
        {
            return true;
        }
    }
    return false;
}



