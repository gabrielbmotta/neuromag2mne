#include "commandlineoptionsparser.hpp"

CommandlineOptionsParser::CommandlineOptionsParser()
    : mOptionsParsedCorrectly(false),
      mStopOnErrors(true),
      mHelpDescriptionPrintMargin1(6),
      mHelpDescriptionPrintMargin2(5)
{
}

void CommandlineOptionsParser::clear()
{
  mOptions.clear();
}

bool CommandlineOptionsParser::allOptionsParsedCorrectly() const
{
  return mOptionsParsedCorrectly;
}

void CommandlineOptionsParser::addOption(std::string& name,
                                         std::vector<std::string>& flags)
{
  mOptions.push_back(CommandlineOption(name, flags));
}

void CommandlineOptionsParser::addOption(std::string& name,
                                         std::vector<std::string>& flags,
                                         std::vector<std::string>& helpLine)
{
  mOptions.push_back(CommandlineOption(name, flags, helpLine));
}

void CommandlineOptionsParser::addOption(std::string& name,
                                         std::vector<std::string>& flags,
                                         std::vector<std::string>& helpLine,
                                         CommandlineOption::commandlineOptionType type)
{
  mOptions.push_back(CommandlineOption(name, flags, helpLine, type));
}

void CommandlineOptionsParser::addOption(const CommandlineOption& opt)
{
  mOptions.push_back(opt);
}

CommandlineOptionsParser::searchResult CommandlineOptionsParser::flagSearch(const std::string& inputFlag) const
{

  for(size_t i = 0; i < mOptions.size(); ++i)
  {
    if(mOptions[i].hasFlag(inputFlag))
    {
      return searchResult(true, i);
    }
  }
  return searchResult(false,  0);
}

CommandlineOptionsParser::searchResult CommandlineOptionsParser::optionSearch(const std::string& optName) const
{
  for (size_t i = 0; i < mOptions.size(); ++i)
  {
    if(mOptions[i].mName == optName)
    {
      return searchResult(true, i);
    }
  }
  return searchResult(false, 0);
}

const CommandlineOption& CommandlineOptionsParser::getOption(const std::string& name) const
{
  searchResult thisSearch = optionSearch(name);
  return mOptions[thisSearch.position];
}

void CommandlineOptionsParser::setStopOnError(bool s)
{
  mStopOnErrors = s;
}

bool CommandlineOptionsParser::getStopOnError() const
{
  return mStopOnErrors;
}

bool CommandlineOptionsParser::isSet(const std::string& optionName) const
{
  searchResult thisSearch(optionSearch(optionName));
  if(thisSearch.exists)
  {
    return mOptions[thisSearch.position].isSet;
  } else {
    return false;
  }
}

std::string CommandlineOptionsParser::value(const std::string& optionName) const
{
  searchResult thisSearch(optionSearch(optionName));
  if(thisSearch.exists)
  {
    return mOptions[thisSearch.position].mValue;
  } else {
    return std::string();
  }
}

std::string CommandlineOptionsParser::getFlagsAsString(const CommandlineOption& opt) const
{
  std::string concatFlags(opt.mFlagsList[0]);
  for(unsigned long int i = 1; i < opt.mFlagsList.size(); ++i )
  {
    concatFlags += ", " + opt.mFlagsList[i];
  }
  return concatFlags;
}

size_t CommandlineOptionsParser::getMaxSizeOfFlagString(int minSize) const
{
  size_t maxFlagStringSize(static_cast<size_t>(minSize));
  for(unsigned long int i = 0; i < mOptions.size(); ++i )
  {
    size_t fSize(getFlagsAsString(mOptions[i]).size());
    if( maxFlagStringSize < fSize )
    {
      maxFlagStringSize = fSize;
    }
  }
  return maxFlagStringSize;
}

std::string CommandlineOptionsParser::getHelpDescription() const
{

  size_t colWidth(getMaxSizeOfFlagString(mHelpDescriptionPrintMargin1 + mHelpDescriptionPrintMargin2) + 3);

  std::string helpStr("Options:\n");
  for (unsigned long int i = 0; i < mOptions.size(); ++i )
  {
    std::string flags(getFlagsAsString(mOptions[i]));
    helpStr += flags + std::string(colWidth - flags.size(),' ');
    if (mOptions[i].mHelpString.size() > 0 )
    {
      helpStr += mOptions[i].mHelpString[0] + "\n";
      for (unsigned long int j = 1; j < mOptions[i].mHelpString.size(); ++j)
      {
        helpStr += std::string(colWidth, ' ') + mOptions[i].mHelpString[j] + "\n";
      }
    }

  }
  helpStr += "\n";
  return helpStr;
}

int CommandlineOptionsParser::parse(int argc, char** argv)
{
  bool errorsWhileParsing(false);
  int i = 1;
  for( ; i < argc; ++i)
  {
    std::string inputflag(argv[i]);
    searchResult optionSearch(flagSearch(inputflag));
    if(optionSearch.exists)
    {
      CommandlineOption& opt = mOptions[optionSearch.position];
      opt.isSet = true;
      if (opt.mType == CommandlineOption::WITH_VALUE)
      {
        bool notLastInputArg(i < (argc -1));
        if( notLastInputArg )
        {
          opt.mValue = std::string(argv[i + 1]);
          ++i;
        } else {
          std::cout << "Error parsing input arguments. Arg: " << opt.mName << " requires a following value.\n";
          errorsWhileParsing = true;
          if(mStopOnErrors)
          {
            return 1;
          }
        }
      }
    } else {
      errorsWhileParsing = true;
      std::cout << "Error. Input argument unknown: " << argv[i] << "\n";
      if(mStopOnErrors)
      {
        return 1;
      }
    }
  }

  if ( i == argc && !errorsWhileParsing )
  {
    mOptionsParsedCorrectly = true;
  }

  return 0;
}



