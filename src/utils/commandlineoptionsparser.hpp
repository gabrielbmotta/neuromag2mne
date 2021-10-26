#ifndef COMMANDLINEOPTIONPARSER
#define COMMANDLINEOPTIONPARSER

#include <string>
#include <vector>

#include "commandlineoption.hpp"
#include "utils_global.hpp"


class CommandlineOptionsParser
{
private:

    bool mOptionsParsedCorrectly;
    bool mStopOnErrors;
    int mHelpDescriptionPrintMargin1;
    int mHelpDescriptionPrintMargin2;
    std::vector<CommandlineOption> mOptions;

public:

    CommandlineOptionsParser();
    
    void addOption( std::string& name, 
                    std::vector<std::string>& flags );
    
    void addOption( std::string& name, 
                    std::vector<std::string>& flags, 
                    std::vector<std::string>& helpLIne );

    void addOption( std::string& name, 
                    std::vector<std::string>& flags, 
                    std::vector<std::string>& helpLIne, 
                    CommandlineOption::commandlineOptionType type );

    void addOption(const CommandlineOption& opt);

    int parse(int argc, char* argv[]);

    void clear();

    void setStopOnError(bool s);

    bool getStopOnError() const;

    bool allOptionsParsedCorrectly() const;

    bool isSet(const std::string& optName) const;

    std::string value(const std::string& optName) const;

    std::string getHelpDescription() const;

    const CommandlineOption& getOption(const std::string& name) const;

private: 

    struct searchResult
    {
        searchResult(bool b, size_t pos)
        : exists(b), position(pos)
        { }
        bool exists;
        size_t position;
    };

    searchResult optionSearch(const std::string& optionName) const;

    searchResult flagSearch(const std::string& inputFlag) const;

    std::string getFlagsAsString(const CommandlineOption& opt) const;

    size_t getMaxSizeOfFlagString(int minSize) const;
};


#endif //COMMANDLINEOPTIONPARSER

