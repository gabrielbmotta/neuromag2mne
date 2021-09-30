#include "controller.hpp"
#include <iostream>
#include <unistd.h>



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
