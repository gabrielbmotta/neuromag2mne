#include "fiff.h"
#include "sharedmemorywatcher.h"s

#include <iostream>

int main (int argc, char* argv[])
{
    SharedMemoryWatcher watcher;
    
    watcher.watch();

    return 0;
}