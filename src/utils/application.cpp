#include "application.hpp"

#include <unistd.h>
#include <iostream>

Application::Application()
: continueRunning(true),
  uSecondsSleepTime(1)
{
}

int Application::run()
{
    while (continueRunning)
    {
      std::cout << "Running!!! \n";
      sleep(uSecondsSleepTime);
    }
    return 0;
}

void Application::stop()
{
  continueRunning = false;
}
