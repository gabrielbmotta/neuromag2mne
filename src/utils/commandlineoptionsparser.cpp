#include "commandlineoptionsparser.hpp"

CommandlineOptionsParser::CommandlineOptionsParser()
: m_bOptionsParsedCorrectly(false),
  m_bStopOnErrors(true),
  m_helpDescriptionPrintMargin1(6),
  m_helpDescriptionPrintMargin2(5)
{
}

void CommandlineOptionsParser::clear()
{
    m_options.clear();
}

bool CommandlineOptionsParser::allOptionsParsedCorrectly() const
{
    return m_bOptionsParsedCorrectly;
}

void CommandlineOptionsParser::addOption(std::string& name,
                                         std::vector<std::string>& flags)
{
    m_options.push_back(CommandlineOption(name, flags));
}

void CommandlineOptionsParser::addOption(std::string& name,
                                         std::vector<std::string>& flags,
                                         std::vector<std::string>& helpLine)
{
    m_options.push_back(CommandlineOption(name, flags, helpLine));
}

void CommandlineOptionsParser::addOption(std::string& name,
                                         std::vector<std::string>& flags,
                                         std::vector<std::string>& helpLine,
                                         CommandlineOption::CommandlineOptionType type)
{
    m_options.push_back(CommandlineOption(name, flags, helpLine, type));
}

void CommandlineOptionsParser::addOption(const CommandlineOption& opt)
{
    m_options.push_back(opt);
}

CommandlineOptionsParser::searchResult CommandlineOptionsParser::flagSearch(const std::string& inputFlag) const
{

    for(size_t i = 0; i < m_options.size(); ++i)
    {
        if(m_options[i].hasFlag(inputFlag))
        {
            return searchResult(true, i);
        }
    }
    return searchResult(false,  0);
}

CommandlineOptionsParser::searchResult CommandlineOptionsParser::optionSearch(const std::string& optName) const
{
    for (size_t i = 0; i < m_options.size(); ++i)
    {
        if(m_options[i].name == optName)
        {
            return searchResult(true, i);
        }
    }
    return searchResult(false, 0);
}

const CommandlineOption& CommandlineOptionsParser::getOption(const std::string& name) const
{
    searchResult thisSearch = optionSearch(name);
    return m_options[thisSearch.position];
}

void CommandlineOptionsParser::setStopOnError(bool s)
{
    m_bStopOnErrors = s;
}

bool CommandlineOptionsParser::getStopOnError() const
{
    return m_bStopOnErrors;
}

bool CommandlineOptionsParser::isSet(const std::string& optionName) const
{
    searchResult thisSearch(optionSearch(optionName));
    if(thisSearch.exists)
    {
        return m_options[thisSearch.position].isSet;
    } else {
        return false;
    }
}

std::string CommandlineOptionsParser::value(const std::string& optionName) const
{
    searchResult thisSearch(optionSearch(optionName));
    if(thisSearch.exists)
    {
        return m_options[thisSearch.position].value;
    } else {
        return std::string();
    }
}

std::string CommandlineOptionsParser::getFlagsAsString(const CommandlineOption& opt) const
{
    std::string concatFlags(opt.flagsList[0]);
    for( unsigned long int i = 1; i < opt.flagsList.size(); ++i )
    {
        concatFlags += ", " + opt.flagsList[i];
    }
    return concatFlags;
}

size_t CommandlineOptionsParser::getMaxSizeOfFlagString(int minSize) const
{
    size_t maxFlagStringSize(static_cast<size_t>(minSize));
    for( unsigned long int i = 0; i < m_options.size(); ++i )
    {
        size_t fSize(getFlagsAsString(m_options[i]).size());
        if( maxFlagStringSize < fSize )
        {
            maxFlagStringSize = fSize;
        }
    }
    return maxFlagStringSize;
}

std::string CommandlineOptionsParser::getHelpDescription() const
{

    size_t colWidth(getMaxSizeOfFlagString(m_helpDescriptionPrintMargin1 + m_helpDescriptionPrintMargin2));

    std::string helpStr("Options:\n");
    for ( unsigned long int i = 0; i < m_options.size(); ++i )
    {
        std::string flags(getFlagsAsString(m_options[i]));
        helpStr += flags + std::string(colWidth - flags.size(),' ');
        if ( m_options[i].helpString.size() > 0 ) 
        {
            helpStr += m_options[i].helpString[0] + "\n";
            for ( unsigned long int j = 1; j < m_options[i].helpString.size(); ++j)
            {
                helpStr += std::string(colWidth, ' ') + m_options[i].helpString[j] + "\n";
            }
        }

    }
    helpStr += "\n";
    return helpStr;
}

int CommandlineOptionsParser::parse(int argc, char** argv)
{
    int i = 1;
    for( ; i < argc; ++i)
    {
        std::string inputflag(argv[i]);
        searchResult optionSearch(flagSearch(inputflag));
        if(optionSearch.exists)
        {
            CommandlineOption& opt = m_options[optionSearch.position];
            opt.isSet = true;
            if (opt.type == CommandlineOption::WITH_VALUE)
            {
                bool notLastInputArg(i < (argc -1));
                if( notLastInputArg )
                {
                    opt.value = std::string(argv[i + 1]);
                    ++i;
                } else {
                    if(m_bStopOnErrors)
                    {
                        std::cout << "Error parsing input argumets. Arg: " << opt.name << " requires a following value.\n";
                        return 1;
                    }
                }
            }
        } else {
            if(m_bStopOnErrors)
            {
                std::cout << "Error. Input argument unknown: " << argv[i] << "\n";
                return 1;
            }
        }
    }

    if ( i == argc)
    {
        m_bOptionsParsedCorrectly = true;   
    }

    return 0;
}



