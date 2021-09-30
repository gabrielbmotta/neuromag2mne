#include "sharedmemorywatcher.hpp"
#include <iostream>

int main (int argc, char* argv[])
{
    SharedMemoryWatcher watcher;
    
    watcher.watch();

    return 0;
}