#include <string>

#include "inputargumentsparser.hpp"

InputArgumentsParser::InputArgumentsParser()
: mStopOnError(false)
{
  mParser.setStopOnError(mStopOnError);
  configureOptions();
}

OptionsPack InputArgumentsParser::parse(int argc, char **argv)
{
  mParser.parse(argc, argv);
  OptionsPack optionsOut;
  if (mParser.allOptionsParsedCorrectly())
  {
    optionsOut.displayHelp = mParser.isSet("optionHelp");
    optionsOut.verboseMode = mParser.isSet("optionVerbose");
    optionsOut.randomDataMode = mParser.isSet("optionRandomData");
    optionsOut.readFromFileMode = mParser.isSet("optionReadFromFile");
    if ( mParser.isSet("optionReadFromFile") )
    {
      optionsOut.fileNameToRead = mParser.value("optionReadFromFile");
    }
  }
  return optionsOut;
}

void InputArgumentsParser::configureOptions()
{
  std::vector<std::string> helpFlags;
  helpFlags.push_back("-h");
  helpFlags.push_back("-H");
  helpFlags.push_back("--help");
  helpFlags.push_back("-help");
  helpFlags.push_back("/h");
  helpFlags.push_back("/?");
  std::vector<std::string> helpOptionHelp;
  helpOptionHelp.push_back("Display this help description.");
  CommandlineOption optHelp("optionHelp", helpFlags, helpOptionHelp, CommandlineOption::WITHOUT_VALUE);
  mParser.addOption(optHelp);

  std::vector<std::string> verboseFlags;
  verboseFlags.push_back("-v");
  verboseFlags.push_back("--verbose");
  std::vector<std::string> verboseHelp;
  verboseHelp.push_back("Verbose mode on.");
  verboseHelp.push_back("During execution, different description messages will be printed to terminal.");
  CommandlineOption optVerbose("optionVerbose", verboseFlags, verboseHelp, CommandlineOption::WITHOUT_VALUE);
  mParser.addOption(optVerbose);

  std::vector<std::string> randomModeFlags;
  randomModeFlags.push_back("--random");
  randomModeFlags.push_back("-r");
  std::vector<std::string> randomModeHelp;
  randomModeHelp.push_back("Random data mode.");
  randomModeHelp.push_back("Instead of capturing raw data from Neuromag MEG,");
  randomModeHelp.push_back("generate random data.");
  CommandlineOption optRandomData("optionRandomData", randomModeFlags,
                                  randomModeHelp,
                                  CommandlineOption::WITHOUT_VALUE);
  mParser.addOption(optRandomData);

  std::vector<std::string> readFromFileFlags;
  readFromFileFlags.push_back("-f");
  readFromFileFlags.push_back("--file");
  std::vector<std::string> readFromFileHelp;
  readFromFileHelp.push_back("Read from file");
  readFromFileHelp.push_back("Instead of capturing raw data from Neuromag MEG,");
  readFromFileHelp.push_back("read the data from a file and stream it.");
  CommandlineOption optReadFromFile("optionReadFromFile", readFromFileFlags, readFromFileHelp,
                                    CommandlineOption::WITH_VALUE);
  mParser.addOption(optReadFromFile);
}

bool InputArgumentsParser::errorWhileParsingOptions() const
{
  return !mParser.allOptionsParsedCorrectly();
}

std::string InputArgumentsParser::getHelp()
{
  return mParser.getHelpDescription();
}