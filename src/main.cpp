// neuromag2mne application

#include <unistd.h>
#include <iostream>
#include <iostream>

#include "neuromag2mne.hpp"

int main (int argc, char* argv[])
{
  int sleepTime(5);

  // Pointer<Controller> c;
  while (true)
  {
    // c->start();
    std::cout << "Hello again!!\n";
    sleep(sleepTime);
  }

  return 0;
}
