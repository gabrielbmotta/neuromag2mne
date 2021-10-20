// neuromag2mne application

#include "neuromag2mne.hpp"

int main (int argc, char* argv[])
{
  ScopedPointer<Controller> controller;
  controller->parseInputArguments(argc, argv);
  controller->start();
  return 0;
}

//todo logging mechanism
//todo licensing. candidate mozilla public license.
//todo testing must include coverage
//todo profiling
//todo documentation
//todo standardize use of namespace in the project