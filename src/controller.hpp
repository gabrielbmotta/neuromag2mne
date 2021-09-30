#include "commandwatcher.hpp"
#include "datawatcher.hpp"
#include "pointer.hpp"

class Controller
{
public:
    Controller();

    void start();

private:
    Pointer<CommandWatcher> commandWatcher;
    Pointer<DataWatcher> dataWatcher;
};