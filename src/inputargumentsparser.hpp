#ifndef NEUROMAG2MNE_INPUTARGUMENTSPARSER_HPP
#define NEUROMAG2MNE_INPUTARGUMENTSPARSER_HPP

#include <vector>
#include <string>

#include "utils/commandlineoptionsparser.hpp"

struct OptionsPack
{
  OptionsPack()
  :displayHelp(false),
   verboseMode(false),
   randomDataMode(false),
   readFromFileMode(false){ }

  bool displayHelp;
  bool verboseMode;
  bool randomDataMode;
  bool readFromFileMode;
  std::string fileNameToRead;

  void print() const
  {
    std::cout << "Options:\n";
    std::cout << "displayHelp: " << displayHelp << "\n";
    std::cout << "verboseMode: " << verboseMode << "\n";
    std::cout << "randomDataMode: " << randomDataMode << "\n";
    std::cout << "readFromFileMode: " << readFromFileMode << "\n";
    std::cout << "fileNameToRead: " << fileNameToRead << "\n";
  }
};

class InputArgumentsParser
{
public:
  InputArgumentsParser();
  OptionsPack parse(int argc, char* argv[]);
  std::string getHelpStr();
  bool errorWhileParsingOptions() const;

private:
  void configureOptions();
  bool mStopOnError;
  CommandlineOptionsParser mParser;
};


#endif //NEUROMAG2MNE_INPUTARGUMENTSPARSER_HPP
