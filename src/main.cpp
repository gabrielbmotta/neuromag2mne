// neuromag2mne application

#include <iostream>
#include <unistd.h>

#include "neuromag2mne.hpp"


int main (int argc, char* argv[])
{
  int sleepTime(5);

  Pointer<Controller> c;
  while (true)
  {
    c->start();
    sleep(sleepTime);
  }

  return 0;
}
