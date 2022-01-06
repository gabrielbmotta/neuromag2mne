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
   readFromFileMode(false),
   neuromagMode(false),
   fileNameToRead(""),
   saveToFileMode(false),
   fileNameToSave(""),
   dontSendDataMode(false)
   { }

  bool displayHelp;
  bool verboseMode;
  bool randomDataMode;
  bool readFromFileMode;
  bool neuromagMode;
  std::string fileNameToRead;
  bool saveToFileMode;
  std::string fileNameToSave;
  bool dontSendDataMode;
  bool sendToFieldTripMode;
  std::string fieldtripBufferAddr;

  void print() const
  {
    std::cout << "Options:\n";
    std::cout << "displayHelp: " << displayHelp << "\n";
    std::cout << "verboseMode: " << verboseMode << "\n";
    std::cout << "randomDataMode: " << randomDataMode << "\n";
    std::cout << "readFromFileMode: " << readFromFileMode << "\n";
    std::cout << "fileNameToRead: " << fileNameToRead << "\n";
    std::cout << "neuromagMode: " << neuromagMode << "\n";
    std::cout << "saveToFileMode: " << saveToFileMode << "\n";
    std::cout << "fileNameToSave: " << fileNameToSave << "\n";
    std::cout << "dontSendDataMode; " << dontSendDataMode << "\n";
  }
};

class InputArgumentsParser
{
public:
  InputArgumentsParser();
  ~InputArgumentsParser();
  OptionsPack parse(int argc, char* argv[]);
  std::string getHelpStr();
  bool errorWhileParsingOptions() const;

private:
  void configureOptions();
  bool mStopOnError;
  CommandlineOptionsParser mParser;
};


#endif //NEUROMAG2MNE_INPUTARGUMENTSPARSER_HPP
