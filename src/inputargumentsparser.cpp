#include <string>

#include "inputargumentsparser.hpp"

InputArgumentsParser::InputArgumentsParser()
: mStopOnError(false)
{
  mParser.setStopOnError(mStopOnError);
  configureOptions();
}

InputArgumentsParser::~InputArgumentsParser()
{

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
    optionsOut.neuromagMode = mParser.isSet("optionNeuromag");
    optionsOut.saveToFileMode = mParser.isSet("optionSaveToFile");
    if (mParser.isSet("optionSaveToFile") )
    {
      optionsOut.fileNameToSave = mParser.value("optionsSaveToFile");
    }
    optionsOut.dontSendDataMode = mParser.isSet("optionDontSendData");
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
  CommandlineOption optionHelp("optionHelp",
                            helpFlags,
                            helpOptionHelp,
                            CommandlineOption::WITHOUT_VALUE);
  mParser.addOption(optionHelp);

  std::vector<std::string> verboseFlags;
  verboseFlags.push_back("-v");
  verboseFlags.push_back("--verbose");
  std::vector<std::string> verboseHelp;
  verboseHelp.push_back("Verbose mode on.");
  verboseHelp.push_back("During execution, different description messages will be printed to terminal.");
  CommandlineOption optionVerbose("optionVerbose",
                               verboseFlags,
                               verboseHelp,
                               CommandlineOption::WITHOUT_VALUE);
  mParser.addOption(optionVerbose);

  std::vector<std::string> randomModeFlags;
  randomModeFlags.push_back("--random");
  randomModeFlags.push_back("-r");
  std::vector<std::string> randomModeHelp;
  randomModeHelp.push_back("Random data mode.");
  randomModeHelp.push_back("Instead of capturing raw data from Neuromag MEG,");
  randomModeHelp.push_back("generate random data.");
  CommandlineOption optionRandomData("optionRandomData",
                                  randomModeFlags,
                                  randomModeHelp,
                                  CommandlineOption::WITHOUT_VALUE);
  mParser.addOption(optionRandomData);

  std::vector<std::string> readFromFileFlags;
  readFromFileFlags.push_back("-i");
  readFromFileFlags.push_back("--in");
  std::vector<std::string> readFromFileHelp;
  readFromFileHelp.push_back("Read from file");
  readFromFileHelp.push_back("Instead of capturing raw data from Neuromag MEG,");
  readFromFileHelp.push_back("read the data from a file and stream it.");
  CommandlineOption optionReadFromFile("optionReadFromFile",
                                    readFromFileFlags,
                                    readFromFileHelp,
                                    CommandlineOption::WITH_VALUE);
  mParser.addOption(optionReadFromFile);

  std::vector<std::string> neuromagModeFlags;
  neuromagModeFlags.push_back("--neuromag");
  neuromagModeFlags.push_back("-n");
  std::vector<std::string> neuromagModeHelp;
  neuromagModeHelp.push_back("Neuromag mode.");
  neuromagModeHelp.push_back("Capturing raw data from a Neuromag system.");
  CommandlineOption optionNeuromag("optionNeuromag",
                                   neuromagModeFlags,
                                   neuromagModeHelp,
                                   CommandlineOption::WITHOUT_VALUE);
  mParser.addOption(optionNeuromag);

  std::vector<std::string> saveToFileFlags;
  saveToFileFlags.push_back("-o");
  saveToFileFlags.push_back("--out");
  std::vector<std::string> saveToFileHelp;
  saveToFileHelp.push_back("Save to file.");
  saveToFileHelp.push_back("Specify a filename to save the output to.");
  CommandlineOption optionSaveToFile("optionSaveToFile",
                                  saveToFileFlags,
                                  saveToFileHelp,
                                  CommandlineOption::WITH_VALUE);
  mParser.addOption(optionSaveToFile);

  std::vector<std::string> doNotSendDataFlags;
  doNotSendDataFlags.push_back("--dont-send-data");
  std::vector<std::string> doNotSendDataHelp;
  doNotSendDataHelp.push_back("Avoid sending data to a server.");
  CommandlineOption optionDontSendData("optionDontSendData",
                                    doNotSendDataFlags,
                                    doNotSendDataHelp);
  mParser.addOption(optionDontSendData);
}

bool InputArgumentsParser::errorWhileParsingOptions() const
{
  return !mParser.allOptionsParsedCorrectly();
}

std::string InputArgumentsParser::getHelpStr()
{
  return mParser.getHelpDescription();
}
