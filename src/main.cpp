// neuromag2mne application

#include <unistd.h>
#include <iostream>
#include <iostream>

#include "neuromag2mne.hpp"

#define AA "this"
#define AAA "test " AA

int main (int argc, char* argv[])
{
  
  int sleepTime(5);

  std::cout << AAA << "\n";

  ScopedPointer<Controller> c;
  while (true)
  {
    c->start();
    sleep(sleepTime);
  }

  return 0;
}


