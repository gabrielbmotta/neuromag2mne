// neuromag2mne application

#include <unistd.h>
#include <iostream>
#include <iostream>

#include "neuromag2mne.hpp"

int main (int argc, char* argv[])
{
  
  int sleepTime(5);

  ScopedPointer<Controller> c;
  while (true)
  {
    c->start();
    sleep(sleepTime);
  }

  return 0;
}


