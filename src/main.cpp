// neuromag2mne application

#include "neuromag2mne.hpp"

int main (int argc, char* argv[])
{
  ScopedPointer<Controller> controller;
  controller->parseInputArguments(argc, argv);
  controller->start();
  return 0;
}


