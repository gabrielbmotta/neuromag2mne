#ifndef COMMANDLINEOPTIONPARSER
#define COMMANDLINEOPTIONPARSER

#include <string>
#include <vector>

#include "commandlineoption.hpp"


// This clas parses input options for the main application. 
// To test it you can use the following code. 


// void testOption(const CommandlineOptionsParser& parser, const std::string& name)
// {
//         std::cout << "\n";
//         if(parser.isSet(name))
//         {
//             std::cout << "option " << name << " is set!!!\n";
//             if(parser.getOption(name).type == withValue)
//             {
//                 std::cout << "and its value is : " << parser.value("option1");
//             }
//         } else {
//             std::cout << "option " << name << " is missing!!!\n";
//         }
//         std::cout << "\n";
// }

// int main(int argc, char* argv[])
// {
//     std::vector<std::string> opt1Flags;
//     opt1Flags.push_back("-dsfs");
//     std::vector<std::string> opt1Help;
//     opt1Help.push_back("This is my second help");
//     CommandlineOption opt1("option1", opt1Flags, opt1Help, withoutValue);
    
//     std::vector<std::string> opt2Flags;
//     opt2Flags.push_back("-f");
//     opt2Flags.push_back("--file");
//     std::vector<std::string> opt2Help;
//     opt2Help.push_back("this is my help");
//     opt2Help.push_back("Because this is my second example.");
//     CommandlineOption opt2("option2", opt2Flags, opt2Help, withValue);

//     CommandlineOption opt3(opt1);
//     opt3.name = std::string("option3");
//     // opt3.flagsList[0] = std::string("-ff");
//     // opt3.flagsList[1] = std::string("--ffile");
//     // opt3.helpString[0] = "this is my help modified";
//     // opt3.helpString.pop_back();
    
//     std::vector<std::string> opt4Flags;
//     opt4Flags.push_back("-h");
//     opt4Flags.push_back("--help");
//     std::vector<std::string> opt4Help;
//     opt4Help.push_back("this is the HELP!!");
//     opt4Help.push_back("Because this is my second example.");
//     CommandlineOption opt4("help", opt4Flags, opt4Help, withoutValue);

//     // if( opt2.hasFlag("-f") )
//     // {
//     //     std::cout << "it has the flag!!\n";
//     // } else {
//     //     std::cout << "it doesn't have the flag!!\n";
//     // }

//     CommandlineOptionsParser parser;
//     parser.addOption(opt1);
//     parser.addOption(opt2);
//     parser.addOption(opt3);
//     parser.addOption(opt4);
//     parser.setStopOnError(false);

//     parser.parse(argc, argv);
    
//     if( parser.allOptionsParsedCorrectly() )
//     {
//         testOption(parser, "option1");
//         testOption(parser, "option2");
//         testOption(parser, "option3");
//         testOption(parser, "help");
//     }


//     std::cout << parser.getHelpDescription();

//     return 0;

// }

class CommandlineOptionsParser
{
private:

    bool m_bOptionsParsedCorrectly;
    bool m_bStopOnErrors;
    int m_helpDescriptionPrintMargin1;
    int m_helpDescriptionPrintMargin2;
    std::vector<CommandlineOption> m_options;

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
                    CommandlineOptionType type );

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

