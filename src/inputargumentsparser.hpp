#ifndef NEUROMAG2MNE_INPUTARGUMENTSPARSER_HPP
#define NEUROMAG2MNE_INPUTARGUMENTSPARSER_HPP

#include <vector>
#include <string>

#include "utils/commandlineoptionsparser.hpp"

struct OptionsPack
{
    bool displayHelp;
    bool verboseMode;
    bool randomDataMode;
    bool readFromFileMode;
    std::string fileNameToRead;
};

class InputArgumentsParser
{
public:
  InputArgumentsParser();
  OptionsPack parse(int argc, char* argv[]);
  std::string getHelp();
  bool errorWhileParsingOptions() const;

private:
  void configureOptions();
  bool mStopOnError;
  CommandlineOptionsParser mParser;
};


#endif //NEUROMAG2MNE_INPUTARGUMENTSPARSER_HPP
